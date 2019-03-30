#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>   
#include <sys/types.h> 
#include <sys/wait.h>
// semaphore libs
#include <sys/ipc.h>
#include <sys/sem.h>

// P() is lock() bzw wait()
// will auf semaphore zugreifen

// V() is unlock()
// will mein Job in cs beenden und semaphore freigeben
/*
struct sembuf {
    unsigned short sem_num; // semaphore number in set, starts with 0
    short sem_op;           // semaphore operation
                            //  +1 is V()  -1 is P() 
    short sem_flg;          // semaphore flags
}
*/
union semun  
{
    int val;
    struct semid_ds *buf;
    ushort array [1];
} sem_attr;

void error(const char * str) {
    printf("ERROR:\n%s, exiting...\n",str);
    exit(-1);
}

int main () {
    printf("starts\n");
    pid_t ret_t;
    int ret;
    
    // create semaphore
    printf("create semaphore\n");
    // get semaphore
    int semID = semget(IPC_PRIVATE, 1, IPC_CREAT | 0660 );
    if(semID < 0)
        error("cant create semaphore");
    // SETVAL for semaphore
    sem_attr.val = 0; // locked
    if (semctl (semID, 0, SETVAL, sem_attr) == -1)
        error("semctl SETVAL");
    
    ret_t = fork();
    if (ret_t < 0)
        error("fork failed");
    else if (ret_t == 0) {
        // SON
        // do V() on semaphore
        printf("do V()\n");
        struct sembuf singleSembuf = {0, 1, 0};
        struct sembuf arrSembuf[1] = {singleSembuf};
        struct sembuf *sops = arrSembuf;
        ret = semop(semID, sops, 1);
        if(ret < 0)
            error("cant do V()");
    } else {
        // FATHER
        // do P() on semaphore
        printf("do P()\n");
        struct sembuf singleSembuf = {0, -1, 0};
        struct sembuf arrSembuf[1] = {singleSembuf};
        struct sembuf *sops = arrSembuf;
        ret = semop(semID, sops, 1);
        if(ret < 0)
            error("cant do P()");
        // delete semaphore
        printf("deleting semaphore...\n");
        ret = semctl(semID, 1, IPC_RMID);
        if(ret < 0)
            error("cant delete samaphore");
    }
    return 0;
}
