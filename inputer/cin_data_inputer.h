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

    virtual ~Cin_Data_Inputer()
    {

    };

    bool get_address(string &address);
    bool get_path(string &path);
    bool get_json(string &path);
};

#endif