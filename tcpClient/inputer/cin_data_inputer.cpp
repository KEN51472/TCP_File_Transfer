#include "cin_data_inputer.h"

using namespace std;

string Cin_Data_Inputer::get_address()
{
    string serv_addr = "";
    cout << "Please enter the server address: " << endl;
    cin >> serv_addr;
    return serv_addr;
}

string Cin_Data_Inputer::get_path()
{
    string file_path = "";
    cout << "Please enter the path of the file to be transferred: " << endl;
    cin >> file_path;
    return file_path;
}