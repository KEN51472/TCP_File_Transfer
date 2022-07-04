#ifndef REMOTE_DATA_READER_H
#define REMOTE_DATA_READER_H

#include <errno.h>
#include <iostream>
#include <unistd.h>
#include <string.h>
#include "data_reader.h"
#include "io_session.h"

using namespace std;

class Remote_Data_Reader:public Data_Reader
{
public:
    Remote_Data_Reader()
    {

    };
    ~Remote_Data_Reader()
    {

    };

    int open();
    int read(char *buf, Io_Session *is, int size);
    string get_name(char *buf);
    int get_size(char *buf);
    
private:
    int size_;
};
#endif