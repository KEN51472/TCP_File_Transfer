#ifndef SESSION_H
#define SESSION_H

#include "remote_data_writer.h"

class Session
{
public:
    Session()
    {

    };

    ~Session()
    {

    };
    
    virtual int link();
    
    virtual int write_data(int sock,char *buf);
    
    // virtual int write_info(int sock);

private:
    int ret, sock, fd;
    char file_info[128] = {0};
};

#endif