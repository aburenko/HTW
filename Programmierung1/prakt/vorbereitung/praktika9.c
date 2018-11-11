#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define len (20+1)

char arrN[][len] = {"Max", "Moritz", "Bolte", "Hans Huckebein", "Helene", "Antonius", "Boeck", "Maecke", "Lempel", "Schlich"};

int size = sizeof(arrN)/(len*sizeof(char));

void sort(char *arr) {
    int i,o;
    char tmp[len];
    for(o=0;o<size-1;o++) {
        for(i=o+1; i<size; i++) {
            if(strcmp(arr[o],arr[i]) > 0) {
                strcpy(tmp,arr[o]);
                strcpy(arr[o],arr[i]);
                strcpy(arr[i],tmp);
            }
        }
    }
}

void printarr(char *arr) {
    int i = 0;
    for(;i<size;i++) {
        printf("%s\n", 
            arr[i]
        );
    }
    puts("");
}

// void addelement(char *vbuf, char *arr, int num) {
//     arr = realloc(arr,(sizeof(arrN)+len));
//     printf("%d", sizeof(arr));
//     //memmove(,,sizeof());
//     size
// }

typedef char tStr[16];
int main() {
    tStr *parr[len] = malloc(sizeof(arrN));
    memcpy(parr,arrN,sizeof(arrN));
    
    char vbuf[] = "Franz"; 
    
//     addelement(vbuf, parr,3);
    sort(parr);
    printarr(parr);
    free(parr);
    return 0;
}