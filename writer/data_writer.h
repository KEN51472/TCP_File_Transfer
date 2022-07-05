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

    virtual int set(const string &address);
    virtual int open(const string &name);
    virtual int write(char *buf, int size);
    virtual int destroy(any a);
};

#endif