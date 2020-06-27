// 尝试打开Socket然后关掉
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
// 实测close是在unistd头文件的，不加这个编译出警告
#include <unistd.h>

int main(void) {
    int fd, close_result, shutdown_result;
    fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd == -1) {
        printf("socket create return -1, fail\n");
        return 0;
    } else {
        printf("socket create return %d, success\n", fd);
    }
    // 停止所有此socket相关的读写操作
    shutdown_result = shutdown(fd, SHUT_RDWR);
    if (0 == shutdown_result) {
        printf("shutdow success");
    } else {
        printf("shutdow fail, %d\n", shutdown_result);
        // 这个示例里面没客户端连接
        // perror(): Transport endpoint is not connected
        perror("perror()");
    }
    // 关闭socket
    close_result = close(fd);
    // 如果关闭Socket失败，比如这里close(9)，9不存在，这时返回-1。成功close返回0
    printf("close socket return %d\n", close_result);
    return 0;
}
