#ifndef DATA_WRITER_H
#define DATA_WRITER_H

#include <string>
#include <iostream>
#include "io_session.h"

using namespace std;

class Data_Writer
{
public:
    Data_Writer()
    {

    };

    virtual ~Data_Writer()
    {

    };

    virtual int open(const string &name);
    virtual int write(char *buf, int size);
    virtual int destroy(Io_Session *is);
    virtual int set(int file_size, Io_Session *is);
};

#endif