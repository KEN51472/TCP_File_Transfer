#ifndef DATA_READER_H
#define DATA_READER_H

#include <iostream>
#include <string>
#include <boost/any.hpp>

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

    virtual int open();
    virtual string get_info(char *buf, int a, int b);
    virtual int read(char *buf, any a, int size);
    virtual int set(const string &file_path);
    virtual int destroy();
};

#endif