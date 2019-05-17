#include<stdio.h>
#include<stdlib.h>

int main() {
    int array[] = {1,2,1};
    printf("Your array: %s\n", array);
    
    int *p=array; //vom Datentyp abhängig
    
    printf("*p'c': %c || *p'p': %p\n", *p, *p);
    printf("===========================\n");
    printf(" p   'p' : %p\n", p);
    printf(" *p++ 'd' : %d\n", *p++);
    printf(" p   'p' : %p\n", p);
    printf("===========================\n");
    printf(" p   'p' : %p\n", p);
    printf(" p++\n"); p++;
    printf(" p   'p' : %p\n", p);
    return 0;
}
