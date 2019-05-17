#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char buf[25+1];
char line[1024];

int wordCount[11+1];

int main() {
    printf("File to open: ");
    fgets(buf,26,stdin);
    buf[strlen(buf)-1]=0;
    FILE *stream = fopen("irrtum.txt"/*buf*/, "r");
    if(stream == NULL) {
        fprintf(stderr, "ERROR file was not found");
        return -1;
    } 
    char *tptr;
    while(fgets(line, 1024, stream)) {
        line[strlen(line)-1] = 0;
        puts(line);
        tptr = strtok(line," ,.");
        while(tptr != NULL) {
            if(strlen(tptr)<11) {
                wordCount[strlen(tptr)] = wordCount[strlen(tptr)] +1;
            } else {
                wordCount[11] = wordCount[11] + 1;
            }
            
            
            tptr = strtok(NULL," ,.");
        }
    }
    int i;
    for(i=1; i<11; i++) 
        printf("%d: %d  gefunden\n", i, wordCount[i]);
    printf("Sonstiges: %d gefunden\n", wordCount[11]);
    
    return 0;
}
