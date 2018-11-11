#include<stdio.h>
#include<unistd.h>

int main() {
    pid_t ret;
    ret = fork();
    
    if(ret == 0) {
        fork();
    }
    sleep(5);
    pid_t myPID = getpid();
    printf("%d %d\n", myPID, ret);
    return 0;
}
