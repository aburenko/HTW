/*
 *
 * Name: Anton Burenko
 * s-Nummer: s76905
 * Studiengruppe: 17/041/01
 * Dozent: Prof. Dr.-Ing. Arnold Beck
 *
 * */
#include <stdio.h>
#include <ctype.h>
#include <stdint.h>
#include "namelist.h"

tMorph Morph;

t_list *listCreate() {
    t_list *list = malloc(sizeof(t_list));
    if (list == NULL) {
        puts("error malloc");
        exit(-1);
    }
    list->pfirst = (t_cnt *) NULL;
    return list;
}

void *getFirst(t_list *list) {
    if (list == NULL) return NULL;
    printf("namelist.c: getFirst() 1\n");
    list->pcurr = list->pfirst;
    printf("namelist.c: getFirst() 2\n");
    return list->pfirst;
}

void *getNext(t_list *list) {
    printf("namelist.c: getNext() 1\n");
    list->pcurr = list->pcurr->pnext;
    printf("namelist.c: getNext() 2\n");
    return list->pcurr;
}


void *getLast(t_list *list) {
    printf("namelist.c: getLast()\n");
    printf("namelist.c: getLast() 1\n");
    if (list == NULL) return NULL;
    printf("namelist.c: getLast() 2\n");
    t_cnt *tmpConnector;
    printf("namelist.c: getLast() 3 %s\n", list);
    for (tmpConnector = getFirst(list);
         tmpConnector->pnext != NULL;
         tmpConnector = getNext(list));
    printf("namelist.c: getLast() 4\n");
    return tmpConnector;
}

void insertBehindValue(t_list *list, void *valueNew) {
    t_cnt *connectorNew = malloc(sizeof(t_cnt));
    if (connectorNew == NULL) {
        puts("error malloc");
        exit(-1);
    }
    connectorNew->value = valueNew;
    connectorNew->pnext = NULL;
    if (list->pfirst == NULL) {
        list->pfirst = connectorNew;
    } else {
        t_cnt *connectorLast = getLast(list);
        connectorLast->pnext = connectorNew;
    }
}

void printList(t_list *list) {
    if (list->pfirst == NULL) return;
    list->pcurr = list->pfirst;
    do {
        // print?
        list->pcurr = list->pcurr->pnext;
    } while (list->pcurr != list->pfirst);
}

void initNameList(void) {
    printf("init name list was called\n");
    pConstList = listCreate();
    mainProc = pCurrProcedure = createProc(NULL);
}

// functions implementation
tBez *createBez(char *pBez) {
    printf("namelist.c: createBez() with bez %s\n", pBez);
    tBez *newBez = (tBez *) malloc(sizeof(tBez));
    printf("namelist.c: createBez() 1\n");
    if (newBez == NULL) {
        return NULL;
    }
    printf("namelist.c: createBez() 2\n");
    newBez->structType = bez_struct;
    printf("namelist.c: createBez() 2.1\n");
    newBez->pObj = 0;
    printf("namelist.c: createBez() 2.2\n");
    newBez->IdxProc = pCurrProcedure->IdxProc;
    printf("namelist.c: createBez() 2.3\n");
    newBez->pName = malloc(strlen(pBez) + 1);
    printf("namelist.c: createBez() 3\n");
    if (newBez->pName == NULL) {
        free(newBez);
        return NULL;
    } else {
        strcpy(newBez->pName, pBez);
        printf("namelist.c: strcopy %s\n", newBez->pName);
    }
    printf("namelist.c: 4\n");
    insertBehindValue(pCurrProcedure->childList, newBez);
    printf("namelist.c: 5 %s\n", newBez);
    return newBez;
}

tConst *createConst(long Val) {
    tConst *newConst = (tConst *) malloc(sizeof(tConst));
    if (newConst == NULL) {
        return FAIL;
    }
    newConst->Val = Val;
    newConst->Idx = idxCnstCounter;
    newConst->structType = const_struct;
    idxCnstCounter++;
    insertBehindValue(pConstList, newConst);
    return newConst;
}

tConst *searchConst(long Val) {
    t_cnt *tmpConnector;
    for (tmpConnector = (tConst *) getFirst(pConstList);
         tmpConnector != NULL && ((tConst *) tmpConnector->value)->Val != Val;
         tmpConnector = (tConst *) getNext(pConstList));
    if (tmpConnector == NULL) {
        return NULL;
    }
    return (tConst *) tmpConnector->value;
}

tVar *createVar(void) {
    printf("namelist.c: createVar()\n");
    tVar *pVar = (tVar *) malloc(sizeof(tVar));
    printf("namelist.c: createVar() 1\n");
    if (pVar == NULL) return NULL;
    printf("namelist.c: createVar() 2\n");
    pVar->Dspl = pCurrProcedure->SpzzVar;
    pVar->structType = var_struct;
    printf("namelist.c: createVar() 3\n");
    pCurrProcedure->SpzzVar += sizeof(int32_t);
    printf("namelist.c: createVar() 4\n");

    tBez *pBez = getLast(pCurrProcedure->childList);
    printf("namelist.c: createVar() 5\n");
    if (pBez == NULL) return NULL;
    printf("namelist.c: createVar() 6\n");
    pBez->pObj = pVar;
    printf("namelist.c: createVar() 7\n");
    return pVar;
}

tProc *createProc(tProc *pParent) {
    printf("namelist.c: createProc() 1\n");
    tProc *pP = (tProc *) malloc(sizeof(tProc));
    if (pP == NULL) {
        return NULL;
    }
    printf("namelist.c: createProc() 2\n");
    pP->structType = proc_struct;
    pP->IdxProc = idxProcCounter;
    printf("namelist.c: createProc() 3\n");
    idxProcCounter++;
    pP->pParent = pParent;
    printf("namelist.c: createProc() 4\n");
    pP->childList = listCreate();
    pP->pLLabl = listCreate();
    printf("namelist.c: createProc() 5\n");
    pP->SpzzVar = 0;
    pCurrProcedure = pP;
    printf("namelist.c: createProc() end\n");
    return pP;
}

tBez *searchBez(tProc *pProc, char *pBez) {
    printf("namelist.c: searchBez()\n");
    if (pProc->childList == NULL) {
        printf("namelist.c: searchBez() was null\n");
        return NULL;
    }

    tBez *tmpBez = NULL;
    t_cnt *tmpConnector = getFirst(pProc->childList);
    printf("namelist.c: searchBez() 1\n");
    while (tmpConnector != NULL) {
        tBez *tmpBez = (tBez *) tmpConnector->value;
        printf("namelist.c: searchBez() 1.1 %s\n", pBez);
        printf("namelist.c: searchBez() 1.2 %s\n", tmpBez->pName);
        if (strcmp(tmpBez->pName, pBez) == 0) {
            printf("namelist.c: searchBez() break\n");
            break;
        }
        printf("namelist.c: searchBez() iter\n");
        tmpConnector = getNext(pProc->childList);
    }
    printf("namelist.c: searchBez() 2\n");
    return tmpBez;
}

tBez *searchBezGlobal(char *pBez) {
    tProc *pPr = pCurrProcedure;
    tBez *pB;
    while (pPr != NULL && (pB = searchBez(pPr, pBez)) == NULL) {
        pPr = pPr->pParent;
    }
    return pB;
}

// Konstantenbezeichner
int Bl1(void) {
    printf("namelist.c: Konstantenbezeichner\n");
    tBez *pBez;
    pBez = searchBez(pCurrProcedure, (char *) Morph.Val.pStr);
    if (pBez != NULL) {
        return FAIL;
    } else if (createBez((char *) Morph.Val.pStr) != NULL) {
        return OK;
    } else {
        return FAIL;
    }
}

// Konstantenwert
int Bl2(void) {
    printf("namelist.c: Konstantenwert\n");
    tBez *pBez;
    tConst *pConst;
    pBez = getLast(pCurrProcedure->childList);
    if ((pConst = searchConst(Morph.Val.Num)) != 0) {
        pBez->pObj = pConst;
    } else {
        pConst = createConst(Morph.Val.Num);
        if (pConst == NULL) return FAIL;
        pBez->pObj = pConst;
    }
    return OK;
}

// Variablenbezeichner
int Bl3(void) {
    printf("namelist.c: Variablenbezeichner with Morph.Val.pStr %s\n", Morph.Val.pStr);
    tBez *pBez;
    printf("namelist.c: Variablenbezeichner 1\n");
    pBez = searchBez(pCurrProcedure, (char *) Morph.Val.pStr);
    printf("namelist.c: Variablenbezeichner 2\n");
    if (pBez != NULL) return FAIL;
    pBez = createBez(Morph.Val.pStr);
    printf("namelist.c: Variablenbezeichner 2.5\n");
    if (pBez == NULL) return FAIL;
    printf("namelist.c: Variablenbezeichner 3\n");
    tVar *pVar = createVar();
    printf("namelist.c: Variablenbezeichner 4\n");
    pBez->pObj = pVar;
    printf("namelist.c: Variablenbezeichner 5\n");
    pVar->Dspl = pCurrProcedure->SpzzVar;
    printf("namelist.c: Variablenbezeichner 6\n");
    pCurrProcedure->SpzzVar = pCurrProcedure->SpzzVar + 4;
    printf("namelist.c: Variablenbezeichner 7\n");
    return OK;
}

// Prozedurbezeichner
int Bl4(void) {
    printf("namelist.c: Prozedurbezeichner\n");
    tBez *pBez;
    pBez = searchBez(pCurrProcedure, (char *) Morph.Val.pStr);
    if (pBez != NULL) return FAIL;
    if (pBez = createBez((char *) Morph.Val.pStr) != NULL) {
        return OK;
    }
    tProc *pProc = createProc(pCurrProcedure);
    pBez->pObj = pProc;
    pCurrProcedure = pProc;
    return OK;
}

// Ende der Prozedurvereinbarung
int Bl5(void) {
    printf("namelist.c: Bl5\n");
    t_cnt *tmpConnector;
    for (tmpConnector = getFirst(pCurrProcedure->childList);
         tmpConnector != NULL;
         tmpConnector = getNext(pCurrProcedure->childList)) {
        free(tmpConnector->value);
    }
    printf("namelist.c: Bl5 after for\n");
    tProc *pTmpParentProcedure = pCurrProcedure->pParent;
    free(pCurrProcedure);
    pCurrProcedure = pTmpParentProcedure;
    printf("namelist.c: Bl5 Codegen\n");
    code(retProc);
    codeEndProcedure();
    printf("namelist.c: Bl5 End\n");
    return OK;
}

// Beginn des Anweisungsteils
int Bl6(void) {
    printf("%d", pCurrProcedure == NULL);
    printf("namelist.c: Bl6 pCurrProcedure->IdxProc: %d, pCurrProcedure->SpzzVar: %d\n", pCurrProcedure->IdxProc,
           pCurrProcedure->SpzzVar);
    code(entryProc, 0, pCurrProcedure->IdxProc, pCurrProcedure->SpzzVar);
    printf("namelist.c: Bl6 end\n");
    return OK;
}

// Endebehandlung
int pr1(void) {
    printf("namelist.c: pr1\n");
    Bl5();
    t_cnt *tmpConnector = getFirst(pConstList);
    while (tmpConnector != NULL) {
        tConst *pConst = tmpConnector->value;
        wr2ToCodeConst(pConst->Val);
        tmpConnector = getNext(pConstList);
    }
    printf("namelist.c: pr1 0.5\n");
    // write number of procedures at first place
    wr2ToCodeAtBegin(idxProcCounter);
    printf("namelist.c: pr1 1\n");
    writeToFile();
    return OK;
}

int fa1(void) {
    printf("namelist.c: fa1\n");
    tConst *pConst = searchConst(Morph.Val.Num);
    printf("namelist.c: after search const\n");
    if (pConst == NULL) {
        printf("namelist.c: fa1 0.5 create const\n");
        pConst = createConst(Morph.Val.Num);
    }
    printf("namelist.c: fa1 1\n");
    code(puConst, pConst->Idx);
    printf("namelist.c: fa1 2\n");
    return OK;
}

int st10(void) {
    code(putVal);
    return OK;
}