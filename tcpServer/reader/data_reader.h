#ifndef DATA_READER_H
#define DATA_READER_H

#include <iostream>
#include <boost/any.hpp>
#include <string>

using namespace boost;
using namespace std;

class Data_Reader
{
public:
    Data_Reader()
    {

    };

    virtual ~Data_Reader()
    {

    };

    virtual int init();
    virtual int start();
    virtual string get_name(char *buf);
    virtual int get_size(char *buf);
    virtual int read(char *buf, any a, int size);
};

#endif