#ifndef SESSION_DATA_INPUTER_H
#define SESSION_DATA_INPUTER_H

#include "server_session.h"
#include "io_session.h"
#include "data_inputer.h"

class Session_Data_Inputer:public Data_Inputer
{
public:
    Session_Data_Inputer()
    {

    };

    ~Session_Data_Inputer()
    {

    };

    int init();
    variant<std::monostate> start();

private:
    Server_Session ss_;
};

#endif