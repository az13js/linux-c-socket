// 测试一条进程可以创建多少条线程
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

void *thread_function (void *arg) {
    sleep(3);
}

void print_error_info(int result) {
    switch (result) {
        case EAGAIN:
            printf("资源不足，无法创建另一个线程，或线程数量达到操作系统的极限\n");
            break;
        case EINVAL:
            printf("线程的运行设置无效，问题出现在pthread_create的第二个输入参数\n");
            break;
        case EPERM:
            printf("没有权限设置调度策略和其它的参数\n");
            break;
        default:
            printf("出现了意料之外的异常情况\n");
    }
}

int main(void) {
    pthread_t *threads;
    int result;
    int test_total = 20000;
    int i;

    threads = (pthread_t *)calloc(test_total, sizeof(pthread_t));
    if (NULL == threads) {
        printf("calloc fail!\n");
    }
    for (i = 0; i < test_total; i++) {
        result = pthread_create(&(threads[i]), NULL, &thread_function, NULL);
        if (0 != result) {
            printf("创建第 %d 个线程时失败了\n", i + 1);
            print_error_info(result);
            return 0;
        }
    }
    sleep(3);
    printf("The end.\n");
    return 0;
}

