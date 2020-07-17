#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

/*
考虑到不同处理器执行速度可能差别巨大，包括 total 可能会被调整以方便观察，这里将线程
设置成可结合的状态，后面阻塞等待线程完成。
*/

void *thread_function (void *arg) {
    /* 循环次数，如果CPU性能差导致执行时间太久，可以减少这个值 */
    int total = 100000;
    int i;
    int *temp;
    int start, end;
    /* 转换成int类型的指针 */
    temp = (int *)arg;
    start = *temp;
    for (i = 0; i < total; i++) {
        /* 指针指向的整数加1，然后保存回去 */
        *temp = *temp + 1;
    }
    end = *temp;
    printf("%d\t->\t%d\n", start, end);
}

/* 线程创建失败用来打印错误消息 */
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
    int i, result;
    /* 所有线程都能操作的变量 */
    int share = 0;
    /* 线程数 */
    int thread_num = 16;
    /* 存线程ID的数组 */
    pthread_t *threads;
    /* 线程配置 */
    pthread_attr_t attr;

    /* 申请一组内存空间，用来存放线程ID的数组 */
    threads = (pthread_t *)calloc(thread_num, sizeof(pthread_t));
    for (i = 0; i < thread_num; i++) {
        /* 首先设置线程的配置 */
        if (0 != pthread_attr_init(&attr)) {
            printf("属性设置初始化失败\n");
            return 0;
        }
        /* 下面会等待这些线程执行完成，所以这里设置成可结合状态 */
        if (0 != pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE)) {
            printf("设置可结合状态失败\n");
            return 0;
        }
        /* 设置调度策略为分时调度策略 */
        if (0 != pthread_attr_setschedpolicy(&attr, SCHED_RR)) {
            printf("设置调度策略失败\n");
            return 0;
        }
        /* 创建线程 */
        result = pthread_create(&(threads[i]), &attr, &thread_function, (void *)(&share));
        if (0 != result) {
            printf("创建第 %d 个线程时失败了\n", i + 1);
            print_error_info(result);
            return 0;
        }
        /* 线程创建完成后销毁线程配置项 */
        if (0 != pthread_attr_destroy(&attr)) {
            printf("属性销毁失败\n");
            return 0;
        }
    }
    /* 阻塞等线程执行完成 */
    for (i = 0; i < thread_num; i++) {
        if (0 != pthread_join(threads[i], NULL)) {
            printf("pthread_join()调用出现异常\n");
            return 0;
        }
    }
    printf("进程执行完成\n");
    /* 释放线程数组占用的内存 */
    free(threads);
    return 0;
}

