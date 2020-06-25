// 创建一个用于通信的文件描述符。
#include <stdio.h>
// 需要下面两个头文件。types.h不是linux必须的，只是历史原因和有些程序需要，所以建议include
#include <sys/types.h>
#include <sys/socket.h>

int main(void) {
    // socket函数创建了用于网络通信的一个端点，并返回一个指向它的文件描述符。
    // socket函数返回的是int类型，这个是文档明确表示的。Windows下可能不是。
    // AF_INET表示IPV4，SOCK_STREAM是保证有顺序的数据报，最后一个这时可以固定为0
    // socket总是返回没有被使用的最小的文件描述符值。测试发现这个值总是3，为什么？
    // 程序刚刚启动的时候，0是标准输入，1是标准输出，2是标准错误。如果此时去打开一个新的文件，
    // 它的文件描述符会是3。POSIX标准要求每次打开文件时（含socket）必须使用当前进程中
    // 最小可用的文件描述符号码，因此，在网络通信过程中稍不注意就有可能造成串话。
    // SOCK_STREAM - 提供面向连接的稳定数据传输，即TCP协议。
    printf("文件描述符的值是%d\n", socket(AF_INET, SOCK_STREAM, 0));
    return 0;
}

