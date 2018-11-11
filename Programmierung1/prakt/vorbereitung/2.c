#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define VSIZE 25

void read();
void mirror();
void mirrorV();
void output();

char vector[VSIZE];
char buf[128];

int main() {
    read();
    mirror();
    output();
    return 0;
}

void read() {
    fgets(vector,VSIZE,stdin);
    vector[strlen(vector)-1] = 0; 
}

void mirror() {
    char tmp;
    int i,end;
    end = strlen(vector);
    for(i=0;i<end/2; i++) {
        tmp = vector[i];
        vector[i] = vector[end-i-1];
        vector[end-i-1] = tmp;
    }
}

void mirrorV() {
    char vectorM[VSIZE];
    int i,end;
    end = strlen(vector);
    for(i=0;i<end; i++) {
        vectorM[i] = vector[end-i-1];
    }
    for(i=0;i<end; i++) {
        vector[i] = vectorM[i];
    }
}

void output() {
    int end,i;
    end = strlen(vector);
    for(i=0;i<end; i++) {
        printf("%c",vector[i]);
    }
    puts("");
}
