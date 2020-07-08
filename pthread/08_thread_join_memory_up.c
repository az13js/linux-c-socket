#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

void *thread_function (void *arg) {
}

int main(void) {
    pthread_t thread;
    int result;
    pthread_attr_t attr;
    printf("输入任何字符开始执行\n");
    getchar();
    for (int i = 0; i < 1024 * 1024 * 100; i++) {
        if (0 != pthread_attr_init(&attr)) {
            printf("属性设置初始化失败\n");
            return 0;
        }
        if (0 != pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE)) {
            printf("设置可结合状态失败\n");
            return 0;
        }
        result = pthread_create(&thread, &attr, &thread_function, NULL);
        if (0 != result) {
            printf("%d - 创建线程失败\n", i + 1);
            return 0;
        }
        usleep(100);
        if (0 != pthread_attr_destroy(&attr)) {
            printf("属性销毁失败\n");
            return 0;
        }
    }
    sleep(1);
    printf("进程执行完成，即将退出\n");
    return 0;
}

