#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstdio>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define SERV_PORT 9877

int main(int argc, char **argv)
{
    int sockfd;
    struct sockaddr_in servaddr;

    if (argc != 2)
    {
        exit(0);
    }

    //创建套接口，初始化套接口地址结构
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&servaddr, 0,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);
    inet_pton(AF_INET, argv[1], &servaddr.sin_addr); //转换由argv指针所指的字符串，并通过servaddr.sin_addr指针存放二进制结果，成功返回1失败返回0

    //与服务器连接
    connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0; //与服务器建立连接

    char file_path[128] = {0};  //文件路径
    char file_info[2048] = {0}; //文件信息

    char buf[1024] = {0};

    //获取用户输入的文件路径
    printf("请输入需要传输文件路径: ");
    scanf("%s", file_path);

    //从文件路径中获取文件名，如"test/a.txt" ==> "a.txt"
    char file_name[128] = {0};
    strncpy(file_name, basename(file_path), sizeof(file_name));

    //打开文件
    int fd = open(file_path, O_RDWR);
    if (fd == -1)
    {
        printf("打开文件[%s]失败", file_path);
        return -1;
    }

    //计算文件大小
    int len = lseek(fd, 0, SEEK_END);

    //文件光标偏移到文件开始位置
    lseek(fd, 0, SEEK_SET);

    //将文件大小和文件名存放到file_info
    sprintf(file_info, "%d", len);
    strcpy(file_info + 16, file_name);

    // 将需要上传的文件名告诉对方
    write(sockfd, file_info, 144);

    int send_len = 0; //记录发送了多少字节

    while (1)
    {
        memset(buf, 0,sizeof(buf));
        //读取数据
        int ret = read(fd, buf, sizeof(buf));
        if (ret <= 0)
        {
            printf("传输文件[%s] 成功...\n", file_name);
            break;
        }

        //发送数据
        write(sockfd, buf, ret);

        send_len += ret; //统计发送了多少字节

        //上传文件的百分比
        printf("上传中 %.2f%%\n", (float)send_len / len * 100);
    }

    // 关闭文件
    close(fd);

    // str_cli(stdin, sockfd); 

    exit(0);
}