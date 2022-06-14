#ifndef REMOTE_DATA_WRITER_H
#define REMOTE_DATA_WRITER_H

#include "wrapper.h"
#include "data_writer.h"

class Remote_Data_Writer 
{
public:
    Remote_Data_Writer()
    {

    };

    ~Remote_Data_Writer()
    {

    };
    
    virtual int tcp_connect();

    virtual int write_data(int sock,char buf[],int left);

private:
};

#endif