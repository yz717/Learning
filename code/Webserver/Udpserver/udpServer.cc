#include "udpServer.hpp"
#include <memory>
using namespace std;

// 业务逻辑 A：单纯打印 
void simplePrint(int sockfd, string msg, string ip, uint16_t port)
{
    cout << "[" << ip << ":" << port << "] Log: " << msg << endl;
}

// 业务逻辑 B：模拟简单的指令处理 
void commandHandler(int sockfd, string msg, string ip, uint16_t port)
{
    cout << "Checking command from " << ip << "..." << endl;
    if(msg == "ls") {
        cout << "User wants to list files." << endl;
        system("ls -l"); // 真的执行 ls 命令
    } else {
        cout << "Unknown command: " << msg << endl;
    }
}

// 业务逻辑 C：收到什么，就回发什么
void echo_handler(int sockfd, string msg, string ip, uint16_t port)
{
    cout << "[" << ip << ":" << port << "] Client says: " << msg << endl;
    string response = "Server gets: " + msg;
    struct sockaddr_in peer;
    memset(&peer, 0, sizeof(peer));
    peer.sin_family = AF_INET;
    peer.sin_port = htons(port);
    peer.sin_addr.s_addr = inet_addr(ip.c_str());
    sendto(sockfd, response.c_str(), response.size(), 0, (struct sockaddr*)&peer, sizeof(peer));
}

int main(int argc, char *argv[])
{
    if(argc != 2) {
        cout << "Usage: ./server port" << endl;
        return 1;
    }
    uint16_t port = atoi(argv[1]);

    UdpServer server(port);
    server.init();
    
    // 传入回调函数
    server.start(echo_handler);

    return 0;
}