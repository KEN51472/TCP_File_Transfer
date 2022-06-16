#include "client_trans_controller.h"

int Client_Trans_Controller::init()
{
    data_path = inputer->get_data();
    data_fd = reader->open_data(data_path); 
    data_size = reader->get_data_size(data_fd);
    data_name = reader->get_data_name(data_path);
    buf = reader->init_buf(data_size);
    reader->read_data(data_fd, data_path, buf);
    return 0;
}

int Client_Trans_Controller::start()
{
    sock = writer->link();
    writer->write_info(sock,data_size,data_name);
    writer->write_data(sock,buf,data_size);
    return 0;
}
