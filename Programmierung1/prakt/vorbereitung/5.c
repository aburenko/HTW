#include<stdio.h>

int main()  {
    
    int x,f = 1;
    scanf("%d",&x);
    do {
        f*=x;
        x--;
    } while(x>0);
    printf("f: %d\n", f);
    return 0;
}
