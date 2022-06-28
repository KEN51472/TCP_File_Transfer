#include "server_trans_controller.h"
#include "remote_data_reader.h"
#include "file_data_writer.h"
#include "data_reader.h"
#include "data_writer.h"

#define CHECK(p)                            \
do{                                         \
    if(!p) {                                \
        cout << p <<" null ptr" << endl;    \
        return -1;                          \
    }                                       \
}while(0) 

int main()
{
    Data_Reader *r_impl = new Remote_Data_Reader;
    CHECK(r_impl);
    Data_Writer *w_impl = new File_Data_Writer;
    CHECK(w_impl);
    Server_Trans_Controller stc(r_impl, w_impl);
    if (stc.init() < 0) {
        cout << "Server using init error...\t" << "errno : " << errno << endl;
        return -1;
    }

    if (stc.start() < 0) {
        cout << "Server using start error...\t" << "errno : " << errno << endl;
        return -1;
    }
    
    delete r_impl;
    delete w_impl;
}