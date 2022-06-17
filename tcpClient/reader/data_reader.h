#ifndef DATA_READER_H
#define DATA_READER_H

class Data_Reader
{
public:
    Data_Reader()
    {

    };

    ~Data_Reader()
    {

    };

    virtual int open_data(char *file_path);

    virtual int read_data(char *file_path, char *buf);
    
    virtual int get_data_size();

    virtual char* get_data_name(char *file_path);

    virtual char* init_buf();

private:
};

#endif