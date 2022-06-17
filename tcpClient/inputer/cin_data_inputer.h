#ifndef CIN_DATA_INPUTER_H
#define CIN_DATA_INPUTER_H

#include "data_inputer.h"

class Cin_Data_Inputer : public Data_Inputer 
{
public:
    Cin_Data_Inputer() 
    {

    };

    ~Cin_Data_Inputer() 
    {

    };

    char* get_data()  ;

private:
    char file_path[128] = {0};
    
};

#endif 