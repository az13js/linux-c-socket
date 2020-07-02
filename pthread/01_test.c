#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void *thread_function (void *arg) {
    for (int i = 0; i < 1000; i++) {
        printf("%d ", *((int *)arg));
    }
}

int main(void) {
    pthread_t thread1, thread2;
    int result = 0, t1 = 1, t2 = 2;
    result = pthread_create(&thread1, NULL, &thread_function, (void *)&t1);
    if (0 != result) {
        printf("创建线程1失败\n");
        return 0;
    }
    result = pthread_create(&thread2, NULL, &thread_function, (void *)&t2);
    if (0 != result) {
        printf("创建线程2失败\n");
        return 0;
    }
    sleep(1);
    printf("\n");
    return 0;
}

