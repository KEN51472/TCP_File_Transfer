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

    virtual char *init_buf();

    virtual int read_data(int fd, char *file_path, char *buf);

    virtual int open_data(char *file_path);
    
private:
    int fd = 0;
    char file_name[128] = {0};
    int len = 0;
};

#endif
