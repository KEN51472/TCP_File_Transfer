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

    virtual int open();

    virtual int write(char *buf, int size);

    virtual int destroy();

private:
};

#endif