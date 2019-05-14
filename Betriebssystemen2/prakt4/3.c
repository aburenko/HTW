#include <stdio.h>
#include <unistd.h>


int main () {
    unsigned long ret = (unsigned long)sbrk(1024*4096);
    unsigned long len = 0;
    
    printf("anfang: %d\n", ret);
    
    while(ret != -1) {
        len = ret;
        ret = (unsigned long)sbrk(1024*4096);
    }
    
    printf("ende: %d\n", len);
        
    
    return 0;
}
