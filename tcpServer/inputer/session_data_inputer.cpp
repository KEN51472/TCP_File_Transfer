#include "session_data_inputer.h"

int Session_Data_Inputer::init()
{
    if (ss_.init() < 0) {
        cout << "Reader init error...\t"
             << "errno : " << errno << endl;
        return -1;
    }

    return 0;
}

variant<int, Io_Session *> Session_Data_Inputer::start()
{   
    int ret = ss_.start();
    if (ret < 0) {
        cout << "Reader init error...\t"
             << "errno : " << errno << endl;
        return -1;
    }
    
    Io_Session *is = new Io_Session(ret);
    variant<int, Io_Session *> var;
    var = is;
    return var;
}