#include "file_data_reader.h"

int File_Data_Reader::open(string &file_path) 
{   
    path = file_path.c_str();
    fd = ::open(path, O_RDWR);
    if (fd == -1) {
        cout << "Open error...\t" << "errno : " << errno << endl;
        return -1;
    }
    cout << "Open [" << file_path << "] success...  \tfd: " << fd << endl;
    
    return 0;  
}

int File_Data_Reader::get_size()
{
    size = lseek(fd, 0, SEEK_END);
    lseek(fd, 0, SEEK_SET);
    cout << "file_size : " << size << endl;
    return size;
}

int File_Data_Reader::read_info(char *buf)
{   
    memset(buf,0,8192);
    const char *s1=to_string(size).c_str();
    char *s2=const_cast<char*>(s1);
    stpcpy(buf,s2);
    strcpy(buf + 16, basename(path));
    return 0;
}

int File_Data_Reader::read(char *buf) 
{
    memset(buf, 0, 8192);
    int rn = ::read(fd, buf, 8192);
    if (rn < 0) {
        cout << "Function read error...\t" << "errno : " << errno << endl;
        return -1;
    }
    return rn;
}

int File_Data_Reader::destroy() 
{
    if(fd >0) {
        close(fd);
        cout << "fd " << fd << " closed success..." << endl;
    }
    
    return 0;
}
