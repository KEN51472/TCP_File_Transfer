#ifndef REMOTE_DATA_WRITER_H
#define REMOTE_DATA_WRITER_H

#include <memory>
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

    int set(const string &address);
    int open();
    int write(char *buf, int size);
    int destroy();  

private:
    int finished_;
    Session s_;
};

#endif