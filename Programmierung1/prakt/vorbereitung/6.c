#include<stdio.h>

int main() {
    int i;
    puts("++i:");
    for(i=0;i<6;++i) {
        printf("%d ", i);
    }
    puts("\ni++:");
    for(i=0;i<6;i++) {
        printf("%d ", i);
    }
    puts(" ");
    return 0;
}
