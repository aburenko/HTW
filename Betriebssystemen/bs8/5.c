#include<stdio.h>
#include<stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]) {

    if(argv[1]==NULL) {
        printf("no parameter :(");
        return -1;
    } 
    
    int i = 0;
    int limit = atoi(argv[1]);
    
    int ret = 0;
    int y = 0;  
    while(ret == 0 && i <= limit) {
        ret = fork();
        if(ret == -1) {
            printf("error in fork");
        }
        if(ret > 0) {
            ret = wait(NULL);
            if (ret == -1) {
                perror("wait");
                exit(EXIT_FAILURE);
            }
            printf("%d,\n", i);
            exit(EXIT_SUCCESS);
        }
        i++;
    }
    
    return 0;
}
