// 尝试创建最多的文件描述符，用于通信的
// 一个系统最多可以创建多少个文件描述符？
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>

int main(void) {
    int fd;
    do {
        // 当通信的端点创建失败的时候，socket函数会返回 -1
        fd = socket(AF_INET, SOCK_STREAM, 0);
        printf("文件描述符的值是%d\n", fd);
    } while (fd != -1);
    perror("创建失败，错误内容：");
    printf("程序运行结束。\n");
    return 0;
}

// 程序运行后发现，这个值最大总是1023。由于0,1和2其实是有在用的，所以合计总共创建了1024个
// 文件描述符。这个限制是操作系统对进程进行的，通过命令 ulimit -n 查看，果然是1024

