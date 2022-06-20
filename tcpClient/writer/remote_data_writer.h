#ifndef REMOTE_DATA_WRITER_H
#define REMOTE_DATA_WRITER_H

#include "data_writer.h"
#include "session.h"


class Remote_Data_Writer : public Data_Writer
{
public:
    Remote_Data_Writer()
    {

    };

    ~Remote_Data_Writer()
    {
        
    };

    int link();

    int write_data(char *buf, int len);

    int write_info(char *buf, char *file_name, int len);

    int destroy();
    

private:
    char file_info[128] = {0};
    Session s;
};

#endif