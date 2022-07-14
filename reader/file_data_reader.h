#ifndef FILE_DATA_READER_H
#define FILE_DATA_READER_H

#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include "data_reader.h"
#include "io.hpp"

using namespace ciere::json;

class File_Data_Reader : public Data_Reader
{
public:
    File_Data_Reader()
    {

    };

    virtual ~File_Data_Reader()
    {
       
    };

    int open();
    int get_size();
    bool set_info(char *buf);
    int read(char *buf, any a, int size);
    void set_path(const string &file_path);
    int destroy();

private:
    string path_;
    int fd_;
    int size_;
};

#endif
