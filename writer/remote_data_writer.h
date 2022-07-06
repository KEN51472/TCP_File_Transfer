#ifndef REMOTE_DATA_WRITER_H
#define REMOTE_DATA_WRITER_H

#include <errno.h>
#include <unistd.h>
#include "data_writer.h"
#include "client_session.h"


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
    int open(const string &name, any a);
    int write(char *buf, any a, int size);
    int destroy(any a);  

private:
    int finished_;
    Session s_;
};

#endif