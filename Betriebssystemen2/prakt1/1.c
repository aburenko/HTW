#include <stdio.h>
#include <stdlib.h>       
#include <sys/types.h> 
#include <sys/wait.h>
#include <unistd.h>

#define FILENAME "zahl.dat"
#define LOOPNUM 100

void routine() {
    FILE *f;
    
    int ret, i, value;
    
    for(i=0; i<LOOPNUM; i++) {
        printf("lauf nr %d with pid %d\n", i, getpid());
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
            printf("value %d\n", value);
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
    
    FILE *f = fopen(FILENAME, "wt");
    fprintf(f, "0");
    fclose(f);
    
    int i, ret;
    int forkNum = 5;
    
    for(i=0; i<forkNum; i++) {
        
        ret = fork();
    
        if(ret < 0) {
            printf("error in fork\n");
            return -1;
        }
        // son
        else if(ret == 0) {
            printf("son born\n");
            routine();
            printf("exit\n");
            exit(0);
        }
    }
    // father
    if (ret != 0) {
        printf("father waits\n");
        ret = wait(NULL);
        if(ret < 0)
            printf("son proccess error\n");
        else
            printf("son %d finished\n", ret);
        printf("father dies\n");
    }
    return 0;
}
