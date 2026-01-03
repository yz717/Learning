#include <iostream>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <strings.h>
#include <string>


using namespace std;

int main(int argc, char* argv[]) {
    // 使用时必须指明端口号
    if(argc != 2) {
        cout << "Usage: " << argv[0] << " port " << endl;
        return 1;
    }
    
    uint16_t port = atoi(argv[1]);

    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if(sockfd == -1) {
        perror("socket");
        return 1;
    }

    struct sockaddr_in server;
    bzero(&server, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    // INADDR_ANY 代表 0.0.0.0，表示接收本机所有网卡的数据
    server.sin_addr.s_addr = htonl(INADDR_ANY);

    if(bind(sockfd, (struct sockaddr*)&server, sizeof(server)) == -1) {
        perror("bind");
        return 1;
    }

    cout << "Server is running on port: " << port << "..." << endl;

    char buffer[1024];
    while (true) {
        struct sockaddr_in client;
        socklen_t len = sizeof(client);
        ssize_t s = recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)&client, &len);
        if(s > 0) {
            buffer[s] = 0;
            string client_ip = inet_ntoa(client.sin_addr);
            uint16_t client_port = ntohs(client.sin_port);
            cout << "[" << client_ip << ":" << client_port << "] 说: " << buffer << endl;
            // sendto(套接字, 内容, 长度, 0, 目标地址结构体, 结构体大小)
            sendto(sockfd, buffer, s, 0, (struct sockaddr*)&client, sizeof(client));
        }
    }
    
    return 0;
}