#ifndef FILE_DATA_READER_H
#define FILE_DATA_READER_H

#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include "data_reader.h"
#include "io.hpp"

using namespace ciere::json;

#define BUFFER_SIZE 8192
#define INFO_SIZE   1024

class File_Data_Reader : public Data_Reader
{
public:
    File_Data_Reader()
    {

    };

    virtual ~File_Data_Reader()
    {
       
    };

    int open(bool type);
    int get_size();
    string get_name(char *buf);
    int read(char *buf, any a, int size);
    void set(const string &file_path, const string &json_path);
    int destroy();

private:
    string json_path_;
    string file_path_;
    int fd_;
    int jfd_;
    value v_;
};

#endif
