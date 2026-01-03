#pragma once
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <cstdlib> 

void Daemonize() {
    // 1. 忽略 SIGPIPE
    // 网络编程中，如果对方关闭连接我们还在写数据，会收到 SIGPIPE 导致进程崩溃
    // 这对于守护进程是致命的，必须忽略
    signal(SIGPIPE, SIG_IGN);
    
    // 2. 也是为了防止僵尸进程 (虽然我们现在用线程，但这是守护进程标配)
    signal(SIGCHLD, SIG_IGN);

    // 3. fork 父进程退出
    // 这样做的目的是让 Shell 认为这条命令已经执行完毕，把终端控制权还给用户
    if (fork() > 0) exit(0);

    // 4. 创建新会话 (Session)
    // 子进程继承了父进程的会话、进程组、终端
    // setsid() 让当前进程创建一个新会话，完全脱离原控制终端
    setsid();

    // 5. 再次 fork (可选，但在 System V 系统中推荐)
    // 确保进程不是会话首进程，从而保证它永远无法重新获得控制终端
    // if (fork() > 0) exit(0);

    // 6. 改变工作目录
    // 守护进程通常在根目录下运行，防止占用可卸载的文件系统（如 U 盘）
    // 这里为了演示方便，也可以不改，或者改成 "/tmp"
    // chdir("/"); 

    // 7. 重设文件权限掩码
    // 这样新创建的文件权限才不会受父进程 umask 影响
    umask(0);

    // 8. 重定向标准输入、输出、错误 (非常重要！)
    // 守护进程没有终端，所以 cout/printf 没地方去。
    // 我们把它们指向 /dev/null (黑洞)，或者重定向到日志文件。
    int fd = open("/dev/null", O_RDWR);
    if (fd >= 0) {
        dup2(fd, 0); // 标准输入 -> /dev/null
        dup2(fd, 1); // 标准输出 -> /dev/null
        dup2(fd, 2); // 标准错误 -> /dev/null
        close(fd);
    }
}