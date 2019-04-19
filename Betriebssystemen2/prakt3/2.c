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
        printf("Wert %d reingeschrieben %d\n", value, getpid());
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
            printf("Wert %d ausgelesen %d\n", value, getpid());
    }
    // close file
    ret = fclose(f);
    if(ret!=0)
        printf("Cannt close\n");
}

void reader(int w, int r, int mutexrc, int priowriter, int *rc) {
    P(priowriter);
    P(r);
    P(mutexrc);
    *rc = *rc + 1; 
    if(*rc == 1)
        P(w) ;
    V(mutexrc);
    V(r);
    V(priowriter);  
    
    /* lesender Zugriff */
    printf("%d lese... \n", getpid());
    sleep(1);
    readFile();
    
    P(mutexrc);
    *rc = *rc - 1;
    if (*rc == 0)
        V(w);
    V(mutexrc);
}

void writer(int w, int r, int mutexwc, int *wc) {
    P(mutexwc);
    *wc = *wc + 1;
    if (*wc == 1)
        P(r);
    V(mutexwc);
    P(w);
    
    /* schreibender Zugriff */
    printf("%d schreibe... \n", getpid());
    sleep(1);
    writeFile();
    
    V(w);
    P(mutexwc);
    *wc = *wc - 1;
    if (*wc == 0)
        V(r);
    V(mutexwc);
}

int main () {
    printf("starts\n");
    // make file and write 0
    FILE *f = fopen(FILENAME, "wt");
    fprintf(f, "0");
    fclose(f);
    
    
    // create shared memory segment for var RC
    // get key
    int shmID  = shmget(IPC_PRIVATE, 1, IPC_CREAT | 0660 );
    if (shmID == -1)
        error("RC cant get key for shared memory segment");
    // attach memory to key
    int *rc = shmat(shmID, NULL, SHM_RND);
    if (rc == (int *)-1)
        error("RC cant attach shared memory segment to key");
    
    // create shared memory segment for var WC
    // get key
    shmID  = shmget(IPC_PRIVATE, 1, IPC_CREAT | 0660 );
    if (shmID == -1)
        error("WC cant get key for shared memory segment");
    // attach memory to key
    int *wc = shmat(shmID, NULL, SHM_RND);
    if (rc == (int *)-1)
        error("cant attach shared memory segment to key");
    
    *rc = 0;
    *wc = 0;
    
    printf("RC shared memory segment assigned with %d\n", *rc);
    printf("WC shared memory segment assigned with %d\n", *wc);
    
    pid_t ret_t;
    int forkNum = 10;
    pid_t retArr[forkNum];
    int i, ret;
    
    printf("create semaphore\n");
    // get semaphore
    int priowriter = semget(IPC_PRIVATE, 1, IPC_CREAT | 0660 );
    int w          = semget(IPC_PRIVATE, 1, IPC_CREAT | 0660 );
    int r          = semget(IPC_PRIVATE, 1, IPC_CREAT | 0660 );
    int mutexrc    = semget(IPC_PRIVATE, 1, IPC_CREAT | 0660 );
    int mutexwc    = semget(IPC_PRIVATE, 1, IPC_CREAT | 0660 );
    if (
        priowriter < 0 || 
        w          < 0 ||
        r          < 0 ||
        mutexrc    < 0 || 
        mutexwc    < 0 
    )
        error("cant create semaphore");
    // SETVAL for semaphore
    sem_attr.val = 1; // unlocked
    if (
        semctl (priowriter, 0, SETVAL, sem_attr) == -1 ||
        semctl (w,          0, SETVAL, sem_attr) == -1 ||
        semctl (r,          0, SETVAL, sem_attr) == -1 ||
        semctl (mutexrc,    0, SETVAL, sem_attr) == -1 ||
        semctl (mutexwc,    0, SETVAL, sem_attr) == -1
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
            
            if(i<9) reader(w, r, mutexrc, priowriter, rc);
            else writer(w, r, mutexwc, wc);
            
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
            printf("son waiting error\n");
        //else printf("son %d finished\n", ret);
    }
    // delete semaphore
    printf("deleting semaphores...\n");
    ret = semctl(priowriter, 1, IPC_RMID);
    if(ret < 0)
        error("cant delete samaphore");
    
    ret = semctl(w, 1, IPC_RMID);
    if(ret < 0)
        error("cant delete samaphore");
    
    ret = semctl(r, 1, IPC_RMID);
    if(ret < 0)
        error("cant delete samaphore");
    
    ret = semctl(mutexrc, 1, IPC_RMID);
    if(ret < 0)
        error("cant delete samaphore");
    
    ret = semctl(mutexwc, 1, IPC_RMID);
    if(ret < 0)
        error("cant delete samaphore");
    
    printf("father dies\n");
    return 0;
}
