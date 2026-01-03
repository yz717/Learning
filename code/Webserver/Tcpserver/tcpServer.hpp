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

// 把 IO 处理逻辑封装成函数，方便复用
void ServiceIO(int service_sock, std::string clientIp, uint16_t clientPort) {
    while (true) {
        char buffer[1024];
        memset(buffer, 0, sizeof(buffer));
        ssize_t s = read(service_sock, buffer, sizeof(buffer) - 1);
        if (s > 0) {
            std::cout << "[" << clientIp << ":" << clientPort << "] Client say# " << buffer << std::endl;
            std::string resp = "Server Echo: " + std::string(buffer);
            write(service_sock, resp.c_str(), resp.size());
        } else if (s == 0) {
            std::cout << "[" << clientIp << ":" << clientPort << "] Client quit..." << std::endl;
            break;
        } else {
            perror("read");
            break;
        }
    }
    close(service_sock); // 关闭连接
}


class TcpServer{
public:
    TcpServer(int port) : port_(port), listen_sock_(-1) {}
    ~TcpServer(){
        if(listen_sock_ >= 0) close(listen_sock_);
    }
    void Init() {
        // 1. 创建socket
        listen_sock_ = socket(AF_INET, SOCK_STREAM, 0);
        CHECK_RET(listen_sock_, "socket");

        // 2.  端口复用
        int opt = 1;
        setsockopt(listen_sock_, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

        // 3. 绑定
        struct sockaddr_in local;
        memset(&local, 0, sizeof(local));
        local.sin_family = AF_INET;
        local.sin_port = htons(port_);
        local.sin_addr.s_addr = htonl(INADDR_ANY);

        int ret = bind(listen_sock_, (struct sockaddr*)&local, sizeof(local));
        CHECK_RET(ret, "bind");

        // 4. 监听
        ret = listen(listen_sock_, 5);
        CHECK_RET(ret, "listen");
        std::cout << "Server is listening on port: " << port_ << "..." << std::endl;
    }

    void Loop() {
        // 5. accept
        while(true) {
            struct sockaddr_in client_addr;
            socklen_t len = sizeof(client_addr);
            int service_sock = accept(listen_sock_, (struct sockaddr*)&client_addr, &len);
            CHECK_RET(service_sock, "accept");

            // 获取客户端信息
            char clientIpBuf[INET_ADDRSTRLEN];
            if(!inet_ntop(AF_INET, &client_addr.sin_addr, clientIpBuf, sizeof(clientIpBuf))) perror("inet_ntop");
            uint16_t clientPort = ntohs(client_addr.sin_port);

            std::cout << "New connection: [" << clientIpBuf << ":" << clientPort << "]" << std::endl;
            // 线程版本
            std::thread t(ServiceIO, service_sock, (std::string)clientIpBuf, clientPort);
            t.detach();
        }

    }
private:
    int port_;
    int listen_sock_;
};