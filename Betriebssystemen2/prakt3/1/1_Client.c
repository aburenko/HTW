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

void routineClient(int semID, char *timeShmID) {
    while(1) {
        sleep(1);
        P(semID);
        
        printf("unverwandter Sohn: %s\n",timeShmID);
        
        V(semID);
    }
}

int main (int argc, char *argv[]) {
    
    if(argc != 3)
        error("usage <path> <sharedMemoryKey> <semaphoreID>");
    // shared memory segment 
    int timeShmKey;
    sscanf (argv[1],"%d",&timeShmKey);
    int shmKey = shmget(timeShmKey, 6, 0);
    if(shmKey < 0)
        error("cant get semaphore");
    // attach memory to key
    char *timeShmID = shmat(shmKey, NULL, SHM_RND);
    if (timeShmID == (char *)-1)
        error("timeShmID cant attach shared memory segment to key");
    
    // get semaphore
    int semKey;
    sscanf (argv[2],"%d",&semKey);
    int semID = semget(semKey, 1, 0);
    if (shmKey == -1)
        error("RC cant get key for shared memory segment");
        
    routineClient(semID, timeShmID);
    exit(0);
}
