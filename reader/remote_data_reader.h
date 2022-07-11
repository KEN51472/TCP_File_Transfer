#ifndef REMOTE_DATA_READER_H
#define REMOTE_DATA_READER_H

#include <errno.h>
#include <unistd.h>
#include "data_reader.h"
#include "io_session.h"

class Remote_Data_Reader : public Data_Reader
{
public:
    Remote_Data_Reader()
    {

    };

    ~Remote_Data_Reader()
    {

    };

    int read(char *buf, any a, int size);
    bool get_info(char *buf, int a, int b, string &info);
    
private:
    int size_;
};
#endif