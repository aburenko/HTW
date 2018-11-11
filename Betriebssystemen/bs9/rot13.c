#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char buf[128];

char getRot13(char c) {
    char start, limit;
    if('A'<=c && 'Z'>=c) {
        start='A';
        limit='Z';
    }
    else if ('a'<=c && 'z'>=c) {
        start='a';
        limit='z';
    }
    else {
        return c;
    }
    
    if( (c+13) <= limit ) {
        return c+13;
    }
    else
        return c-13;
}

int main() {
    fgets(buf,128,stdin);
    
    int i;
    for(i=0;i<strlen(buf)-1; i++) {
        buf[i]=getRot13(buf[i]);
    }
    
    printf("%s",buf);
    
    return 0;
}
