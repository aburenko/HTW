#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>   
#include <sys/types.h> 
#include <sys/wait.h>
// semaphore libs
#include <sys/ipc.h>
#include <sys/sem.h>

#define FILENAME "zahl.dat"
#define LOOPNUM 20000

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

void routine() {
    FILE *f;
    
    int ret, i, value;
    
    for(i=0; i<LOOPNUM; i++) {
        printf("lauf i %d with pid %d\n", i, getpid());
        //open
        f = fopen(FILENAME, "r+t");
        if(f==NULL) {
            printf("Cannt open\n");
        }
        else {
            // read value from file
            ret = fscanf(f, "%d", &value);
            if(ret <= 0)
                printf("Cannt find a value in FILENAME\n");
            // inkrement the value
            value++;
            //printf("value %d\n", value);
            // clear file
            f = freopen(FILENAME, "wt", f);
            if(f == NULL)
                printf("Cannt reopen FILENAME\n");
            // write value
            ret = fprintf(f, "%d", value);
            if(ret <= 0)
                printf("Cannt write a value to file\n");
        }
        // close file
        ret = fclose(f);
        if(ret!=0)
            printf("Cannt close\n");
    }
}

int main () {
    printf("starts\n");
    
    FILE *f = fopen(FILENAME, "wt");
    fprintf(f, "0");
    fclose(f);
    
    pid_t ret_t;
    pid_t retArr[5];
    int i, ret;
    int forkNum = 5;
    
    // create semaphore
    printf("create semaphore\n");
    // get semaphore
    int semID = semget(IPC_PRIVATE, 1, IPC_CREAT | 0660 );
    if(semID < 0)
        error("cant create semaphore");
    // SETVAL for semaphore
    sem_attr.val = 1; // unlocked
    if (semctl (semID, 0, SETVAL, sem_attr) == -1)
        error("semctl SETVAL");
    
    for(i=0; i<forkNum; i++) {
        
        ret_t = fork();
    
        if(ret_t < 0) {
            printf("error in fork\n");
            return -1;
        }
        // son
        else if(ret_t == 0) {
            printf("son born\n");
            
            // do P() on semaphore
            printf("do P() pid:%d\n", getpid());
            struct sembuf singleSembuf = {0, -1, SEM_UNDO};
            struct sembuf arrSembuf[1] = {singleSembuf};
            struct sembuf *sops = arrSembuf;
            ret = semop(semID, sops, 1);
            if(ret < 0)
                error("cant do P()");
           
            if(i==0) {
                printf("abort!\n");
                abort();
            }
            
            routine();
            
            // do V() on semaphore
            printf("do V()\n");
            struct sembuf singleSembufV = {0, 1, SEM_UNDO};
            struct sembuf arrSembufV[1] = {singleSembufV};
            struct sembuf *sopsV = arrSembufV;
            printf("1\n");
            ret = semop(semID, sopsV, 1);
            printf("2\n");
            if(ret < 0)
                error("cant do V()");
            
            printf("exit\n");
            exit(0);
        }
        // father
        else {
            retArr[i] = ret_t;
        }
    }
    for(i=0; i<forkNum; i++) {
        printf("father waits\n");
        ret = waitpid(retArr[i], NULL, 0);
        if(ret < 0)
            printf("son proccess error\n");
        else
            printf("son %d finished\n", ret);
    }
    // delete semaphore
    printf("deleting semaphore...\n");
    ret = semctl(semID, 1, IPC_RMID);
    if(ret < 0)
        error("cant delete samaphore");
    printf("father dies\n");
    return 0;
}
