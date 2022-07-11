#ifndef DATA_WRITER_H
#define DATA_WRITER_H

#include <string>
#include <iostream>
#include <boost/any.hpp>

using namespace boost;
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

    virtual void set(const string &address);
    virtual int open(const string &name, any a) = 0;
    virtual int write(char *buf, any a, int size) = 0;
    virtual int destroy(any a) = 0;
};

#endif