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
    virtual string get_name(char *buf);
    virtual int get_size() = 0;
    virtual bool set_info(char *buf);
    virtual int read(char *buf, any a, int size) = 0;
    virtual void set_path(const string &file_path);
    virtual int destroy();
};

#endif