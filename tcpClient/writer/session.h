#ifndef SESSION_H
#define SESSION_H

#include <unistd.h>
#include <iostream>
using namespace std;

class Session
{
public:
    Session()
    {

    };

    ~Session()
    {

    };

    int tcp_link();

private:
    int ret, sock, fd;
};

#endif