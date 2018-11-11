#include<string.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

int *merge(int *src1, int s1, int *src2, int s2) {
    int *result = malloc(s1+s2+sizeof(int));
    int c,i;
    for(c=0;c<s1/sizeof(int);c++) {
        result[c] = src1[c];
    }    
    for(i=0;i<s2/sizeof(int);i++,c++) {
        result[c] = src2[i];
    }
    result[c] = '\0';
    return result;
}

int main() {
    int arr1[] = {1,2,3,4};
    int arr2[] = {5,6,7,8};
    int *res = merge(arr1,sizeof(arr1),arr2,sizeof(arr2));
    int i;
    for(i=0;res[i] != '\0';i++) {
        printf("%d",res[i]);
    }
    printf("\n");
    return 0;
}

