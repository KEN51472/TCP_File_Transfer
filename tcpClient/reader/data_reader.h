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

    virtual char *init_buf();

    virtual int read_data(int fd, char *file_path, char *buf);

    virtual int open_data(char *file_path);

private:
};

#endif