#ifndef DATA_WRITER_H
#define DATA_WRITER_H

#include <string>
#include <iostream>

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

    virtual int write(int fd, char *buf, int size);
};

#endif