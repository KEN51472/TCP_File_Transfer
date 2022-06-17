#include "client_trans_controller.h"
#include "cin_data_inputer.h"
#include "file_data_reader.h"
#include "remote_data_writer.h"

int main()
{ 
    Cin_Data_Inputer i_impl;
    File_Data_Reader r_impl; 
    Remote_Data_Writer w_impl;
    Client_Trans_Controller ctc(i_impl,r_impl,w_impl);
    ctc.init();
    ctc.start();
    
}