#ifndef FILE_DATA_READER_H
#define FILE_DATA_READER_H

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

    int open_data(char *file_path, int size);

    int read_data(char *buf);

    int destroy();

private:
    int fd = 0;
};

#endif
