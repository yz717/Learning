#include "udpClient.hpp"
#include <iostream>

using namespace std;

static void Usage(string proc)
{
    cout << "Usage:\n\t" << proc << " server_ip server_port\n" << endl;
}

// 运行方式: ./client 127.0.0.1 8080
int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        Usage(argv[0]);
        return 1;
    }

    string ip = argv[1];
    uint16_t port = atoi(argv[2]);

    // 1. 实例化并初始化
    UdpClient client(ip, port);
    client.init();

    string message;
    while (true)
    {
        cout << "Please Enter# ";
        getline(cin, message);

        if (message == "quit") break;

        // 2. 发送逻辑
        client.sendMsg(message);

        // 3. 接收逻辑 (阻塞等待服务器回复)
        string response = client.recvMsg();
        if(!response.empty())
        {
            cout << "Server Echo: " << response << endl;
        }
    }

    return 0;
}