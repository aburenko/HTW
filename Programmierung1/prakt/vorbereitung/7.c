#include<stdio.h>

#define N 10

void readArray(int *arr);
void readArray2(int *arr);
void oddevenmerge(int *src1, int* src2, int *resvec);
void output(int *arr, int size);

int main() {
    
    int vec1[N],vec2[N],resvec[2*N];
    readArray(vec1);
    readArray(vec2);
    oddevenmerge(vec1,vec2,resvec);
    puts("arr1: "); output(vec1, N);
    puts("arr2: "); output(vec2, N);
    puts("res arr: "); output(resvec, 2*N);
    return 0;
}

void readArray(int *arr) {
    int i=0;
    while(i<N) {
        scanf("%i",&arr[i]);
        printf("arr[%d]: %d\n", i,arr[i]);
        i++;
    } 
}

void readArray2(int *arr) {
    int i=0;
    char tmp;
    while(i<N && ((tmp=getchar())!='\n')) {
        arr[i] = atoi(&tmp);
        printf("arr[%d]: %d\n", i,arr[i]);
        i++;
    } 
}

void oddevenmerge(int *src1, int* src2, int *resvec) {
    int i=0;
    for(;i<N;i++) {
        resvec[2*i] = src1[i];
        resvec[2*i+1] = src2[i];
    }
}

void output(int *arr, int size) {
    int i = 0;
    while(i<size) {
        printf("%d ",arr[i]);
        i++;
    } 
    puts("");
}
