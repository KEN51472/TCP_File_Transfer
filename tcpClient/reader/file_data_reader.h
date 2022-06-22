#ifndef FILE_DATA_READER_H
#define FILE_DATA_READER_H

#include <errno.h>
#include <fcntl.h>
#include <iostream>
#include <unistd.h>
#include <string.h>
#include "data_reader.h"

using namespace std;

class File_Data_Reader : public Data_Reader
{
public:
    File_Data_Reader()
    {

    };

    ~File_Data_Reader()
    {
       
    };

    int open();
    int get_size();
    int read_info(char *buf);
    int read(char *buf);
    int set(string &file_path);
    int destroy();

private:
    string path_;
    int fd_ = 0;
    int size_ = 0;
};

#endif
