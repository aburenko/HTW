#include<string.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

int mergeStrings(char *dest, char *src1, char *src2) {
    strcpy(dest,src1);
    strcat(dest,src2);
    return 0;
}

char *mergeStringsMalloc(char *src1, char *src2) {
    char *res = (char*)malloc(11*sizeof(char));
    strcpy(res,src1);
    strcat(res,src2);
    return res;
}

int main() {
    printf("%d\n",n*sizeof(int)+1);
    char result[10];
    char string1[] = "abc";
    char string2[] = "xyz";
    if( ( sizeof(string1) + sizeof(string2) ) > sizeof(result)) {
        puts("result strign is too small");
        return -1;
    }
    mergeStrings(result, string1, string2);
    puts(result);  
    
    strcpy(result,mergeStringsMalloc(string1, string2));
    puts(result);

    return 0;
}

