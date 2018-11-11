#include<stdio.h>
#include<stdlib.h>
#include<string.h>


    
int main() {
    char posted[256] = "insLast=0&1=Name&2=7&3=77\n";
    posted[strlen(posted)-1] = 0;
    printf("string: %s\n", posted);
    char * ptr = NULL;
    int i= 0;
    ptr = strtok(posted, "&");
    printf("string: %s\n", ptr);
    while(i<=2) { // loop parameters
        ptr = strtok(NULL, "=");
        ptr = strtok(NULL, "&");
        printf("string: %s\n", ptr);
        i++;
    }
}