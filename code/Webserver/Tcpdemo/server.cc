#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <pthread.h>
#include <thread>
#include "daemon.hpp"

using namespace std;

// 错误处理宏
#define CHECK_RET(exp, msg) \
    do { \
        if ((exp) < 0) { \
            perror(msg); \
            exit(1); \
        } \
    } while (0)

// 把 IO 处理逻辑封装成函数，方便复用
void ServiceIO(int service_sock, string clientIp, uint16_t clientPort) {
    while (true) {
        char buffer[1024];
        memset(buffer, 0, sizeof(buffer));
        ssize_t s = read(service_sock, buffer, sizeof(buffer) - 1);
        if (s > 0) {
            cout << "[" << clientIp << ":" << clientPort << "] Client say# " << buffer << endl;
            string resp = "Server Echo: " + string(buffer);
            write(service_sock, resp.c_str(), resp.size());
        } else if (s == 0) {
            cout << "[" << clientIp << ":" << clientPort << "] Client quit..." << endl;
            break;
        } else {
            perror("read");
            break;
        }
    }
    close(service_sock); // 关闭连接
}

// 线程参数结构体
struct ThreadData {
    int serviceSock;
    string clientIp;
    uint16_t clientPort;
};

void* ThreadRoutinr(void* args) {
    // 线程分离，线程退出时自动回收资源，不需要主线程 join
    pthread_detach(pthread_self());
    ThreadData* td = (ThreadData*)args;
    ServiceIO(td->serviceSock, td->clientIp, td->clientPort);
    delete td;
    return nullptr;
}

int main(int argc, char* argv[]) {

    if (argc != 2) {
        cout << "Usage: " << argv[0] << " port" << endl;
        return 1;
    }

    // 守护进程
    Daemonize();

    uint16_t port = atoi(argv[1]);

    // 1. 创建 socket 
    int listen_sock = socket(AF_INET, SOCK_STREAM, 0);
    CHECK_RET(listen_sock, "socket");

    // 【新增】设置端口复用 (Solves: Address already in use)
    int opt = 1;
    // SOL_SOCKET: 也就是 Socket Level，表示设置 socket 层面的选项
    // SO_REUSEADDR: 允许重用本地地址和端口
    // &opt: 开启选项 (1)
    setsockopt(listen_sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    // 2. 绑定 (Bind)
    struct sockaddr_in local;
    memset(&local, 0, sizeof(local));
    local.sin_family = AF_INET;
    local.sin_port = htons(port); // 注意转换网络字节序
    local.sin_addr.s_addr = htonl(INADDR_ANY); 

    CHECK_RET(bind(listen_sock, (struct sockaddr*)&local, sizeof(local)), "bind");

    // 3. 监听 (Listen) - 这是 UDP 没有的步骤
    //  listen()声明sockfd处于监听状态,并且最多允许有backlog个客户端处于连接等待状态
    CHECK_RET(listen(listen_sock, 5), "listen"); 
    cout << "Server is listening on port: " << port << "..." << endl;

    // [version 2]【插入在这里】防止僵尸进程
    // 显式忽略 SIGCHLD 信号，系统会自动回收子进程资源
    // signal(SIGCHLD, SIG_IGN);

    // 4. 获取连接 (Accept) - 阻塞等待客户端连接
    while (true) {
        struct sockaddr_in client_addr;
        socklen_t len = sizeof(client_addr);
        
        //  三次握手完成后,服务器调用accept()接受连接
        // addr是一个传出参数,accept()返回时传出客户端的地址和端口号
        // 注意：accept 返回的是一个新的文件描述符(service_sock)，专门用于和这个特定的客户端通信
        int service_sock = accept(listen_sock, (struct sockaddr*)&client_addr, &len);
        if (service_sock < 0) {
            perror("accept");
            continue;
        }
        cout << "service_sock = " << service_sock << "  ";
        char clientIpBuf[INET_ADDRSTRLEN];
        const char* ptr = inet_ntop(AF_INET, &client_addr.sin_addr, clientIpBuf, sizeof(clientIpBuf));
        if(!ptr) {
            perror("inet_ntop failed");
        }
        uint16_t clientPort = ntohs(client_addr.sin_port);
        cout << "Get a new link: [" << clientIpBuf << ":" << clientPort << "]" << endl;
        // 5. 进行 IO 操作 (读写数据)
        // 注意：目前的单进程写法，如果不 fork/多线程，服务器在处理这个 while 循环时
        // 无法处理其他客户端的连接请求 (串行处理)
        // ---------- version 1 -----------
        // ServiceIO(service_sock, clientIpBuf, clientPort);

        // ---------- version 2 -----------
        // pid_t id = fork();
        // if(id == 0) {
        //     close(listen_sock);
        //     ServiceIO(service_sock, clientIpBuf, clientPort);
        //     exit(0);
        // } else if(id > 0) {
        //     // 父进程不需要通信 socket，必须关闭！
        //     // 重点：如果不关，文件描述符会泄露，导致最后无法建立新连接
        //     close(service_sock);
        // } else {
        //     perror("fork");
        // }


        // ---------- version 3.0 -----------
        // ThreadData* td = new ThreadData();
        // td->clientIp = clientIpBuf;
        // td->clientPort = clientPort;
        // td->serviceSock = service_sock;

        // pthread_t tid;
        // int ret = pthread_create(&tid, nullptr, ThreadRoutinr, (void*)td);
        // if(ret != 0) {
        //     cout << "pthread_create error" << endl;
        //     // 创建失败记得释放内存和关闭socket
        //     delete td;
        //     close(service_sock);
        //     continue;
        // }

        // ---------- version 3.1 -----------
        thread t(ServiceIO, service_sock, (string)clientIpBuf, clientPort);
        t.detach();


    }
    close(listen_sock);
    return 0;
}