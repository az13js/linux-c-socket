#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

void *thread_function (void *arg) {
    printf("Thread function is running\n");
    sleep(1);
    printf("Thread function is running\n");
    sleep(1);
    printf("Thread function is running\n");
    sleep(1);
    printf("Thread function end\n");
}

int main(void) {
    pthread_t thread;
    int result;

    pthread_attr_t attr;
    if (0 != pthread_attr_init(&attr)) {
        printf("Init fail\n");
        return 0;
    }
    if (0 != pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED)) {
        printf("Set Detach state fail\n");
        return 0;
    }
    result = pthread_create(&thread, &attr, &thread_function, NULL);
    if (0 != result) {
        printf("Create thread fail!\n");
        return 0;
    }
    printf("Thread creae ok.\n");
    printf("Main function is running\n");
    sleep(1);
    printf("Main function is running\n");
    sleep(1);
    printf("Main function is running\n");
    sleep(1);
    printf("Main function end\n");
    return 0;
}

