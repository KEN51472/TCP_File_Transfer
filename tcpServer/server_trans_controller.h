#ifndef SERVER_TRANS_CONTROLLER_H
#define SERVER_TRANS_CONTROLLER_H

#include <thread>
#include <unistd.h>
#include <vector>
#include "data_reader.h"
#include "data_writer.h"

#define BUFFER_SIZE 8192
#define INFO_SIZE   1024

struct data_info
{
    int sock;
    int size;
    int sent;
    int fd;
};

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
    int trans(vector<data_info> &v_, int i);
    
private:
    Data_Reader *reader_;
    Data_Writer *writer_;
    vector<data_info> v_;
};

#endif