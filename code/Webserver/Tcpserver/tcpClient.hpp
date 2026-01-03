#pragma once
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <cstring>
#include <thread>
#include <string>
// 错误处理宏
#define CHECK_RET(exp, msg) \
    do { \
        if(exp < 0) { \
            perror(msg); \
            exit(1); \
        } \
    } while(0)


class TcpClient{
public:
    TcpClient(std::string ip, uint16_t port) 
        : server_ip_(ip), server_port_(port), sockfd_(-1) {}

    ~TcpClient() {
        if (sockfd_ >= 0) close(sockfd_);
    }

    // 连接服务器
    bool Connect() {
        sockfd_ = socket(AF_INET, SOCK_STREAM, 0);
        CHECK_RET(sockfd_, "socket");

        struct sockaddr_in server;
        memset(&server, 0, sizeof(server));
        server.sin_family = AF_INET;
        server.sin_port = htons(server_port_);
        int ret = inet_pton(AF_INET, server_ip_.c_str(), &server.sin_addr);
        if(ret != 1) {
            perror("inet_pton");
            exit(1);
        }

        int n = connect(sockfd_, (struct sockaddr*)&server, sizeof(server));
        if (n < 0) {
            perror("connect");
            close(sockfd_); // 连接失败记得关闭 socket
            return false;
        }
        return true;
    }

    // 发送请求并获取响应
    void Request() {
        while (true) {
            std::cout << "Please Enter# ";
            std::string msg;
            std::getline(std::cin, msg);

            if (msg == "quit") break;

            // 发送数据
            ssize_t n = write(sockfd_, msg.c_str(), msg.size());
            if (n < 0) {
                perror("write");
                break;
            }

            // 读取响应
            char buffer[1024];
            memset(buffer, 0, sizeof(buffer));
            n = read(sockfd_, buffer, sizeof(buffer) - 1);
            if (n > 0) {
                std::cout <<  buffer << std::endl;
            } else if (n == 0) {
                std::cout << "Server closed connection." << std::endl;
                break;
            } else {
                perror("read");
                break;
            }
        }
    }

private:
    std::string server_ip_;
    uint16_t server_port_;
    int sockfd_;
};