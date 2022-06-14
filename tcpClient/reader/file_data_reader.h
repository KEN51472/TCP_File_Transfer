#ifndef FILE_DATA_READER_H
#define FILE_DATA_READER_H

#include "data_reader.h"
#include "wrapper.h"

class File_Data_Reader : public Data_Reader 
{
public:   
    File_Data_Reader() 
    {

    };

    ~File_Data_Reader() 
    {

    };

    virtual int read_data(int fd,char* buf,char file_name);

    virtual int open_data(char* file_path,char* file_name,char* file_info);

private:
};

#endif 

