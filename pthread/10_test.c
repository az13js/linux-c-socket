#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

void *thread_function (void *arg) {
    /* 循环次数 */
    int total = 60000;
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
    threads = (pthread_t *)calloc(thread_num, sizeof(pthread_t));
    for (i = 0; i < thread_num; i++) {
        result = pthread_create(&(threads[i]), NULL, &thread_function, (void *)(&share));
        if (0 != result) {
            printf("创建第 %d 个线程时失败了\n", i + 1);
            print_error_info(result);
            return 0;
        }
    }
    /* 暂停等线程执行完成 */
    sleep(5);
    printf("进程执行完成\n");
    return 0;
}

