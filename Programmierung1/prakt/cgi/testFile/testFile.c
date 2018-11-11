#include<stdio.h>
#include<stdlib.h>

#define DB "unitDB.csv"
#define DBBU "unitDBBackUp.csv"

int main() {
    
    puts("Content-type:text/html\n\n");
    FILE * stream = fopen("unitDB.csv", "r");
    if(stream == NULL) {
        fprintf(stderr, "ERROR");
    }
    char a[100];
    fgets(a,100,stream);
    puts(a);
    
    fclose(stream);

    FILE * stream2 = fopen("unitDB.csv", "r");
    if(stream2 == NULL) {
        fprintf(stderr, "ERROR");
    }
    char b[100];
    fgets(b,100,stream2);
    puts(a);
    
    stream2 = freopen("unitDB.csv", "w", stream2);
    if(stream2 == NULL) {
        fprintf(stderr, "ERROR");
    }
    
    fputs("abosrach", stream2);
    
    fclose(stream2);
    
    return 0;
}