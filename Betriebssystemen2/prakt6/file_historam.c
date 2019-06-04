#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>      
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>


#define bin_number 32

int bin_counter[bin_number];


int get_file_length(char * file_path) {
    struct stat statbuf;
    // get length of file
    lstat(file_path, &statbuf);
    int length = statbuf.st_size;
    perror("length");
    return length;
}


void dir_search(int step, char *dir_name) {
    DIR *dir_pointer = opendir(dir_name);
    struct dirent *dir_entry;
    dir_entry = readdir(dir_pointer);
    perror("open and read");
    while(dir_entry != NULL)
    {
        unsigned char entry_type = dir_entry->d_type;
        char *entry_name = dir_entry->d_name;
        char name_next[1024];
        strcat(name_next, dir_name);
        strcat(name_next, "/");
        strcat(name_next, entry_name);
        
        printf("dir: %s\n", dir_name);
        printf("filename: %s\n", name_next);
        if(entry_type == DT_REG) {
            int file_length = get_file_length(name_next);
            int index = file_length / step;
            if(index >= bin_number) {
                printf("step is not large enough");
            }
            else {
                bin_counter[index]++;
            }
            printf("file length: %d\n", file_length);
        } 
        else if (entry_type == DT_DIR) {
            printf("next search\n");
            dir_search(step, name_next);
        }
        name_next[0] = '\0';
        dir_entry = readdir(dir_pointer);
        printf("\nnext eintrag\n");
    }
    perror("schleife");
}


int main(int argc, char* argv[]) {
    
    if(argc != 2) {
        printf("usage: <%s> <step>\n", argv[0]);
        return -1;
    }
    
    int step = atoi(argv[1]);
    char path[4096];
    getcwd(path, 4096);
    
    // init with 0's
    for(int i=0; i < bin_number; i++)
        bin_counter[i] = 0;
    perror("eingaben");
    
    dir_search(step, path);
    perror("search");
    
    for(int i=0; i < bin_number; i++) {
        printf("file size from %8d to %8d: %d\n", i*step, (i+1)*step, bin_counter[i]);
    }
        
    return 0;
}
