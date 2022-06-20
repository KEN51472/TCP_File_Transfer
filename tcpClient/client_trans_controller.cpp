#include "client_trans_controller.h"

int Client_Trans_Controller::init()
{
    data_path = inputer->get_info();
    reader->open_data(data_path);
    data_size = reader->get_data_size();
    data_name = reader->get_data_name(data_path);
    buf = reader->init_buf();
    reader->read_data(data_path, buf);
    return 0;
}

int Client_Trans_Controller::start()
{
    writer->link();
    writer->write_info(buf, data_name, data_size);
    writer->write_data(buf, data_size);
    return 0;
}

int Client_Trans_Controller::destroy()
{
    reader->destroy();
    writer->destroy();
    return 0;
}