#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define VSIZE 25

void read();
void mirror();
void output();

int vector[VSIZE+1];
char buf[VSIZE+1];

int main() {
    read();
    mirror();
    output();
    return 0;
}

void read() {
    fgets(buf,VSIZE,stdin);
    int i;
    char tmp;
    for(i=0;i<strlen(buf)-1;i++) {
        tmp=buf[i];
        vector[i] = atoi(&tmp);
    }
    vector[i] = '\0';
}

void mirror() {
    int tmp;
    int i,end = 0;
    while(vector[end] != '\0')
        end++;
    for(i=0;i<end/2; i++) {
        tmp = vector[i];
        vector[i] = vector[end-i-1];
        vector[end-i-1] = tmp;
    }
}

void output() {
    int end,i;
    end = sizeof(vector)/sizeof(int);
    for(i=0;i<end && vector[i]!='\0'; i++) {
        printf("%d",vector[i]);
    }
    puts("");
}
