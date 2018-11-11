#include<stdlib.h>
#include<stdio.h>

int main(int argc, char *argv[]) {
    
    if(argc!=2) {
        printf("usage %s <dateiname>\n", argv[0]);
        exit(-1);
    }
    printf("file: %s\n", argv[1]);
    FILE *file = fopen(argv[1], "rb");
    if(file == NULL) {
        printf("file open error\n");
        exit(-1);
    }
    
    fseek(file,0,SEEK_END);
    long fileSize = ftell(file);
    rewind(file);
    
    int i;
    char v;
    for(i=0; i<fileSize/sizeof(char); i++) {
        fread(&v,sizeof(char),1,file);
        if(v != '.')
            printf("%c",v);
        else
            printf("<STOP>");
    }
    
    
    return 0;
}
