#ifndef DATA_READER_H
#define DATA_READER_H

#include <iostream>
#include <string>
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
    virtual int get_size();
    virtual int read_info(char *buf);
    virtual int read(char *buf);
    virtual int set(string &file_path);
    virtual int destroy();
};

#endif