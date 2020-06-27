// Socket编写服务器，监听某个端口
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>

int do_listen_and_accept(int fd) {
    int listen_result, close_socket_return, shutdown_result;
    struct sockaddr *peer_addr;
    // 临时指针，指向保存了客户端地址信息的结构体
    struct sockaddr_in *temp;
    int *len_of_sockaddr;
    int peer_socket;
    listen_result = listen(fd, SOMAXCONN);
    if (0 != listen_result) {
        // 处理listen失败的情况
        printf("listen fail! return %d\n", listen_result);
        perror("fail info is ");
        return 0;
    } else {
        // listen成功
        printf("listen success.\n");
        // 接受20次连接后不再重复。监听80端口，浏览器访问127.0.0.1可以看到效果
        for (int i = 0; i < 20; i++) {
            printf("ID: %d\n", i);
            len_of_sockaddr = (int *)malloc(sizeof(int));
            *len_of_sockaddr = sizeof(struct sockaddr);
            peer_addr = (struct sockaddr *)malloc(sizeof(struct sockaddr));
            // accept函数直到有客户端连接上来才会返回
            peer_socket = accept(fd, peer_addr, len_of_sockaddr);
            if (-1 == peer_socket) {
                printf("accept fail! return %d\n", peer_socket);
                perror("fail info is ");
            } else {
                // 处理accept成功的情况
                printf("accept success\n");
                // 获取客户机的地址信息
                temp = (struct sockaddr_in *)peer_addr;
                // 将网络字节序的地址信息转换为字符串地址，返回的指针由inet_ntoa控制不需要人为释放
                printf("Client address: %s\n", inet_ntoa(temp->sin_addr));
                // 打印端口号
                printf("Client port: %d\n", ntohs(temp->sin_port));

                // 关闭连接
                shutdown_result = shutdown(peer_socket, SHUT_RDWR);
                if (0 != shutdown_result) {
                    printf("shutdow fail, %d\n", shutdown_result);
                    perror("perror()");
                    return 0;
                } else {
                    printf("shutdow success\n");
                }
                close_socket_return = close(peer_socket);
                if (0 != close_socket_return) {
                    printf("Close peer socket fail! Function close() return %d.\n", close_socket_return);
                } else {
                    printf("Close peer socket success.\n");
                }
            }
            free(len_of_sockaddr);
            free(peer_addr);
        }
    }
    return 0;
}

// 配置监听地址和绑定操作
int binding_address(int fd) {
    //struct sockaddr *addr; 与struct sockaddr_in可以相互转换，它们大小相同
    struct sockaddr_in *addr;
    //保存bind函数的返回值
    int bind_result;
    //首先需要配置绑定的端口号之类的配置信息
    //printf("Size of sockaddr_in is %ld.\n", sizeof(struct sockaddr_in)); 16字节
    addr = (struct sockaddr_in *)malloc(sizeof(struct sockaddr_in));
    if (0 == addr) {
        printf("Malloc fail! sockaddr_in\n");
        return 0;
    }
    // 使用IPv4
    addr->sin_family = AF_INET;
    // 允许任何IP接入
    addr->sin_addr.s_addr = htonl(INADDR_ANY);
    // 监听端口是80端口
    addr->sin_port = htons(80);

    // 接下来需要使上面配置的信息生效，就是执行真正的绑定动作，使用bind函数
    bind_result = bind(fd, (struct sockaddr *)addr, sizeof(struct sockaddr));
    // 处理绑定失败的情况
    if (0 != bind_result) {
        printf("Bind error, return %d\n", bind_result);
        // 如果没有root权限，那么此时会打印出 Permission denied
        perror("Bind error info is ");
    } else {
        printf("Bind success.\n");
        do_listen_and_accept(fd);
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
    binding_address(fd);
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
