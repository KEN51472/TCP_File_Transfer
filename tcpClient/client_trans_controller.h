#ifndef CLIENT_TRANS_CONTROLLER_H
#define CLIENT_TRANS_CONTROLLER_H

#include "data_inputer.h"
#include "data_reader.h"
#include "data_writer.h"

class Client_Trans_Controller
{
public:
    Client_Trans_Controller(Data_Inputer *i_impl, 
                            Data_Reader *r_impl, 
                            Data_Writer *w_impl):
                            inputer_(i_impl), 
                            reader_(r_impl), 
                            writer_(w_impl){}

    ~Client_Trans_Controller()
    {

    }

    int init();
    int start();
    int destroy();

private:
    int size_;
    Data_Inputer *inputer_;
    Data_Reader *reader_;
    Data_Writer *writer_;
};

#endif