#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <wrapper.h>

char file_info[128] = {0};
char buf[65536] = {0};
char file_path[128] = {0};
char file_name[128] = {0};

int open_data() {
    int fd;
    fd = open(file_path, O_RDWR);
    if (fd == -1) {
        cout << "Open error...\t"
             << "errno : " << errno << endl;
        return -1;
    }
    DesWrapper fd_wrapper(fd);
    strncpy(file_name, basename(file_path), sizeof(file_name));
    cout << "Open [" << file_path
         << "] success... \tdescriptor : " << fd_wrapper.get() << endl;

    int len = lseek(fd_wrapper.get(), 0, SEEK_END);
    lseek(fd, 0, SEEK_SET);
    cout << "file_size : " << len << endl;
    sprintf(file_info, "%d", len);
    strcpy(file_info + 16, file_name);
}

int start_read(DesWrapper fd_wrapper) {
    memset(buf, 0, sizeof(buf));
    int rn = read(fd_wrapper.get(), buf, sizeof(buf));
    if (rn == 0) {
        cout << "Transfer [" << file_name << "] success..." << endl;
        // break;
    }
    if (rn < 0) {
        cout << "Function read error...\t"
             << "errno : " << errno << endl;
        return -1;
    }
}