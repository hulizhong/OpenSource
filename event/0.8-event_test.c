/*
 * Compile with:
 * cc -I/usr/local/include -o event-test event-test.c -L/usr/local/lib -levent
 */

#include <sys/types.h>
#include <sys/stat.h>
#ifndef WIN32
#include <sys/queue.h>
#include <unistd.h>
#include <sys/time.h>
#else
#include <windows.h>
#endif
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#include "event.h"


void
fifo_buffev_write(struct bufferevent *buffev, void *arg)
{
	char buf[255] = {0};
    sprintf(buf, "feedback in fd=%d, ev=%p\n", buffev->ev_write.ev_fd, &(buffev->ev_write));
    bufferevent_write(buffev, buf, strlen(buf));
	fprintf(stdout, "Write: %s", buf);
}

void fifo_buffev_read(struct bufferevent *buffev, void *arg)
{
	char buf[255] = {0};
    bufferevent_read(buffev, buf, sizeof(buf));
	fprintf(stdout, "Read: %s", buf);
}

int
main (int argc, char **argv)
{
	struct event evfifo, evwrite;
	struct stat st;
	char *fifo = "event.fifo";
	int socket;
 
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

	socket = open (fifo, O_RDWR | O_NONBLOCK, 0);
	if (socket == -1) {
		perror("open");
		exit (1);
	}

	fprintf(stderr, "Write data to %s\n", fifo);

	event_init();
    struct bufferevent *buffev = bufferevent_new(socket, fifo_buffev_read, fifo_buffev_write, NULL, NULL);
    //bufferevent_enable(buffev, EV_READ|EV_WRITE);
    bufferevent_enable(buffev, EV_READ);
    bufferevent_enable(buffev, EV_WRITE);

	event_dispatch();
	return (0);
}

