#ifndef CLIENT_SESSION_H
#define CLIENT_SESSION_H

#include <unistd.h>
#include <arpa/inet.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <iostream>

using namespace std;

#define SERV_PORT 9877

class Client_Session
{
public:
    Client_Session()
    {

    };

    ~Client_Session()
    {

    };

    int set(const string &address);
    int open();
    int write(char *buf, int size);
    int destroy();

private:
    int sock_;
    string serv_addr_;
};

#endif