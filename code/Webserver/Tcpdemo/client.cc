#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

using namespace std;

#define CHECK_RET(exp, msg) if ((exp) < 0) { perror(msg); exit(1); }

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cout << "Usage: " << argv[0] << " server_ip server_port" << endl;
        return 1;
    }

    string ip = argv[1];
    uint16_t port = atoi(argv[2]);

    // 1. 创建 Socket
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    CHECK_RET(sock, "socket");

    // 2. 发起连接 (Connect) 
    struct sockaddr_in server;
    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    int ret = inet_pton(AF_INET, ip.c_str(), &server.sin_addr);
    if (ret != 1) {
        perror("inet_pton 错误"); 
        return 1;;
    } 
    // 客户端需要调用connect()连接服务器
    // connect会发出SYN段并阻塞等待服务器应答
    cout << "Connecting to " << ip << ":" << port << "..." << endl;
    CHECK_RET(connect(sock, (struct sockaddr*)&server, sizeof(server)), "connect");
    
    cout << "Connect Success!" << endl;

    // 3. 业务循环
    while (true) {
        cout << "Please Enter# ";
        string msg;
        getline(cin, msg);

        if (msg == "quit") break;

        // 发送数据
        write(sock, msg.c_str(), msg.size());

        // 接收回显
        char buffer[1024];
        memset(buffer, 0, sizeof(buffer));
        ssize_t s = read(sock, buffer, sizeof(buffer) - 1);
        if (s > 0) {
            buffer[s] = 0;
            cout << buffer << endl;
        } else {
            cout << "Server closed connection." << endl;
            break;
        }
    }

    // 4. 关闭
    close(sock);
    return 0;
}