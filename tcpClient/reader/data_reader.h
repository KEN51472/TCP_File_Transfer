#ifndef DATA_READER_H
#define DATA_READER_H

#include "wrapper.h"

class Data_Reader 
{
public:
    Data_Reader()
    {

    };

    ~Data_Reader()
    {

    };
    
    virtual int read_data(int fd,char* buf,char file_name);

    virtual int open_data(char* file_path,char* file_name,char* file_info);

private:
};

#endif