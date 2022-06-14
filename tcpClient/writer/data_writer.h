#ifndef DATA_WRITER_H
#define DATA_WRITER_H

#include "wrapper.h"

class Data_Writer 
{
public:
    Data_Writer()
    {

    };

    ~Data_Writer()
    {

    };
    
    virtual int tcp_connect();

    virtual int write_data(int sock,char buf[],int left);

private:
};

#endif