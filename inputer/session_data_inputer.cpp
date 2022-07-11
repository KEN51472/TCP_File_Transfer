#include "session_data_inputer.h"

#define CHECK(p)                            \
do {                                         \
    if (!p) {                                \
        cout << p <<" null ptr" << endl;    \
        return -1;                          \
    }                                       \
} while(0) 

int Session_Data_Inputer::init()
{
    if (ss_.init() < 0) {
        cout << "Inputer init error...\t"
             << "errno : " << errno << endl;
        return -1;
    }

    return 0;
}

any Session_Data_Inputer::start()
{   
    int ret = ss_.start();
    if (ret < 0) {
        cout << "Reader init error...\t"
             << "errno : " << errno << endl;
        return -1;
    }
    
    IO_Session *is = new IO_Session(ret);
    CHECK(is);
    any a = is;
    return a;
}