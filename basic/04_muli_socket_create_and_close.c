// 尝试打开多个Socket并最后关闭它们
// 文件描述符总是按照最小可用的来返回，那么我关闭了旧的再创建新的，函数会复用上一个文件描述符吗？
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

int main(void) {
    int fds[5], close_results[5], i;

    // 分两次，每次创建多个Socket然后关闭
    printf("1:\n");
    for (i = 0; i < 5; i++) {
        fds[i] = socket(AF_INET, SOCK_STREAM, 0);
        printf("Socket %d, value %d\n", i + 1, fds[i]);
    }
    for (i = 0; i < 5; i++) {
        close_results[i] = close(fds[i]);
        printf("Close socket %d, close() return %d\n", i + 1, close_results[i]);
    }

    // 第二遍，通过再次创建Socket来找到问题的答案
    printf("2:\n");
    for (i = 0; i < 5; i++) {
        fds[i] = socket(AF_INET, SOCK_STREAM, 0);
        printf("Socket %d, value %d\n", i + 1, fds[i]);
    }
    for (i = 0; i < 5; i++) {
        close_results[i] = close(fds[i]);
        printf("Close socket %d, close() return %d\n", i + 1, close_results[i]);
    }

    return 0;
}

/*

下面是程序的运行结果，表明了socket函数在返回值的时候总是会使用当前能用的最小的数作为文件描述符。
只要被close释放了，那么就会重复使用

1:
Socket 1, value 3
Socket 2, value 4
Socket 3, value 5
Socket 4, value 6
Socket 5, value 7
Close socket 1, close() return 0
Close socket 2, close() return 0
Close socket 3, close() return 0
Close socket 4, close() return 0
Close socket 5, close() return 0
2:
Socket 1, value 3
Socket 2, value 4
Socket 3, value 5
Socket 4, value 6
Socket 5, value 7
Close socket 1, close() return 0
Close socket 2, close() return 0
Close socket 3, close() return 0
Close socket 4, close() return 0
Close socket 5, close() return 0


*/


