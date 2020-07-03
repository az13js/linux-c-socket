#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

void *thread_function (void *arg) {
    sleep(3);
}

int main(void) {
    pthread_t *threads;
    int result;
    int test_total = 10000;
    int i;

    threads = (pthread_t *)calloc(test_total, sizeof(pthread_t));
    if (NULL == threads) {
        printf("calloc fail!\n");
    }
    for (i = 0; i < test_total; i++) {
        result = pthread_create(&(threads[i]), NULL, &thread_function, NULL);
        if (0 != result) {
            printf("创建线程 %d 失败\n", i);
            return 0;
        }
    }
    sleep(3);
    printf("The end.\n");
    return 0;
}

