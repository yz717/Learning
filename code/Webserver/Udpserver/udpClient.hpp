#pragma once
#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

class UdpClient
{
public:
    UdpClient(std::string server_ip, uint16_t server_port) 
        : _server_ip(server_ip), _server_port(server_port), _sockfd(-1)
    {}

    ~UdpClient()
    {
        if (_sockfd >= 0) close(_sockfd);
    }

    void init()
    {
        // 1. 创建 Socket
        _sockfd = socket(AF_INET, SOCK_DGRAM, 0);
        if (_sockfd < 0)
        {
            perror("socket error");
            exit(1);
        }

        // 2. 提前填好服务器的地址信息 
        memset(&_server_addr, 0, sizeof(_server_addr));
        _server_addr.sin_family = AF_INET;
        _server_addr.sin_port = htons(_server_port);
        // string -> uint32_t
        _server_addr.sin_addr.s_addr = inet_addr(_server_ip.c_str());
    }

    // 发送消息接口
    void sendMsg(const std::string &msg)
    {
        // 直接使用成员变量 _server_addr
        sendto(_sockfd, msg.c_str(), msg.size(), 0, 
               (struct sockaddr*)&_server_addr, sizeof(_server_addr));
    }

    // 接收消息接口 (带回显功能)
    std::string recvMsg()
    {
        char buffer[1024];
        // 这里的 temp 用来占位，我们其实知道是谁发的（肯定是服务器）
        struct sockaddr_in temp;
        socklen_t len = sizeof(temp);

        ssize_t s = recvfrom(_sockfd, buffer, sizeof(buffer)-1, 0, 
                             (struct sockaddr*)&temp, &len);
        
        if(s > 0)
        {
            buffer[s] = 0;
            return std::string(buffer);
        }
        return "";
    }

private:
    int _sockfd;
    std::string _server_ip;
    uint16_t _server_port;
    // 关键：把服务器的地址结构体存下来，作为成员变量
    struct sockaddr_in _server_addr; 
};