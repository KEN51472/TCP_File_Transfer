#ifndef DATA_WRITER_H
#define DATA_WRITER_H

class Data_Writer 
{
public:
    Data_Writer()
    {

    };

    ~Data_Writer()
    {

    };
    
    virtual int link();

    virtual int write_data(int sock, char *buf, int data_size);

    virtual int write_info(int sock, int len, char *file_name);

private:
};

#endif