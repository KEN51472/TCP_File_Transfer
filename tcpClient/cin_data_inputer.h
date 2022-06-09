#include "data_inputer.h"
class Cin_Data_Inputer : public Data_Inputer {
private:
public:
    Cin_Data_Inputer();
    ~Cin_Data_Inputer();
    virtual int get_data();
};
