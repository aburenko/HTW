#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>      
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>


int main(int argc, char* argv[]) {
    
    FILE *file = fopen("test.txt","r+");
    if (file == NULL) {
        perror("file");
    }  
    
    printf("try to seek\n");
    if (!fseek(file, 5, SEEK_SET)) {
        perror("seek");
    }
    
    printf("try to write\n");
    if(!fprintf(file, "zzz")) {
        perror("fprintf");
    }
    
    fclose(file);
    
    
    return 0;
}
 
