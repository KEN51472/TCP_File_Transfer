#include "server_trans_controller.h"
#include "remote_data_reader.h"
#include "file_data_writer.h"
#include "data_reader.h"
#include "data_writer.h"

int main()
{
    Data_Reader *r_impl = new Remote_Data_Reader;
    Data_Writer *w_impl = new File_Data_Writer;
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