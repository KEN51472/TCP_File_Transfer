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

    virtual int write_data(char *buf);

    virtual int write_info(char *buf,char *file_name);

private:
};

#endif