#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>

void Daemonize() {
    // 1. 忽略信号
    signal(SIGCHLD, SIG_IGN); 

    // 2. 第一步 Fork：父进程退出
    if (fork() > 0) exit(0);

    // 3. 创建新会话：彻底脱离终端
    setsid();

    // 4. 第二步 Fork（防范性编程）：
    // 再次 fork 并非严格必须，但可以确保进程永远无法重新打开一个终端。
    // (不是会话首进程就不能打开终端)
    if (fork() > 0) exit(0);

    // 5. 改变工作目录
    chdir("/");

    // 6. 重设权限掩码
    umask(0);

    // 7. 关闭并重定向标准输入输出
    // 这一步是将 0, 1, 2 全部指向 /dev/null
    int fd = open("/dev/null", O_RDWR);
    dup2(fd, 0); // stdin -> /dev/null
    dup2(fd, 1); // stdout -> /dev/null
    dup2(fd, 2); // stderr -> /dev/null
    close(fd);
}
