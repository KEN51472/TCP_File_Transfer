#ifndef SERVER_TRANS_CONTROLLER_H
#define SERVER_TRANS_CONTROLLER_H

#include <thread>
#include <unistd.h>
#include <vector>
#include "data_reader.h"
#include "data_writer.h"
#include "data_inputer.h"
#include "server_session.h"
#include "io_session.h"

#define BUFFER_SIZE 8192
#define INFO_SIZE   1024

using namespace boost;

class Server_Trans_Controller
{
public:
    Server_Trans_Controller(Data_Inputer *i_impl,
                            Data_Reader *r_impl, 
                            Data_Writer *w_impl):
                            inputer_(i_impl),
                            reader_(r_impl), 
                            writer_(w_impl){}

    ~Server_Trans_Controller()
    {

    }

    int init();
    int start();
    int trans(Io_Session *io);
    
private:
    Data_Inputer *inputer_;
    Data_Reader *reader_;
    Data_Writer *writer_;

};

#endif