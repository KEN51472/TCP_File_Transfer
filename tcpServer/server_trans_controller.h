#ifndef SERVER_TRANS_CONTROLLER_H
#define SERVER_TRANS_CONTROLLER_H

#include <thread>
#include "data_reader.h"
#include "data_writer.h"

class Server_Trans_Controller
{
public:
    Server_Trans_Controller(Data_Reader *r_impl, 
                            Data_Writer *w_impl):
                            reader_(r_impl), 
                            writer_(w_impl){}

    ~Server_Trans_Controller()
    {

    }

    int init();
    int start();
    int trans(int sock);
    
private:
    Data_Reader *reader_;
    Data_Writer *writer_;
    int size;
};

#endif