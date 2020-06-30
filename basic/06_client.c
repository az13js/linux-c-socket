// Socket连接服务器端
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>

// 设置连接的服务器地址
int set_address(int fd) {
    int inet_aton_return, connect_return, shutdown_result;
    struct sockaddr_in *addr;
    char buf[10] = {'a', 'b', 'c', '\0'};
    ssize_t len;
    addr = (struct sockaddr_in *)malloc(sizeof(struct sockaddr_in));
    if (0 == addr) {
        printf("Malloc fail! sockaddr_in\n");
        return 0;
    }
    addr->sin_family = AF_INET;
    addr->sin_port = htons(80);
    inet_aton_return = inet_aton("127.0.0.1", &(addr->sin_addr));
    if (0 == inet_aton_return) {
        printf("Set ip error. return %d\n", inet_aton_return);
    } else {
        printf("Set ip success.\n");
        connect_return = connect(fd, (struct sockaddr *)addr, sizeof(struct sockaddr_in));
        if (0 == connect_return) {
            printf("Connect success.\n");
            len = send(fd, buf, 4, 0);
            printf("Send %ld byte\n", len);
            // 关闭连接
            shutdown_result = shutdown(fd, SHUT_RDWR);
            if (0 != shutdown_result) {
                printf("shutdow fail, %d\n", shutdown_result);
                perror("perror()");
            } else {
                printf("shutdow success\n");
            }
        } else {
            perror("Connect fail");
        }
    }
    free(addr);
}

// 创建和释放socket的地方
int basic_socket_operate(void) {
    int fd, close_socket_return;
    fd = socket(AF_INET, SOCK_STREAM, 0);
    if (-1 == fd) {
        printf("Create socket fail! Function socket() return -1.\n");
        return 0;
    } else {
        printf("Create socket success.\n");
    }
    set_address(fd);
    close_socket_return = close(fd);
    if (0 != close_socket_return) {
        printf("Close socket fail! Function close() return %d.\n", close_socket_return);
    } else {
        printf("Close socket success.\n");
    }
    return 0;
}

int main(void) {
    basic_socket_operate();
    return 0;
}
