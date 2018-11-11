#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"../func.h"

#define DB "unitDB.csv"
#define DBBU "unitDBBackUp.csv"

int listWriteInDB() { //write list into DB
    FILE *streamOriginal = fopen(DB, "r"); // open in "r" for copy into backUp 
    if(streamOriginal == NULL) { printf("ERROR in opening file : listWriteInDB\n"); return -1;}
    
    listCreateDBBackUP(streamOriginal);
    
    freopen(DB, "w", streamOriginal); // erase all content 
    if(streamOriginal == NULL) { printf("ERROR in reopening file : listWriteInDB\n"); return -1;}
    
    tcnt * pointerWhile = list->pfirst;
    char stringTmp[sizeof(unit)+3*sizeof(",")+sizeof("\n")]; 
    while(pointerWhile != NULL) { //loop the list
        sprintf(stringTmp,"%s,%d,%d\n",
                 pointerWhile->pdata->unitName,
                 pointerWhile->pdata->unitID,
                 pointerWhile->pdata->unitCount
        );
        fputs(stringTmp, streamOriginal);
        pointerWhile = pointerWhile->pnxt;
    }
    
    fclose(streamOriginal);
    return 0;
}

int listReadFromDB() { // compile file into list
    FILE *streamOriginal = fopen(DB, "r");    
    if(streamOriginal == NULL) { printf("ERROR in opening file : listReadFromDB\n"); return -1;}
    
    char *ptr;
    char line[1024];
    while(fgets(line, 1024, streamOriginal)){ // get line from file
        unit * unitC;
        unitC = malloc(sizeof(unit));
        ptr = strtok(line, ","); // get first line element
        int i = 1;
        while(ptr != NULL){
            unitWriteParameter(i, unitC, ptr);
            ptr = strtok(NULL, ","); // get next -||- 
            i++;
        }
        insLast(unitC);
    }
    fclose(streamOriginal);
    
    return 0;
}

int listCreateDBBackUP(FILE *streamOriginal) { // create Back Up
    FILE * streamBackUp = fopen(DBBU, "w");
    if(streamBackUp == NULL) { printf("ERROR in opening file listCreateDBBackUP\n"); return -1;}
    
    char ch;
    while((ch = getc(streamOriginal)) != EOF)
         putc(ch, streamBackUp); // put char to char
    
    fclose(streamBackUp);
    return 0;
}

int listFree() {
    tcnt *ptrTmp = list->pfirst;
    tcnt *ptrPrevTmp = NULL;
    while(ptrTmp != NULL) { // loop elements
        ptrPrevTmp = ptrTmp;
        ptrTmp = ptrTmp->pnxt;
        free(ptrPrevTmp); // free unit's memory
    }
    free(list); // free list's memory
    return 0;
}

void listOutput() {
    tcnt * pointerWhile = list->pfirst;
    while(pointerWhile != NULL) { // loop elements
        printf("%-30s %-6d %-6d\n",
            pointerWhile->pdata->unitName,
            pointerWhile->pdata->unitID,
            pointerWhile->pdata->unitCount
        );
        pointerWhile = pointerWhile->pnxt; // set to next
    }
}