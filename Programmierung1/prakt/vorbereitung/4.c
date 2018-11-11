#include<stdio.h>
#include<stdlib.h>
#include <string.h>

#define DELIM " "

void sort(int *vector, int vSize);
void output(int *vector, int vSize);

char buf[128];

int main() {
    FILE *file=fopen("zahlen.txt", "r");
    if(file==NULL) {
        puts("error fileopen");
        exit(-1);
    }
    int vector[128], i, b;
    fgets(buf, 128, file);

    char *ptoken=strtok(buf, DELIM);
    for(i=0; ptoken;i++) {
        vector[i] = atoi(ptoken);
        printf("i:%d number:%d pointer:%d\n", i, vector[i], ptoken);
        ptoken=strtok(NULL, DELIM);
    }
    
    sort(vector, i);
    output(vector, i);
    
    
    if((file=freopen("zahlen.txt","w",file))==NULL) {
        puts("error fileREopen");
        exit(-1);
    }
    
    printf("es %d:%d\n",0, vector[0]);
    for(b=0; b<i; b++) {
        printf("%d:%d\n",b, vector[b]);
        if(b!=i-1) fprintf(file, "%d ", vector[b]);
        else fprintf(file, "%d\0", vector[b]);
    }
        
    puts(" ");
    fclose(file);
    return 0;
}

void sort(int *vector, int vSize) {
    int i, o, tmp; // i=innere o=äußere Pfeile
    for(o=0; o<vSize-1; o++) { // Pfeile o läuft bis zum vSize-1
        for(i=o+1; i<vSize; i++) { // und mit allen Elementen i=o+1
            if(vector[o]>vector[i]) { // vergleichen, wenn Element o groeser als i
                //wechseln die Elementen
                tmp = vector[o];
                vector[o] = vector[i];
                vector[i] = tmp;
            }
        }
    }
}

void output(int *vector, int vSize) {
    int i;
    for(i=0; i<vSize; i++) {
        printf("%d ",vector[i]);
    }
    puts(" ");
}
