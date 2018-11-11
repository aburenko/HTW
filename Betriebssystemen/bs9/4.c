#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define READEND 0
#define WRITEEND 1

int main(int argc, char *argv[]) {
    // checks ===================================
    if(argc != 2) {
        printf("usage: %s <Anzahl der Prozesse>\n",argv[1]);
        return -1;
    }
    int n = atoi(argv[1]);
    if(n<=0) {
        puts("use positive n");
        return -1;
    }
    //create pipe
    int pipefd[2];
    if(pipe(pipefd)==-1) {
        puts("error to create new pipe");
        exit(EXIT_FAILURE);
    }
    
    pid_t ret = 1;
    int soncount = n;
    // create subproccesses ======================================
    while(n > 0 && ret>0) { // only father
        ret = fork();
        if(ret==-1) {
            printf("error to create new fork n:%d\n",n);
            exit(EXIT_FAILURE);
        }
        else if (ret==0) {
            // SON -----------------------------------------
            close(pipefd[WRITEEND]);
            int bufs;
            read(pipefd[READEND],&bufs,1);
            close(pipefd[READEND]);
            printf("sohn closed pid_t: %d  bufs:%d\n", getpid(), bufs);
            exit(EXIT_SUCCESS);
        }
        n--;
    }
    if(ret>0) {
        // send on all sons ===========================
        close(pipefd[READEND]);
        int i;
        printf("Writing\n");
        for(i=1;i<=soncount;i++)
            write(pipefd[WRITEEND],&i,1);
        close(pipefd[WRITEEND]);
        while(wait(NULL) != -1);
        printf("father beendet\n");
    }
    return 0;
}