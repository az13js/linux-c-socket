#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

void *thread_function (void *arg) {
    printf("线程正在执行\n");
    sleep(1);
    printf("线程正在执行\n");
    sleep(1);
    printf("线程正在执行\n");
}

int main(void) {
    pthread_t thread;
    int result;

    pthread_attr_t attr;
    if (0 != pthread_attr_init(&attr)) {
        printf("属性设置初始化失败\n");
        return 0;
    }
    if (0 != pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED)) {
        printf("设置可分离状态失败\n");
        return 0;
    }
    result = pthread_create(&thread, &attr, &thread_function, NULL);
    if (0 != result) {
        printf("创建线程失败\n");
        return 0;
    }
    printf("线程创建成功\n");
    printf("进程正在运行\n");
    sleep(1);
    printf("进程正在运行\n");
    sleep(1);
    printf("进程正在运行\n");
    sleep(1);
    printf("进程执行完成，即将退出\n");
    return 0;
}

