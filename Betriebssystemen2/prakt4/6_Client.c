#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>   
#include <sys/types.h> 
#include <sys/wait.h>
#include <string.h>

#include <sys/ipc.h>
#include <sys/msg.h>
    
#include <signal.h>

#include "6.h"

#define MAXLINE 2048

// links to professor scripts examples
// https://www2.htw-dresden.de/~robge/bs2/vl/src/share.h
// https://www2.htw-dresden.de/~robge/bs2/vl/src/msgserver.c
// https://www2.htw-dresden.de/~robge/bs2/vl/src/msgclient.c

void send(int mID, char *pline, int len) {
    int
    ret = msgsnd(mID, pline, len, 0);
    if (ret == -1) {
        printf("client: msgsnd()");
    }
}

int main () {
    /* Create Message Queue */
    int mID = msgget(CHANALKEY, IPC_CREAT|0622);
    if (mID == -1) {
        perror("msgget() input");
        exit(EXIT_FAILURE);
    }
    
    char pline[MAXLINE];
    
    char *files[3] = {"a.text\n","6.c\n","6_Client.c\n"};
    
    for(int i=0; i<3; i++)
        send(mID, files[i], strlen(files[i]));
    
    while(fgets(pline, MAXLINE, stdin)) {
        send(mID, pline, strlen(pline));
    }

    exit(EXIT_SUCCESS);
}
