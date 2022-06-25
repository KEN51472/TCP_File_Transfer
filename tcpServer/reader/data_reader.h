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
    virtual int init();
    virtual int start();
    virtual string get_name(char *buf);
    virtual int get_size(char *buf);
    virtual int read(char *buf, int sock, int size);
};

#endif