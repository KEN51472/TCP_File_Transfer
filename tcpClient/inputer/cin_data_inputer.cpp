#include "cin_data_inputer.h"
#include <iostream>
using namespace std;

char *Cin_Data_Inputer::get_info()
{
    cout << "Please enter the path of the file to be transferred: " << endl;
    cin >> file_path;
    return file_path;
}