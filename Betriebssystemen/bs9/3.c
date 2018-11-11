#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define READIDX 0
#define WRITEIDX 1
#define FILENAME test.txt
char buf[128];

int main() {
    int pipes_f[2],pipef_s[2];
    pid_t ret;
    
    ret = fork();
    // if fork() failed
    if(ret == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    // son
    else if(ret == 0) {
        close(pipes_f[READIDX]);
        close(pipef_s[WRITEIDX]);
        
        write(pipes_f[WRITEIDX],'a',1);
        
        close(pipes_f[WRITEIDX]);
        close(pipef_s[READIDX]);
    }
    // father
    else{
        close(pipes_f[WRITEIDX]);
        close(pipef_s[READIDX]);
        char a;
        read(pipes_f[READIDX],a,1);
        printf("%c",a);
        close(pipes_f[READIDX]);
        close(pipef_s[WRITEIDX]);
    }
    return 0;
}
