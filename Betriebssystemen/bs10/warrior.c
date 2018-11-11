#include <unistd.h>
#include <signal.h>
#include <stdio.h> 
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>

char pr[15];

void handlerStd(int c) {
    printf("%s:get signal %d\n", pr, c);
    sleep(1);
    return;
}

int main(int argc, char* argv[])
{
    strcpy(pr, argv[0]);
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
        //check win
        if(system(command) != 0) {
            printf("! %s won !\n", argv[0]);
            exit(EXIT_SUCCESS);
        }
        sleep(1);
    }
    return 0;
}