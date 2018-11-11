#include<stdio.h>
#include<stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]) {

    if(argv[1]==NULL) {
        printf("no parameter :(");
        return -1;
    } 
    
    int i;
    int limit = atoi(argv[1]);
    
    int ret;
    
    for(i=0;i<limit;i++) {
        ret = fork();
        if(ret == 0) {
            if(ret<0) {
                printf("error in fork");
                return -1;
            }
            printf("ich :%d: gehe schlafen\n", getpid());
            sleep(2);
            printf("ich :%d: bin wieder da\n", getpid());
            exit(0);
        }
    }
    
    return 0;
}
