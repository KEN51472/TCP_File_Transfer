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

    int open_data(char *file_path);

    int read_data(char *file_path, char *buf);

    int get_data_size();

    char *get_data_name(char *file_path);

    char *init_buf();

    int destroy();

private:
    int fd = 0;
    int len = 0;
    char file_name[128] = {0};
};

#endif
