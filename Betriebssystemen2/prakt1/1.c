#include <stdio.h>
#include <stdlib.h>       
#include <sys/types.h> 
#include <sys/wait.h>
#include <unistd.h>

#define FILENAME "zahl.dat"
#define LOOPNUM 20000

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
    
    
    for(i=0; i<forkNum; i++) {
        
        ret_t = fork();
    
        if(ret_t < 0) {
            printf("error in fork\n");
            return -1;
        }
        // son
        else if(ret_t == 0) {
            printf("son born\n");
            routine();
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
    printf("father dies\n");
    return 0;
}
