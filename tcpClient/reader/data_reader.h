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
    virtual int get_info(char *buf, int size);
    virtual int read(char *buf, int size);
    virtual int set(const string &file_path);
    virtual int destroy();
};

#endif