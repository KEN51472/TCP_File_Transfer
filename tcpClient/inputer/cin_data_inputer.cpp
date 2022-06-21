#include "cin_data_inputer.h"

using namespace std;

string Cin_Data_Inputer::get_info()
{
    string file_path(128,0);
    cout << "Please enter the path of the file to be transferred: " << endl;
    cin >> file_path;
    return file_path;
}