#ifndef SERVER_SESSION_H
#define SERVER_SESSION_H

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

class Server_Session
{
public:
    Server_Session()
    {

    };

    ~Server_Session()
    {

    };

    int init();
    int start();

private:
    int sock_;
};

#endif