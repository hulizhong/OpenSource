/*
 * Compile with:
 * cc -I/usr/local/include -o event-test event-test.c -L/usr/local/lib -levent
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/queue.h>
#include <sys/time.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#include "event.h"

void
fifo_read(int fd, short event, void *arg)
{
	char buf[255];
	int len;
	struct event *ev = arg;

	/* Reschedule this event */
	event_add(ev, NULL);

	//fprintf(stderr, "fifo_read called with fd: %d, event: %d, arg: %p\n", fd, event, arg);

	len = read(fd, buf, sizeof(buf) - 1);
	if (len == -1) {
		perror("read");
		return;
	} else if (len == 0) {
		fprintf(stderr, "Connection closed\n");
		return;
	}

	buf[len] = '\0';
	fprintf(stdout, "Read: %s", buf);
}

void
fifo_timeout(int fd, short event, void *arg)
{
    struct event *evtimeout = (struct event*)arg;
    fprintf(stdout, "timeout with %d seconds %d useconds\n", evtimeout->ev_timeout.tv_sec, evtimeout->ev_timeout.tv_usec);
    struct timeval now;
    now.tv_sec = 3;
    now.tv_usec = 0;
	event_add(evtimeout, &now);
}

void
fifo_read_timeout(int fd, short event, void *arg)
{
    if (event & EV_TIMEOUT)
        fifo_timeout(fd, event, arg);
    else if (event & EV_READ) {
        char buf[255];
        int len;
        struct event *ev = arg;

        /* Reschedule this event, diff with fifo_read at this step */
        struct timeval delay;
        delay.tv_sec = 3;
        delay.tv_usec = 0;
        event_add(ev, &delay);

        //fprintf(stderr, "fifo_read called with fd: %d, event: %d, arg: %p\n", fd, event, arg);

        len = read(fd, buf, sizeof(buf) - 1);
        if (len == -1) {
            perror("read");
            return;
        } else if (len == 0) {
            fprintf(stderr, "Connection closed\n");
            return;
        }

        buf[len] = '\0';
        fprintf(stdout, "Read: %s", buf);
    }
    else
        fprintf(stdout, "cant support: %d\n", event);
}

int
main (int argc, char **argv)
{
	struct stat st;
	char *fifo = "event.fifo";
	int socket;
	struct event evfifo, evtimeout;
    struct timeval delay;
    delay.tv_sec = 3;
    delay.tv_usec = 0;
 
	if (lstat (fifo, &st) == 0) {
		if ((st.st_mode & S_IFMT) == S_IFREG) {
			errno = EEXIST;
			perror("lstat");
			exit (1);
		}
	}

	unlink (fifo);
	if (mkfifo (fifo, 0600) == -1) {
		perror("mkfifo");
		exit (1);
	}

	/* Linux pipes are broken, we need O_RDWR instead of O_RDONLY */
#ifdef __linux
	socket = open (fifo, O_RDWR | O_NONBLOCK, 0);
#else
	socket = open (fifo, O_RDONLY | O_NONBLOCK, 0);
#endif

	if (socket == -1) {
		perror("open");
		exit (1);
	}

	fprintf(stderr, "Write data to %s\n", fifo);

	/* Initalize the event library */
	event_init();

#if 0
	// Initalize one event
	event_set(&evfifo, socket, EV_READ, fifo_read, &evfifo);
	// Add it to the active events, without a timeout
	event_add(&evfifo, NULL);
#endif

#if 0
	event_set(&evtimeout, socket, EV_TIMEOUT, fifo_timeout, &evtimeout);
    fprintf(stderr, "sec: %d  usec: %d\n", delay.tv_sec, delay.tv_usec);
	event_add(&evtimeout, &delay);
#endif
	
#if 1
	event_set(&evfifo, socket, EV_READ|EV_TIMEOUT, fifo_read_timeout, &evfifo);
	event_add(&evfifo, &delay);
#endif
	event_dispatch();

	return (0);
}

