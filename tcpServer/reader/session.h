#ifndef SESSION_H
#define SESSION_H

#include <unistd.h>
#include <arpa/inet.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <thread>
#include <iostream>

using namespace std;

#define SERV_PORT 9877
#define LISTENQ 1024
#define SA struct sockaddr

class Session
{
public:
    Session()
    {

    };

    ~Session()
    {

    };

    int init();
    int start();
    int destroy();

private:
    int sock_;
    int accept_sock_;
    socklen_t clilen;
    struct sockaddr_in cliaddr;
    struct sockaddr_in servaddr;
};

#endif