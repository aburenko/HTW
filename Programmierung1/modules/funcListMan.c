#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"../func.h"

void listCreate() { // create a new list
    list = malloc(sizeof(tlist));
    if(list)
        list->pfirst = list->plast = NULL;
    else
        fprintf(stderr, "ERROR in function listCreate: no memory\n");
    listReadFromDB(); // fill from DB
}

void listSortBy(char type) {
    if(list->pfirst == NULL || list->pfirst->pnxt == NULL)
        return;
    // outer loop
    tcnt *ptrOutL = list->pfirst;
    tcnt *ptrOutLPrev = NULL;
    // inner loop
    tcnt *ptrInnL = ptrOutL->pnxt;
    tcnt *ptrInnLPrev = NULL;
    // help varibles
    int compare = 0; // 0-right 1-to replace
    while(ptrOutL != list->plast) // up to n-1 
    {
        ptrInnL = ptrOutL->pnxt;
        while(ptrInnL != NULL) // up to n
        {   
            if(type == 'N') {
//                 if(strcmp(ptrOutL->pdata->unitName, ptrInnL->pdata->unitName) > 0)
//                     compare = 1;
                //simplifications
                char *OutN = ptrOutL->pdata->unitName;
                char *InnN = ptrInnL->pdata->unitName;
                // compare character to charecter in lower case
                int i = 0;
                while(charToLow(OutN[i]) == charToLow(InnN[i])) {
                    if(OutN[i+1] == '\0' || InnN[i+1] == '\0') { // avoid checking out of arrays
                        break;
                    }
                    i++;
                }
                // check 
                if(charToLow(OutN[i]) > charToLow(InnN[i]))
                    compare = 1;
            }
            else if(type == 'I') {
                if(ptrOutL->pdata->unitID > ptrInnL->pdata->unitID)
                    compare = 1;
            }
            else if(type == 'C') {
                if(ptrOutL->pdata->unitCount > ptrInnL->pdata->unitCount)
                    compare = 1;
            }
//             printf("<br>ptrOutL:%d :: ptrInnL:%d :: compare:%d",ptrOutL->pdata->unitID, ptrInnL->pdata->unitID,compare);
            if(compare) {
                unit *ptrUnitTmp = ptrInnL->pdata;
                ptrInnL->pdata = ptrOutL->pdata;
                ptrOutL->pdata = ptrUnitTmp;
                return listSortBy(type);
            }
            ptrInnLPrev = ptrInnL; 
            ptrInnL = ptrInnL->pnxt;
        }
        ptrOutLPrev = ptrOutL;
        ptrOutL = ptrOutL->pnxt;
    }
    return;
}

int insFirst(unit * m) {
    tcnt * tcntTmp = malloc(sizeof(tcnt));
    if(!tcntTmp){
        fprintf(stderr, "ERROR in function insFirst, no memory");
        return -1;
    }
    tcntTmp->pdata = m;
    // set pointer variables in the list 
    if(list->pfirst == NULL)
        list->plast = tcntTmp; // if list is empty
    tcntTmp->pnxt = list->pfirst;
    list->pfirst = tcntTmp;
    
    return 0;
}

int insLast(unit * m) {
    tcnt * tcntTmp = malloc(sizeof(tcnt));
    if(!tcntTmp){
        fprintf(stderr, "ERROR in function insLast, no memory");
        return -1;
    }
    tcntTmp->pdata = m;
    // set pointer variables in the list     
    if(list->pfirst == NULL)
        list->pfirst = tcntTmp; // if list is empty
    else
        list->plast->pnxt = tcntTmp;
    list->plast = tcntTmp;
    tcntTmp->pnxt = NULL; 
    
    return 0;
}

int insert(unit *m, int elementNumber) {
    int i=0;
    tcnt *pointerWhile = list->pfirst;
    // loop to element of element number
    while( i<elementNumber && pointerWhile->pnxt != NULL ) { 
        i++;
        pointerWhile = pointerWhile->pnxt;
    } 
    // end of or empty list
    if( pointerWhile == NULL || pointerWhile->pnxt == NULL) 
        return insLast(m);
    else 
        return insAfter(m, pointerWhile);
    
    return 0;
}

int insAlpha(unit * m) {
    char *unitNameTmp = m->unitName;
    // search the alphabetish previos element
    tcnt *ptrTmp = list->pfirst;
    tcnt *ptrPrevTmp = NULL;
    while(ptrTmp != NULL) { 
        if(strcmp(ptrTmp->pdata->unitName, unitNameTmp) > 0) break;
        ptrPrevTmp = ptrTmp;
        ptrTmp = ptrTmp->pnxt;
    } 
    // choose how to insert
    if(ptrTmp == NULL) return insLast(m); // if end of the list 
    else if(ptrTmp == list->pfirst) insFirst(m); // if start of the list
    else return insAfter(m, ptrPrevTmp);
    
    return 0;
}

int insAfter(unit *m, tcnt * tcntPrev) {
    tcnt * tcntTmp = malloc(sizeof(tcnt));  
    if(!tcntTmp) {
        fprintf(stderr, "ERROR in function insFirst, no memory\n");
        return -1; 
    }
    // set pointer variables in the list 
    tcntTmp->pnxt = tcntPrev->pnxt;
    tcntPrev->pnxt = tcntTmp;
    if(tcntTmp->pnxt == NULL) list->plast = tcntTmp;
    tcntTmp->pdata = m;
    
    return 0;
}

int listChangeParameter(unit * m, int option) {
    //get Parameter
    printf("Your Parameter for %d:", option);
    fgets(buf, 31, stdin);
    //write into unit "m"
    if(!unitWriteParameter(option, m, buf)) return -1;
    
    return 0;
}

int deleteElement(int elementNummer){
    tcnt * pointerWhile = list->pfirst;
    if(pointerWhile == NULL) { // List is empty
        fprintf(stderr, "ERROR in funtion deleteElement: List is empty\n");
        return -1;
    }
    
    tcnt * pointerWhilePrev = NULL;
    int i = 0;
    while(pointerWhile != NULL && i<elementNummer) { // loop elements
        pointerWhilePrev = pointerWhile;
        pointerWhile = pointerWhile->pnxt;
        i++;
    }
    
    if(pointerWhile == NULL) { // elementNummer is overlooping the list
        fprintf(stderr, "ERROR in funtion deleteElement: pointerWhile is NULL, after looping\n");
        return -1;
    }
    
    if(pointerWhilePrev == NULL && pointerWhile->pnxt == NULL) { // there is only one element in list
        list->plast = pointerWhilePrev;
        list->pfirst = pointerWhile->pnxt;
    }
    else if(pointerWhilePrev == NULL) { // first element
        list->pfirst = pointerWhile->pnxt;
    }
    else if(pointerWhile->pnxt == NULL) { // last element
        list->plast = pointerWhilePrev;
        pointerWhilePrev->pnxt = pointerWhile->pnxt;
    }
    else { // !first && !last
        pointerWhilePrev->pnxt = pointerWhile->pnxt;
    }
    // free the memory of this element
    free(pointerWhile->pdata);
    free(pointerWhile);
    return 0;
}

unit * putUnit() {
    int i;
    unit * unitTmp = malloc(sizeof(unit));
    for(i=1; i<=3; i++) {
        fgets(buf,128,stdin); // get element
        buf[strlen(buf)-1] = 0;
        // write in unit and check return
        if(unitWriteParameter(i, unitTmp, buf)) {
            puts("Error in unitWriteParameter");
            exit(-1);
        }
    }
    return unitTmp;
}

int unitWriteParameter(int option, unit *u, char *ptr) {
    // choose option
    switch(option) {
        case 1:
            strcpy(u->unitName, ptr);
            break;
        case 2:
            u->unitID=atoi(ptr);
            break;
        case 3:
            u->unitCount=atoi(ptr);
            break;
        default:
            return -1;
    }
    return 0;
}

int unitCopyParameter(int option, unit *dest, tcnt *src) {
    // choose option
    switch(option) {
        case 1:
            strcpy(dest->unitName, src->pdata->unitName);
            break;
        case 2:
            dest->unitID = src->pdata->unitID;
            break;
        case 3:
            dest->unitID = src->pdata->unitCount;
            break;
        default:
            return -1;
    }
    return 0;
}