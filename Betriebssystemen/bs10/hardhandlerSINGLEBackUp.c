#include <unistd.h>
#include <signal.h>
#include <stdio.h> 
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>

char pr;

void handlerStd(int c) {
    printf("%c:get signal %d\n", pr, c);
    sleep(1);
    return;
}

int main(int argc, char* argv[])
{
    pr = argv[0][2];
    pid_t retfork;
    //create fork
    if((retfork = fork()) == -1) {
        printf("fork call error");
        exit(EXIT_FAILURE);
    }
    else if (retfork == 0) {
        //son ========================================================
        //avoid recursive calling
        if(argv[2] != NULL && strcmp("childfree",argv[2]) == 0) {
            printf("exits childfree\n");
            exit(EXIT_SUCCESS);
        }
        // establish a command string
        char command[50];
        sprintf(command, "./%s %s childfree", argv[1], argv[0]);
        // run in the bash
        if(system(command) == -1) {
            printf("system call error");
            exit(EXIT_FAILURE);
        }
        // exit printout
        printf("program %s exits with success a.k.a. child\n", argv[1]);
        exit(EXIT_SUCCESS);
    }
    // father ========================================================
    sig_t ret;
    int i;
    //install signals
    for(i=1; i<27; i++) {
        // exclude SIGKILL(9) and SIGSTOP(17,19,23) and SIGTERM(15)
        if(i==9 || i==17 || i==19 || i==23 || i==15)
            continue;
        // set for all standart handler
        ret = signal(i, (sig_t) &handlerStd);
        if(ret == SIG_ERR) {
            puts("hh:cant catch");
            exit(EXIT_FAILURE);
        }
    }
    // send singnals to other program 
    for(i=26; i>=1; i--) {
        // exclude SIGKILL(9) and SIGSTOP(17,19,23)
        if(i==9 || i==17 || i==19 || i==23)
            continue;
        // send all signals
        char command[50];
        sprintf(command, "killall -s %d %s", i, argv[1]);
        system(command);
        //check win
        if(printf("%d\n",system(command)) != 0) {
            printf("%s won", argv[0]);
            exit(EXIT_SUCCESS);
        }
        sleep(1);
    }
    printf("program %s ended a.k.a. father\n", argv[0]);
    return 0;
}