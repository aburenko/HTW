#include <unistd.h>
#include <signal.h>
#include <stdio.h> 
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[])
{
    //create fork
    pid_t retfork;
    if((retfork = fork()) == -1) {
        printf("fork call error");
        exit(EXIT_FAILURE);
    }
    
    char command[50];
    char n = -1;
    
    if (retfork == 0) {
        //son ========================================================
        // establish a command string
        sprintf(command, "./%s %s", argv[1], argv[2]);
        n=1;
    }
    else {
        //father ========================================================
        // establish a command string
        sprintf(command, "./%s %s", argv[2], argv[1]);
        n=2;
    }
    // run in the bash
    if(system(command) == -1) {
        printf("system call error");
        exit(EXIT_FAILURE);
    }
    // exit printout
    printf("program %d ended\n", n);
    exit(EXIT_SUCCESS);
}