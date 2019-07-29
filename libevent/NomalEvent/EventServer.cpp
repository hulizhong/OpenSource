/*************************************************************************
	> File Name: EventServer.cpp
	> Author: 
	> Mail: 
	> Created Time: Sat 13 Oct 2018 05:27:22 AM CDT
 ************************************************************************/

#include <iostream>
#include <event2/event.h>
#include <event2/listener.h>
//#include <sys/socket.h>
//#include <netinet/in.h>
#include <arpa/inet.h> //inet_addr
#include <string.h> //strlen
#include <unistd.h>


#define BUFFER_LEN 128

void clientReadCb(evutil_socket_t fd, short what, void *arg)
{
    if (!(what & EV_READ))
    {
        std::cout << "client fd." << fd << " not trigger readevent in readcallback." << std::endl;
        return;
    }
    char buffer[BUFFER_LEN] = {0};
    int res = recv(fd, buffer, sizeof(buffer), 0);
    if (res > 0) {
        std::cout << "rcv fd." << fd << " say:" << buffer;
        res = send(fd, buffer, strlen(buffer), 0);
        if (res == strlen(buffer)) {
            std::cout << "\treply fd." << fd << " ok." << std::endl;
        }
        else {
            std::cout << "\treply fd." << fd << " failed." << std::endl;
        }
    }
    else if (res == 0) {
        std::cout << "rcv fd." << fd << " close." << std::endl;
        /* Must call event_del, 
         * cause ev was ev_persist and always notify user the connect exit. */
        event* ev = reinterpret_cast<event*>(arg);
        event_del(ev);
        event_free(ev);
        close(fd);
    }
    else {
        std::cout << "rcv fd." << fd << " occur error." << std::endl;
    }
}

void listenerCb(struct evconnlistener *listener, 
        evutil_socket_t fd, struct sockaddr *addr, int addrLen, void *arg)
{
    event_base *base = reinterpret_cast<event_base*>(arg);
    event *ev = event_new(base, fd, EV_READ | EV_PERSIST, clientReadCb, event_self_cbarg());
    //timeval tv;
    event_add(ev, NULL);
}

int main(int argc, char* argv[])
{
    std::cout << argc << std::endl;
    if (argc!=1 && argc!=3) {
        std::cout << "run as follow.\n\t./eventSer bindhost bindport\n\t./eventSer" << std::endl;
        return -1;
    }
    bool userAddr = (argc==3 ? true : false);

    sockaddr_in bindAddr;
    bindAddr.sin_family = AF_INET;
    if (userAddr) {
        bindAddr.sin_addr.s_addr = inet_addr(argv[1]);
        bindAddr.sin_port = htons(std::atoi(argv[2]));
    }
    else {
        bindAddr.sin_addr.s_addr = htonl(INADDR_ANY);
        bindAddr.sin_port = htons(8989);
    }
    int bindAddrLen = sizeof(bindAddr);
    unsigned int listenerFlags = LEV_OPT_CLOSE_ON_EXEC | LEV_OPT_REUSEABLE;

    /* Init the base and listener. */
    event_base *base = event_base_new();

    struct evconnlistener *listener = evconnlistener_new_bind(base, listenerCb, (void*)base,
            listenerFlags, 1, (struct sockaddr*)&bindAddr, bindAddrLen);

    
    /* Run the base loop. */
    event_base_dispatch(base);

    /* Release the listener, base. */
    evconnlistener_free(listener);
    event_base_free(base);

    return 0;
}
