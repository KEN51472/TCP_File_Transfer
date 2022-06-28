#ifndef FILE_DATA_WRITER_H
#define FILE_DATA_WRITER_H

#include <errno.h>
#include <iostream>
#include <unistd.h>
#include "data_writer.h"

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

    int write(int fd, char *buf, int size);
};
#endif