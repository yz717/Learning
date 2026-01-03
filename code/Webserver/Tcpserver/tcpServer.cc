#include "tcpServer.hpp"
#include <memory>
#include "daemon.hpp" 

// 简单的日志重定向函数
void EnableFileLog() {
    // 打开一个文件，如果不存在则创建，追加模式
    int fd = open("server.log", O_WRONLY | O_CREAT | O_APPEND, 0664);
    if (fd < 0) return;

    // 把标准输出 (1) 和 标准错误 (2) 都改成这个文件
    dup2(fd, 1);
    dup2(fd, 2);
    close(fd);
}


int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "Usage: " << argv[0] << " <port>" << std::endl;
        return 1;
    }

    // 变成守护进程
    Daemonize(); 

    // 开启文件日志 (把 cout 的内容写到 server.log)
    EnableFileLog();

    // 1. 实例化 Server 对象
    std::unique_ptr<TcpServer> server(new TcpServer(atoi(argv[1])));

    // 2. 初始化网络层
    server->Init();

    // 3. 启动服务
    server->Loop();

    return 0;
}