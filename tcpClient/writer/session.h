#ifndef SESSION_H
#define SESSION_H

#include <unistd.h>
#include <iostream>

using namespace std;

class Session
{
public:   
    Session(int port, const string &address):serv_port_(port), serv_addr_(address){};

    ~Session()
    {

    };

    int open();
    int write(char *buf,int size);
    int destroy();

private:
    int sock_;
    int serv_port_;
    string serv_addr_;
};

#endif