#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>   
#include <sys/types.h> 
#include <sys/wait.h>
#include <string.h>

#include <sys/ipc.h>
#include <sys/msg.h>

#include <sys/stat.h>

#include <sys/mman.h>
#include <fcntl.h>



int main () {
    // open file to copy from
    int filedesc = open("a.text", O_RDONLY);
    if(filedesc < 0) {
        perror("fileopen");
        return 1;
    }
    struct stat *statbuf;
    // get length of file
    fstat(filedesc, statbuf);
    int length = statbuf->st_size;
    
    // open destination file
    int fddest = open("dest.text", O_APPEND | O_CREAT | O_WRONLY);
    if(fddest < 0) {
        perror("fileopen");
        return 1;
    }
    
    void *pmap = mmap(0, length, filedesc, MAP_SHARED, PROT_READ,0);
    if(MAP_FAILED == pmap){
        perror("pmap");
        return 1;
    }
    void *pmapdest = mmap(0, length, fddest, MAP_SHARED, PROT_READ,0);    
    if(MAP_FAILED == pmapdest){
        perror("pmapdest");
        return 1;
    }

    void *retcpy = memcpy(pmap,pmapdest,length);
    
    int un = munmap(pmap, length);
    if(un < 0) {
        perror("un pmap");
        return 1;
    }
    
    un = munmap(pmapdest, length);
    if(un < 0) {
        perror("un pmapdest");
        return 1;
    }
    
    exit(EXIT_SUCCESS);
}
