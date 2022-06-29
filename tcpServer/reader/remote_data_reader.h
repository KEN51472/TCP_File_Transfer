#ifndef REMOTE_DATA_READER_H
#define REMOTE_DATA_READER_H

#include <errno.h>
#include <fcntl.h>
#include <iostream>
#include <unistd.h>
#include <string>
#include "data_reader.h"
#include "session.h"

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

    int init();
    int start();
    int open();
    int read(char *buf, int sock, int b_size ,int sent ,int size);
    string get_name(char *buf);
    int get_size(char *buf);
    int destroy();
    
private:
    Session s_;
    string name_;
    int size_;
    int fd_;
};
#endif