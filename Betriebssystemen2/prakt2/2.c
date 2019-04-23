#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>   
#include <sys/types.h> 
#include <sys/wait.h>
// semaphore libs
#include <sys/ipc.h>
#include <sys/sem.h> 
// shared memory segment
#include <sys/shm.h>

#define FILENAME "zahl.dat"

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

void writeFile() {
    FILE *f;
    int ret, value;
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
        printf("Wert %d reingeschrieben\n", value);
        if(ret <= 0)
            printf("Cannt write a value to file\n");
    }
    // close file
    ret = fclose(f);
    if(ret!=0)
        printf("Cannt close\n");
}

void readFile() {
    FILE *f;
    int ret, value;
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
        else // print value
            printf("Wert %d ausgelesen\n", value);
    }
    // close file
    ret = fclose(f);
    if(ret!=0)
        printf("Cannt close\n");
}

void reader(int *shmAdress, int semaphoreWrite, int mutexRead) {
    P(mutexRead);
    *shmAdress += 1; 
    if(*shmAdress == 1)
        P(semaphoreWrite) ;
    V(mutexRead);    
    
    /* lesender Zugriff */
    printf("%d lese... \n", getpid());
    readFile();
    sleep(1);
    printf("%d gelesen... \n", getpid());
    
    P(mutexRead);
    *shmAdress -= 1; 
    if(*shmAdress == 0)
        V(semaphoreWrite) ;
    V(mutexRead) ;
}

void writer(int *shmAdress, int semaphoreWrite) {
    P(semaphoreWrite);
    
    /* schreibender Zugriff */
    printf("%d schreibe... \n", getpid());
    writeFile();
    sleep(1);
    printf("%d geschrieben \n", getpid());
    
    V(semaphoreWrite);
}

int main () {
    printf("starts\n");
    // make file and write 0
    FILE *f = fopen(FILENAME, "wt");
    fprintf(f, "0");
    fclose(f);
    
    
    // create shared memory segment for var rc
    // get key
    int shmID  = shmget(IPC_PRIVATE, 1, IPC_CREAT | 0660 );
    if (shmID == -1)
        error("cant get key for shared memory segment");
    // attach memory to key
    int *shmAdress = shmat(shmID, NULL, SHM_RND);
    if (shmAdress == (int *)-1)
        error("cant attach shared memory segment to key");
    
    *shmAdress = 0;
    printf("shared memory segment assigned with %d\n", *shmAdress);
    
    pid_t ret_t;
    pid_t retArr[5];
    int i, ret;
    int forkNum = 5;
    
    printf("create semaphore\n");
    // get semaphore
    int semaphoreWrite  = semget(IPC_PRIVATE, 1, IPC_CREAT | 0660 );
    int mutexRead = semget(IPC_PRIVATE, 1, IPC_CREAT | 0660 );
    if(semaphoreWrite < 0 || mutexRead < 0)
        error("cant create semaphore");
    // SETVAL for semaphore
    sem_attr.val = 1; // unlocked
    if (
        semctl (semaphoreWrite,  0, SETVAL, sem_attr) == -1 ||
        semctl (mutexRead, 0, SETVAL, sem_attr) == -1
    )
        error("semctl SETVAL");
    
    for(i=0; i<forkNum; i++) {
        
        ret_t = fork();
    
        if(ret_t < 0) {
            printf("error in fork\n");
            return -1;
        }
        // son
        else if(ret_t == 0) {
            //printf("son born\n");
            
            if(i==2 || i==3) reader(shmAdress, semaphoreWrite, mutexRead);
            else     writer(shmAdress, semaphoreWrite);
            
            exit(0);
        }
        // father
        else {
            retArr[i] = ret_t;
        }
    }
    for(i=0; i<forkNum; i++) {
        //printf("father waits\n");
        ret = waitpid(retArr[i], NULL, 0);
        if(ret < 0)
            printf("son proccess error\n");
        //else printf("son %d finished\n", ret);
    }
    // delete semaphore
    printf("deleting semaphores...\n");
    ret = semctl(semaphoreWrite, 1, IPC_RMID);
    if(ret < 0)
        error("cant delete samaphore");
    
    ret = semctl(mutexRead, 1, IPC_RMID);
    if(ret < 0)
        error("cant delete samaphore");
    
    printf("father dies\n");
    return 0;
}
