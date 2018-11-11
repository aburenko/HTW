#include<stdlib.h>
#include<stdio.h>

int main(int argc, char *argv[]) {
    
    if(argc!=2) {
        printf("usage %s <dateiname>\n", argv[0]);
        exit(-1);
    }
    printf("file: %s\n", argv[1]);
    FILE *file = fopen(argv[1], "r");
    if(file == NULL) {
        printf("file open error\n");
        exit(-1);
    }
    
    int b;
    while((b=fgetc(file))!=EOF) {
        if(b!='.') printf("%c",b);
        else printf("<STOP>");
    }
    puts("");
    return 0;
}
