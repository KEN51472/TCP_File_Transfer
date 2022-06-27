#include "client_trans_controller.h"
#include "cin_data_inputer.h"
#include "file_data_reader.h"
#include "remote_data_writer.h"
#include "data_inputer.h"
#include "data_reader.h"
#include "data_writer.h"

int main()
{
    Data_Inputer *i_impl = new Cin_Data_Inputer;
    Data_Reader *r_impl = new File_Data_Reader;
    Data_Writer *w_impl = new Remote_Data_Writer;
    Client_Trans_Controller ctc(i_impl, r_impl, w_impl);
    if (ctc.init() < 0) {
        cout << "Client using init error...\t" << "errno : " << errno << endl;
        return -1;
    }
    if (ctc.start() < 0) {
        cout << "Client using start error...\t" << "errno : " << errno << endl;
        return -1;
    }
    ctc.destroy();
    delete i_impl;
    delete r_impl;
    delete w_impl;
}