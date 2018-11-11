#include<stdio.h>
#include<stdlib.h>

char buff[128];

int main () {

    int i1;
    unsigned int u1;
    int i2;
    unsigned int u2;    

    printf("Geben Sie erstes Integer ein: ");
    fgets(buff, 128, stdin);
    i1 = atoi(buff);    
    u1 = atoi(buff);    
    
    printf("Geben Sie zweites Integer ein: ");
    fgets(buff, 128, stdin);
    i2 = atoi(buff);    
    u2 = atoi(buff);    
    
    printf("i1: _d_  %d      _u_ %u               _x_ %x\n", i1, i1, i1);
    printf("i2: _d_ %d      _u_ %u      _x_ %x\n", i2, i2, i2);

    printf("u1: _d_  %d      _u_ %u               _x_ %x\n", u1, u1, u1);
    printf("u2: _d_ %d      _u_ %u      _x_ %x\n", u2, u2, u2);
    
    printf("----------------------------------------------\n");
    
    i1 >>= 1;
    i2 >>= 2;
    printf("i1>>1: %d --- i2>>2: %d\n", i1, i2);
    i1 <<= 1;
    i2 <<= 2;
    printf("i1<<1: %d --- i2<<2: %d\n", i1, i2);

    printf("----------------------------------------------\n");
    
    unsigned int a = -12;
    a >>= 2; 
    printf("a: %d\n", a);

    unsigned int c = 12;
    c >>= 1; 
    printf("c: %d\n", c);

    printf("----------------------------------------------\n");
    
    int b1 = 4;
    int b2 = 4;
    b1 <<= 3;
    b2 <<= 1;
    printf("b1: %d, b2: %d, b1 + b2: %d\n", b1, b2, b1+b2);
  
    return 0;
}
