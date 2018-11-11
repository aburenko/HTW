#include<stdio.h>
#include<stdlib.h>
#include"func.h"

int main()
{
    student a = {"Burenko Anton", 47433, 1.5, 2};
    printf("%s\n", a.name);

    uniLong u = {0xA};
    
    printf("ld:%ld\nlx:%lx\n", u.l, u.l);
    printf("%s\n", u.bc);
    return 0;
}
