/*beleg.c*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"func.h"

int main() {
    printHead();
    
    listCreate();
    proccessPosted();
    printBody();
    
    listWriteInDB();
    listFree();
    
    return 0;
}

/*
 modules:
 ->funcPrintCGI.c 
 ->funcListDB.c
 ->funcListMan.c
*/
