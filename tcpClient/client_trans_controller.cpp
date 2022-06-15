#include "client_trans_controller.h"

int Client_Trans_Controller::init()
{
   
    cdi_get = cdi.get_data();
    fdr_open = fdr.open_data(cdi_get); 
    buf = fdr.init_buf();
    fdr.read_data(fdr_open, cdi_get, buf);
    return 0;
}

int Client_Trans_Controller::start()
{
    sock = s.link();
    s.write_data(sock,buf);
    return 0;
}

int Client_Trans_Controller::destroy()
{
    return 0;
}