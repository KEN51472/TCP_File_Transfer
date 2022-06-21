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

    int write(char *buf, int rn, int size);

    int write_info(char *file_path, char *buf ,int size);

    int destroy();
    

private:
    int left;
    int uploaded;
    Session s;
};

#endif