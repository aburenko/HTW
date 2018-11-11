#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<string.h>

void *printHelloWorld(char str[]) {
    printf("your string: %s\n", str);
    int *strlength = malloc(sizeof(int));
    *strlength = strlen(str);
    pthread_exit(strlength);
}

int main(int argc, char *argv[]) {
    if(argc != 2) {
        printf("usage: %s \"<string>\"\n", argv[0]);
        exit(-1);
    }
    pthread_t helloWorldThread;
    //create new
    pthread_create(&helloWorldThread, NULL, (void*)printHelloWorld, argv[1]);
    printf("Main Thread!\n");
    //connent with main
    int **strlengthmain;
    pthread_join(helloWorldThread, (void**)strlengthmain);
    printf("length: %d\n", **strlengthmain);
    return 0;
}