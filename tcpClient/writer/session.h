#ifndef SESSION_H
#define SESSION_H

#include <unistd.h>
#include <arpa/inet.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <iostream>

using namespace std;

#define SERV_PORT 9877

class Session
{
public:
    Session()
    {

    };

    ~Session()
    {

    };

    int set(const string &address);
    int open();
    int write(char *buf,int size);
    int destroy();

private:
    int sock_;
    string serv_addr_;
};

#endif