#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

using namespace std;


int main(int argc, char *argv[])
{
    if(argc != 3) 
    {
        cout << "Usage: " << argv[0] << " server_ip server_port" << endl;
        return 1;
    }

    string server_ip = argv[1];
    uint16_t server_port = atoi(argv[2]);

    // 1. 创建 socket
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if(sockfd < 0)
    {
        perror("socket");
        return 1;
    }

    // 客户端不需要 bind！操作系统会在第一次发送时自动分配端口
    struct sockaddr_in server;
    bzero(&server, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(server_port); // 填入服务器端口
    server.sin_addr.s_addr = inet_addr(server_ip.c_str()); // 填入服务器IP

    // 3. 主循环：读取键盘 -> 发送
    string message;
    while(true)
    {
        cout << "Please Enter# ";
        getline(cin, message); // 读取一行输入

        if(message == "quit") break;

        // sendto(套接字, 内容, 长度, 0, 目标地址结构体, 结构体大小)
        sendto(sockfd, message.c_str(), message.size(), 0, (struct sockaddr*)&server, sizeof(server));
    }

    close(sockfd);
    return 0;
}