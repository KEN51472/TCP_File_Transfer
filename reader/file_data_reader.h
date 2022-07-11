#ifndef FILE_DATA_READER_H
#define FILE_DATA_READER_H

#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include "data_reader.h"

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
    bool get_info(char *buf, int a, int b, string &info);
    int read(char *buf, any a, int size);
    void set(const string &file_path);
    int destroy();

private:
    string path_;
    int fd_;
    int size_;
};

#endif
