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
#include <functional> 

using callback_t = std::function<void(int, std::string, std::string, uint16_t)>;

class UdpServer
{
public:
    // 定义错误码规范
    enum ErrorCode {
        SOCKET_ERR = 1,
        BIND_ERR 
    };
    UdpServer(uint16_t port) :_port(port), _sockfd(-1) {}
    ~UdpServer() {
        if(_sockfd >= 0) close(_sockfd);
    }
    // 初始化 socket + bind
    void init() {
        _sockfd = socket(AF_INET, SOCK_DGRAM, 0);
        if(_sockfd == -1) {
            perror("socket error");
            exit(SOCKET_ERR);
        }

        struct sockaddr_in local;
        memset(&local, 0, sizeof(local));
        local.sin_family = AF_INET;
        local.sin_port = htons(_port);
        local.sin_addr.s_addr = htonl(INADDR_ANY);

        if(bind(_sockfd, (struct sockaddr*)&local, sizeof(local)) == -1) {
            perror("bind error");
            exit(BIND_ERR);
        }
        std::cout << "Server init success on port: " << _port << std::endl;
    }
    // 启动服务：死循环 + 回调
    void start(callback_t cb) {
        char buffer[1024];
        while(true) {
            struct sockaddr_in peer;
            socklen_t len = sizeof(peer);
            ssize_t s = recvfrom(_sockfd, buffer, sizeof(buffer) - 1, 0, (struct sockaddr*)&peer, &len);
            if(s > 0) {
                buffer[s] = 0;
                std::string msg = buffer;
                std::string client_ip = inet_ntoa(peer.sin_addr);
                uint16_t client_port = ntohs(peer.sin_port);
                // 调用回调函数处理业务
                cb(_sockfd, msg, client_ip, client_port);
            }
        }
    }
private:
    uint16_t _port;
    int _sockfd;
};