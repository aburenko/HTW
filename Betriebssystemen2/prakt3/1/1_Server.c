#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>   
#include <sys/types.h> 
#include <sys/wait.h>
#include <string.h>
// semaphore libs
#include <sys/ipc.h>
#include <sys/sem.h>
// shared memory segment
#include <sys/shm.h>

#include <time.h>

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

void P(int semaphoreID) {
    // do P() on write semaphore
    //printf("do P()\n");
    struct sembuf singleSembuf = {0, -1, 0};
    struct sembuf arrSembuf[1] = {singleSembuf};
    struct sembuf *sops = arrSembuf;
    if(semop(semaphoreID, sops, 1) < 0)
        error("cant do P()");
}

void V(int semaphoreID) {
    // do V() on semaphore
    //printf("do V()\n");
    struct sembuf singleSembuf = {0, 1, 0};
    struct sembuf arrSembuf[1] = {singleSembuf};
    struct sembuf *sops = arrSembuf;
    if(semop(semaphoreID, sops, 1) < 0)
        error("cant do V()");
}


char * getTime() {
    time_t timeTemp;
    time (&timeTemp);
    struct tm * timeinfo = gmtime(&timeTemp);
    char *t = malloc(6);
    sprintf(t,"%d:%d.%d", timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
    return t;
}

void routineClient(int semID, char *timeShmID) {
    while(1) {
        sleep(1);
        P(semID);
        
        printf("forkson: %s\n",timeShmID);
        fflush(stdout);
        
        V(semID);
    }
}

void routineServer(int semID, char *timeShmID) {
    while(1) {
        P(semID);
        
        char *curTime = getTime();
        memcpy(timeShmID, curTime, sizeof(curTime));
        
        V(semID);
        sleep(1);
    }
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
    sem_attr.val = 1; // unlocked
    if (semctl (semID, 0, SETVAL, sem_attr) == -1)
        error("semctl SETVAL");
    
    // create shared memory segment for var RC
    // get key
    int shmKey  = shmget(IPC_PRIVATE, 6, IPC_CREAT | 0660 );
    if (shmKey == -1)
        error("RC cant get key for shared memory segment");
    // attach memory to key
    char *timeShmID = shmat(shmKey, NULL, SHM_RND);
    if (timeShmID == (char *)-1)
        error("timeShmID cant attach shared memory segment to key");
    
    ret_t = fork();
    
    // error
    if(ret_t < 0) {
        printf("error in fork\n");
        return -1;
    }
    // son
    else if(ret_t == 0) {
        printf("unverwandter son born\n");
        // TODO: zu implementieren
        execl("1_Client.c", 
            "1_Client.c", shmKey, semID 
            (char*) NULL);
        
        printf("unverwandter son exit\n");
        exit(0);
    }
    
    ret_t = fork();
    
    // error
    if(ret_t < 0) {
        printf("error in fork\n");
        return -1;
    }
    // son
    else if(ret_t == 0) {
        printf("fork son born\n");
        
        routineClient(semID, timeShmID);
        
        printf("fork son exit\n");
        exit(0);
    }
    
    // start server routine
    routineServer(semID, timeShmID);
    
    // wait on ret_t(sohn id)
    ret = waitpid(ret_t, NULL, 0);
    if(ret < 0)
        printf("son proccess error\n");
    else
        printf("son %d finished\n", ret);
        
    // delete semaphore
    printf("deleting semaphore...\n");
    ret = semctl(semID, 1, IPC_RMID);
    if(ret < 0)
        error("cant delete samaphore");
    printf("father dies\n");
    return 0;
}
