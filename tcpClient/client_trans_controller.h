#ifndef CLIENT_TRANS_CONTROLLER_H
#define CLIENT_TRANS_CONTROLLER_H

#include "data_inputer.h"
#include "data_reader.h"
#include "data_writer.h"

class Client_Trans_Controller
{
public:
    Client_Trans_Controller(Data_Inputer *i_impl, Data_Reader *r_impl, Data_Writer *w_impl)
    {
        inputer = i_impl;
        reader = r_impl;
        writer = w_impl;
    }

    ~Client_Trans_Controller()
    {

    }

    int init(char *file_path, int size);
    int start(char *file_path, char *buf, int size);
    int destroy();

private:
    Data_Inputer *inputer;
    Data_Reader *reader;
    Data_Writer *writer;
    int uploaded;
};

#endif