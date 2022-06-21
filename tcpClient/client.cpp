#include "client_trans_controller.h"
#include "cin_data_inputer.h"
#include "file_data_reader.h"
#include "remote_data_writer.h"
#include "data_inputer.h"
#include "data_reader.h"
#include "data_writer.h"

int main()
{
    char *file_path = new char[128];
    char *buf= new char[8192];
    Data_Inputer *i_impl = new Cin_Data_Inputer;
    Data_Reader *r_impl = new File_Data_Reader;
    Data_Writer *w_impl = new Remote_Data_Writer;
    Client_Trans_Controller ctc(i_impl, r_impl, w_impl);
    ctc.init(file_path);
    ctc.start(file_path, buf);
    ctc.destroy();
    delete file_path;
    delete buf;
}