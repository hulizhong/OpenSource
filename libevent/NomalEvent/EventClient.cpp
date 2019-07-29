/*************************************************************************
	> File Name: EventClient.cpp
	> Author: 
	> Mail: 
	> Created Time: Sat 13 Oct 2018 05:27:58 AM CDT
 ************************************************************************/

#include <iostream>
#include <event2/event.h>
#include <unistd.h> //read
#include <signal.h>
#include <arpa/inet.h>
#include <string.h>
//using namespace std;

#define BUFFER_LEN 128

void sigintCb(evutil_socket_t fd, short what, void *arg)
{
    event_base *base = (event_base*)arg;
    event_base_loopbreak(base);
    //event_base_loopexit(base, timeval*);
}

void readConsoleCb(evutil_socket_t fd, short what, void *arg)
{
    int *ser = (int*)arg;
    char buffer[BUFFER_LEN] = {0};
    int res = read(fd, buffer, sizeof(buffer));
    int res1 = send(*ser, buffer, strlen(buffer), 0);
    if (res == res1) {
        std::cout << "client fd." << *ser << " say:" << buffer;
    }
    else {
        std::cout << "client fd." << *ser << " snd failed." << std::endl;
    }
    //std::cout << buffer << std::endl;
}

//nc ip port
//telent ip port
int main(int argc, char* argv[])
{
    std::cout << argc << std::endl;
    if (argc!=1 && argc!=3) {
        std::cout << "run as follow.\n\t./eventCli serverhost serverport\n\t./eventCli" << std::endl;
        return -1;
    }
    bool userAddr = (argc==3 ? true : false);

    int cli = socket(AF_INET, SOCK_STREAM, 0);
    if (cli == -1) {
        std::cout << "Cant init the socket." << std::endl;
    }
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    if (userAddr) {
        serverAddr.sin_addr.s_addr = inet_addr(argv[1]);
        serverAddr.sin_port = htons(std::atoi(argv[2]));
    }
    else {
        serverAddr.sin_port = inet_addr("127.0.0.1");
        serverAddr.sin_port = htons(8989);
    }
    int serverAddrLen = sizeof(serverAddr);
    int res = connect(cli, (sockaddr*)&serverAddr, serverAddrLen);
    if (res == -1) {
        std::cout << "Cant connect the server." << std::endl;
    }
    
    event_base *base = event_base_new();

    event *ev = event_new(base, STDIN_FILENO, EV_READ|EV_PERSIST, readConsoleCb, (void*)&cli);
    event_add(ev, NULL);
    event *evSigint = evsignal_new(base, SIGINT, sigintCb, (void*)base);
    evsignal_add(evSigint, NULL);

    event_base_dispatch(base);

    std::cout << "ctrl+c break loop." << std::endl;
    event_free(ev);
    event_base_free(base);

    return 0;
}
