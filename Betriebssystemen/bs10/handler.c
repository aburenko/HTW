#include <unistd.h>
#include <signal.h>
#include <stdio.h> 
#include <sys/types.h>
#include <stdlib.h>

void SIGUSR1handler() {
    printf("SIGUSR1 empfangen!\n");
    // set signal to SIGUSR1 to standart handler 
    sig_t ret;
    ret = signal(SIGUSR1, (sig_t) SIG_DFL);
    if(ret == SIG_ERR) {
        puts("cant catch in handler");
        exit(EXIT_FAILURE);
    }
    return;
}

int main(int argc, char* argv[])
{
    sig_t ret;
    //install signal
    ret = signal(SIGUSR1, (sig_t) &SIGUSR1handler);
    if(ret == SIG_ERR) {
        puts("cant catch");
        exit(EXIT_FAILURE);
    }
    // send two SIGUSR1 to itself 
    kill(getpid(),SIGUSR1);
    kill(getpid(),SIGUSR1);
    return 0;
}