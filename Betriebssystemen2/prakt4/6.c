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

#define ZIELORDNER "./.."


// links to professor scripts examples
// https://www2.htw-dresden.de/~robge/bs2/vl/src/share.h
// https://www2.htw-dresden.de/~robge/bs2/vl/src/msgserver.c
// https://www2.htw-dresden.de/~robge/bs2/vl/src/msgclient.c

int end = 1;

void routine(char *msgbuf) {
    char cmd[MAXSIZE];
    msgbuf[strlen(msgbuf)-1] = '\0';
    sprintf(cmd,"cp %s %s", msgbuf, ZIELORDNER);
    printf("command: %s\n",cmd);
    system(cmd);
}

void sigint_handler(void *in) {
    end = 0;
}

int getNumberOfMessagesInQueue(int mID) {
    struct msqid_ds buf;
    int ret = msgctl(mID, IPC_STAT, &buf);    
    if (ret == -1) {
        perror("getNum()");
        return -1;
    }
    return buf.msg_qnum;
}

int main () {
    ssize_t rcvlength;
    char *msgbuf;
    int ret, mID;
  
    // platz für buf schaffen
    msgbuf = malloc(MAXSIZE);
    if (!msgbuf) {
        perror("malloc();");
        exit(EXIT_FAILURE);
    }
    
    // signal setzen
    ret = (int)signal(SIGINT, (__sighandler_t) sigint_handler);
    if (ret == -1) {
        free(msgbuf);
        perror("signal()");
        exit(EXIT_FAILURE);
    }
        
    /* Create Message Queue */
    mID = msgget(CHANALKEY, IPC_CREAT|0622);
    if (mID == -1) {
        perror("msgget() input");
        exit(EXIT_FAILURE);
    }
    
    while(end) {
        usleep(1000000);
        printf("empfange... warteschlange anzahl: %d\n",                              
               getNumberOfMessagesInQueue(mID));
        rcvlength = msgrcv(mID, msgbuf, MAXSIZE, 0, MSG_NOERROR);
        if (rcvlength == -1) {
            perror("msgrcv()");
            exit(EXIT_FAILURE);
        }

        ret = fork();
    
        if(ret < 0) {
            printf("error in fork\n");
            return -1;
        }
        // son
        else if(ret == 0) {
            routine(msgbuf);
            exit(0);
        }
    }
    
    ret = msgctl(mID, IPC_RMID, NULL);
    if (ret == -1) {
        perror("msgctl(), remove, input queue");
    }

    free(msgbuf);
    exit(EXIT_SUCCESS);
}
