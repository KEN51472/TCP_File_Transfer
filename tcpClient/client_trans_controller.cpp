#include "client_trans_controller.h"

int Client_Trans_Controller::init()
{   
    data_path = inputer->get_data();
    reader->open_data(data_path); 
    reader->get_data_size();
    data_name = reader->get_data_name(data_path);
    buf = reader->init_buf();
    reader->read_data(data_path, buf);
    return 0;
}

int Client_Trans_Controller::start()
{
    writer->link();
    writer->write_info(buf,data_name);
    writer->write_data(buf);
    return 0;
}
