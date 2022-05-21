#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstdio>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>

#define SERV_PORT 9877
#define LISTENQ 1024
#define	SA	struct sockaddr

int main(int argc, char **argv)
{
    int listenfd, connfd;
    pid_t childpid;
    socklen_t clilen;
    struct sockaddr_in cliaddr, servaddr;

    //创建套接口，捆绑服务器的端口
    listenfd = socket(AF_INET, SOCK_STREAM, 0); //创建一个套接口
    printf("创建套接口成功...\n");
    memset(&servaddr, 0,sizeof(servaddr)); //将内存块的前sizeof(servaddr)个字节清零
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);
    bind((listenfd), (SA *)&servaddr, sizeof(servaddr)); //套接口绑定提供服务的端口
    printf("套接口绑定端口成功...\n");
    listen(listenfd, LISTENQ); //指示套接口进入监听连接请求状态
    printf("套接口进入监听成功...\n");
    printf("等待完成客户连接...\n");
    for (;;)
    { //等待完成客户连接
        clilen = sizeof(cliaddr);
        connfd = accept(listenfd, (SA *)&cliaddr, &clilen); //接受连接请求，进入连接状态
        printf("连接成功...\n");

        //并发服务器
        if ((childpid = fork()) == 0)
        {
            close(listenfd);
            char file_len[16] = {0};   //文件长度
            char file_name[128] = {0}; //文件名称
            char buf[1024] = {0};      //数据缓冲区
            char filepath[2048] = {0};
            //读取文件大小和文件名称
            read(connfd, buf, sizeof(buf));                                //将accept中的所有内容读取到buf指针所指的内存中
            strncpy(file_len, buf, sizeof(file_len));                      //取出文件大小(复制字符串前n个字符)
            strncpy(file_name, buf + sizeof(file_len), sizeof(file_name)); //取出文件名称

            printf("准备接收文件...... 文件名:[%s] 大小:[%s] \n", file_name, file_len);

            //新的文件名
            sprintf(buf, "recv-%s", file_name);                   //将格式化数据写入字符串
            sprintf(filepath, "/home/code/tcp_download/%s", buf); //指定文件接收位置
            //创建新文件
            int fd = open(filepath, O_RDWR | O_CREAT | O_TRUNC, 0666);
            int size = atoi(file_len); //文件大小
            int write_len = 0;         //记录已写入的字节数

            //接收文件
            while (1)
            {
                bzero(buf, 1024); //清空buf内存块方便后续写入

                //接收文件数据
                int ret = read(connfd, buf, sizeof(buf));
                if (ret <= 0)
                {
                    printf("\n [recv-%s] 文件传输完毕...\n", file_name);
                    break;
                }

                //将数据写入文件
                write(fd, buf, ret);

                write_len += ret; //记录写入的字节数

                //动态的输出接收进度
                printf("传输中 %.2f%% \n", (float)write_len / size * 100);
            }
            exit(0);
        }
        close(connfd);
    }
}