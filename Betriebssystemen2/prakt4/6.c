#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>   
#include <sys/types.h> 
#include <sys/wait.h>
// semaphore libs
#include <sys/ipc.h>
#include <sys/sem.h>

#include "6.h"

// https://www2.htw-dresden.de/~robge/bs2/vl/src/share.h
// https://www2.htw-dresden.de/~robge/bs2/vl/src/msgserver.c
// https://www2.htw-dresden.de/~robge/bs2/vl/src/msgclient.c

void routine() {    
    
}
            
void sigint_handler(void *in)
{
  end = 1;
}

int main () {
    printf("starts\n");
    
    char *msgbuf;
  
    // signal setzen
    ret = (int) signal(SIGINT, (__sighandler_t) sigint_handler);
    if (ret == -1) {
        free(msgbuf);
        perror("signal()");
        exit(EXIT_FAILURE);
    }
    // platz für buf schaffen
    msgbuf = malloc(MAXSIZE);
    if (!msgbuf) {
        perror("malloc();");
        exit(EXIT_FAILURE);
    }
        
    /* Create Message Queue */
    input_id = msgget(CHANALKEY, IPC_CREAT|0622);
    if (input_id == -1) {
        perror("msgget() input");
        exit(EXIT_FAILURE);
    }
    
    // init message parsing
    printf("create message parsing\n");
    // get key
    key_t mKey = ftok("/bin/cat", 0);
    int mID = msgget(mKey, IPC_CREAT | 0660 );
    if(mID < 0)
        error("cant create semaphore");
    
    int ret;
    while(true) {
        
        ret_t = fork();
    
        if(ret_t < 0) {
            printf("error in fork\n");
            return -1;
        }
        // son
        else if(ret_t == 0) {
            routine();
            printf("exit\n");
            exit(0);
        }
        // father
        else {
            retArr[i] = ret_t;
        }
    }
    
    return -1;
}
