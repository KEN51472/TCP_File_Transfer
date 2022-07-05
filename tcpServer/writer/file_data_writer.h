#ifndef FILE_DATA_WRITER_H
#define FILE_DATA_WRITER_H

#include <errno.h>
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include "data_writer.h"
#include "io_session.h"

using namespace std;

class File_Data_Writer : public Data_Writer
{
public:
    File_Data_Writer()
    {

    };

    ~File_Data_Writer()
    {

    };

    int set(int file_size, Io_Session *is);
    int open(const string &name);
    int write(char *buf, int size);
    int destroy(any a);

private:
    int fd_;
};

#endif