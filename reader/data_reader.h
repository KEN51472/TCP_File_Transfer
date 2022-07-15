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

    virtual int open(bool type);
    virtual string get_name(char *buf) = 0;
    virtual int get_size() = 0;
    virtual int read(char *buf, any a, int size) = 0;
    virtual void set(const string &file_path, const string &json_path);
    virtual int destroy();
};

#endif