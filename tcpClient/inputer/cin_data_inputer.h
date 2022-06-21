#ifndef CIN_DATA_INPUTER_H
#define CIN_DATA_INPUTER_H

#include "data_inputer.h"
#include <string>

class Cin_Data_Inputer : public Data_Inputer
{
public:
    Cin_Data_Inputer()
    {

    };

    ~Cin_Data_Inputer()
    {

    };

    string get_info();

};

#endif