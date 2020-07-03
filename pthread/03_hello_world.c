// 包含 stdio.h 是为了使用 printf 函数，在屏幕上输出文字
#include <stdio.h>
// 使用 Pthread 相关函数需要包含头文件 pthread.h
#include <pthread.h>
// 为了使用 sleep 函数，使程序暂停执行一定时间
#include <unistd.h>

// 定义的线程函数
void *thread_function (void *arg) {
    printf("这个是线程函数\n");
}

int main(void) {
    pthread_t thread;
    int result;
    result = pthread_create(&thread, NULL, &thread_function, NULL);
    if (0 != result) {
        printf("创建线程失败！\n");
        return 0;
    }
    sleep(1);
    printf("主程序执行完成。\n");
    return 0;
}

// 更多详细内容，参考
// https://www.man7.org/linux/man-pages/man3/pthread_create.3.html

