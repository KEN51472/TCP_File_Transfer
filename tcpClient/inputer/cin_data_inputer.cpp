#include "cin_data_inputer.h"
#include <iostream>
#include "string.h"
using namespace std;

char *Cin_Data_Inputer::get_info(char *file_path)
{
    memset(file_path, 0, 128);
    cout << "Please enter the path of the file to be transferred: " << endl;
    cin >> file_path;
    return file_path;
}