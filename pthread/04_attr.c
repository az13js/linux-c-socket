#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

void *thread_function (void *arg) {
    printf("这个是线程函数\n");
}

int main(void) {
    pthread_t thread;
    int result;

    pthread_attr_t *attr;
    attr = (pthread_attr_t *)malloc(sizeof(pthread_attr_t));
    // 不用malloc申请内存的方式也是没问题的，比如：
    // pthread_attr_t attr_no_malloc;
    // pthread_attr_t attr = &attr_no_malloc;

    // 设置线程执行特性的参数
    if (0 != pthread_attr_init(attr)) {
        printf("属性初始化失败\n");
        free(attr);
        return 0;
    }
    if (0 != pthread_attr_setscope(attr, PTHREAD_SCOPE_SYSTEM)) {
        printf("设置属性失败\n");
        free(attr);
        return 0;
    } else {
        printf("设置属性成功\n");
    }

    result = pthread_create(&thread, attr, &thread_function, NULL);
    if (0 != result) {
        printf("创建线程失败！\n");
        return 0;
    }
    // 销毁配置属性，调用pthread_create之后立刻销毁此属性也不会影响到创建出来的线程。
    if (0 != pthread_attr_destroy(attr)) {
        printf("属性销毁失败\n");
    }

    // 使用malloc申请的内存可以释放掉了
    free(attr);
    sleep(1);
    printf("主程序执行完成。\n");
    return 0;
}

