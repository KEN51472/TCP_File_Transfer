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

variant<std::monostate> Session_Data_Inputer::start()
{   
    int ret = ss_.start();
    if (ret < 0) {
        cout << "Reader init error...\t"
             << "errno : " << errno << endl;
        return -1;
    }
    
    Io_Session *is = new Io_Session(ret);
    variant<std::monostate> var;
    var = is;
    cout << "new session"<< endl;
    return var;
}