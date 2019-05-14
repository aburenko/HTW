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

#include <sys/types.h>
#include <unistd.h>


int main () {
    // open file to copy from
    int filedesc = open("a.text", O_RDONLY);
    if(filedesc < 0) {
        perror("fileopen first");
        return 1;
    }
    struct stat *statbuf;
    // get length of file
    fstat(filedesc, statbuf);
    int length = statbuf->st_size;
    printf("%d\n", length);
    
    // open destination file
    int fddest = open("dest.text", O_CREAT | O_RDWR, 0600);
    if(fddest < 0) {
        perror("fileopen dest");
        return 1;
    }
    lseek(fddest, length-1, SEEK_SET);
    write(fddest, "\0" , 1);
    
    
    void *pmap = mmap(0, length, PROT_READ, MAP_SHARED, filedesc, 0);
    if(MAP_FAILED == pmap){
        perror("pmap");
        return 1;
    }
    void *pmapdest = mmap(0, length, PROT_READ|PROT_WRITE, MAP_SHARED, fddest, 0);    
    if(MAP_FAILED == pmapdest){
        perror("pmapdest");
        return 1;
    }
    void *retcpy = memcpy(pmapdest,pmap,length);
    
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
