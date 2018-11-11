#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

int main() {
    pid_t ret = fork();
    if(ret==-1) {
        puts("fork error");
        exit(EXIT_FAILURE);
    }
    if(ret == 0)
        fork();
        
    printf("my PID: %d\n", getpid());
    
    exit(EXIT_SUCCESS);
}