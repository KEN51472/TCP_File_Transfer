#ifndef SESSION_H
#define SESSION_H

#include "wrapper.h"
#include "remote_data_writer.h"

#define SERV_PORT 9877
#define SERV_ADDR "127.0.0.1"

class Session
{
public:
    Session()
    {

    };

    ~Session()
    {

    };
    
    virtual int tcp_connect();

    virtual int write_data(int sock,char buf[],int left);

private:
};

#endif