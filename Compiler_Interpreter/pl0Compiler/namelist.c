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
#include <langinfo.h>
#include "namelist.h"

tMorph Morph;

t_list *listCreate() {
    t_list *list = malloc(sizeof(t_list));
    if (list == NULL) {
        puts("error malloc");
        exit(-1);
    }
    list->pfirst = NULL;
    list->pcurr = NULL;
    return list;
}

t_cnt *getFirst(t_list *list) {
    if (list == NULL) return NULL;
    list->pcurr = list->pfirst;
    return list->pfirst;
}

t_cnt *getNext(t_list *list) {
//    printf("namelist.c: getNext() 1\n");
    list->pcurr = list->pcurr->pnext;
//    printf("namelist.c: getNext() 2\n");
    return list->pcurr;
}


t_cnt *getLast(t_list *list) {
    if (list == NULL) return NULL;
    t_cnt *tmpConnector = getFirst(list);
    if (tmpConnector == NULL) {
        return NULL;
    }
    for (;
            tmpConnector->pnext != NULL;
            tmpConnector = getNext(list));
    return tmpConnector;
}


int getListSize(t_list *list) {
    t_cnt * pcurrtemp = list->pcurr;
    if (list == NULL) exit(-3);
    t_cnt *tmpConnector = getFirst(list);
    if (tmpConnector == NULL) {
        return 0;
    }
    int counter = 1;
    for (;
            tmpConnector->pnext != NULL;
            tmpConnector = getNext(list)) {
        counter++;
    }
    list->pcurr = pcurrtemp;
    return counter;
}

// n begins with 1
t_cnt *getNumberNFromEnd(t_list *list, int n) {
    if (list == NULL) return NULL;
    t_cnt *tmpConnector = getFirst(list);
    if (tmpConnector == NULL) {
        return NULL;
    }
    int size = getListSize(list);
    if (size == 1 || n > size) {
        printf("false usage %d, %d", n, size);
        exit(-1);
    }
    int neededElementIndex = size - n;
    int counter = 0;
    for (;
            tmpConnector->pnext != NULL;
            tmpConnector = getNext(list))
    {
        if (counter == neededElementIndex) break;
        counter++;
    }
    return tmpConnector;
}

t_cnt *getPreLast(t_list *list) {
    if (list == NULL) return NULL;
    t_cnt *tmpConnector = getFirst(list);
    if (tmpConnector == NULL) {
        printf("namelist.c: getPreLast() tmpConnector was NULL 2.5\n");
        return NULL;
    }
    t_cnt *tmpConnectorPrevious = tmpConnector;
    while (tmpConnector->pnext != NULL) {
        tmpConnectorPrevious = tmpConnector;
        tmpConnector = getNext(list);
    }
    return tmpConnectorPrevious;
}

void removeLast(t_list *list) {
    t_cnt * preLast = getPreLast(list);
    if (preLast->pnext != NULL) {
        free(preLast->pnext->value);
    }
    free(preLast->pnext);
    preLast->pnext = NULL;
}

void printBezeichnerList(t_list *list) {
    if (list == NULL) {
        return;
    }
    t_cnt *tmpConnector = getFirst(list);
    if (tmpConnector == NULL) {
        return;
    }
    while (tmpConnector != NULL) {
        tmpConnector = getNext(list);
    }
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

void initNameList(void) {
    printf("init name list was called\n");
    pConstList = listCreate();
    pLabelList = listCreate();
    mainProc = pCurrProcedure = createProc(NULL);
}

tLabl *createLabel(tStructType structType, char *iJump) {
    tLabl *label = (tLabl *) malloc(sizeof(tLabl));
    label->structType = structType;
    label->iJmp = iJump;
    return label;
}

// functions implementation
tBez *createBez(char *pBez) {
    tBez *newBez = (tBez *) malloc(sizeof(tBez));
    if (newBez == NULL) {
        return NULL;
    }
    newBez->structType = bez_struct;
    newBez->pObj = 0;
    newBez->IdxProc = pCurrProcedure->IdxProc;
    newBez->pName = malloc(strlen(pBez) + 1);
    if (newBez->pName == NULL) {
        free(newBez);
        return NULL;
    } else {
        strcpy(newBez->pName, pBez);
    }
    insertBehindValue(pCurrProcedure->childList, newBez);
    return newBez;
}

void testPCurrProcedure(void) {
    printBezeichnerList(pCurrProcedure->childList);
    getLast(pCurrProcedure->childList);
    getFirst(pCurrProcedure->childList);
    printBezeichnerList(pCurrProcedure->childList);
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
    for (tmpConnector = getFirst(pConstList);
         tmpConnector != NULL && ((tConst *) tmpConnector->value)->Val != Val;
         tmpConnector = getNext(pConstList));
    if (tmpConnector == NULL) {
        return NULL;
    }
    return (tConst *) tmpConnector->value;
}

tVar *createVar(void) {
    tVar *pVar = (tVar *) malloc(sizeof(tVar));
    if (pVar == NULL) return NULL;
    pVar->Dspl = pCurrProcedure->SpzzVar;
    pVar->structType = var_struct;
    pCurrProcedure->SpzzVar += sizeof(int32_t);

    t_cnt *pConn = getLast(pCurrProcedure->childList);
    tBez *pBez = pConn->value;
    if (pBez == NULL) return NULL;
    pBez->pObj = pVar;
    return pVar;
}

tConst *findOrCreateConst(long value) {
    tConst *pConst = searchConst(value);
    if (pConst != NULL) {
        return pConst;
    }
    pConst = createConst(value);
    if (pConst == NULL) {
        printf("failed creating a constant");
        exit(-10);
    }
    return pConst;
}

void generateVariableAddress(tBez *pBez) {
    tVar *pVar = (tVar *) pBez->pObj;
    int procedureWhereFound = pBez->IdxProc;
    if (procedureWhereFound == 0) {
        code(puAdrVrMain, pVar->Dspl);
    } else if (procedureWhereFound == pCurrProcedure->IdxProc) {
        code(puAdrVrLocl, pVar->Dspl);
    } else {
        code(puAdrVrGlob, pVar->Dspl, pCurrProcedure->IdxProc);
    }
}

void generateVariableValue(tBez *pBez) {
    tVar *pVar = (tVar *) pBez->pObj;
    int procedureWhereFound = pBez->IdxProc;
    if (procedureWhereFound == 0) {
        code(puValVrMain, pVar->Dspl);
    } else if (procedureWhereFound == pCurrProcedure->IdxProc) {
        code(puValVrLocl, pVar->Dspl);
    } else {
        code(puValVrGlob, pVar->Dspl, pCurrProcedure->IdxProc);
    }
}

void generateIndex() {
    // push index
    if (Morph.arrayIndexType == 1) {
        printf("generateIndex 1 %ld\n", Morph.arrayIndex.index);
        tConst *pConst = findOrCreateConst(Morph.arrayIndex.index);
        printf("generateIndex const index was %d\n ", pConst->Idx);
        code(puConst, pConst->Idx);
        printf("generateIndex const end\n");
    } else if (Morph.arrayIndexType == 2) {
        printf("generateIndex 2 %s\n", Morph.arrayIndex.ident);
        tBez *pIndexBez = searchBezGlobal(Morph.arrayIndex.ident);
        tConst *pIndexConst = (tConst *) pIndexBez->pObj;
        if (pIndexConst->structType == const_struct) {
            code(puConst, pIndexConst->Idx);
        } else if (pIndexConst->structType == var_struct) {
            generateVariableValue(pIndexBez);
        }
    } else {
        printf("non valid type of array index %d", Morph.arrayIndexType);
        exit(-7);
    }
}

void generateArrayBlock() {
    generateIndex();
    tConst *pConst = findOrCreateConst(4);
    code(puConst, pConst->Idx);
    code(OpMult);
    code(OpAddAddr);
}

tArr *createArrayVar(void) {
    tArr *pArrVar = (tArr *) malloc(sizeof(tArr));
    if (pArrVar == NULL) return NULL;
    pArrVar->Dspl = pCurrProcedure->SpzzVar;
    pArrVar->structType = arr_struct;
    // get size of array
    if (Morph.arrayIndexType == 1) {
        pArrVar->size = Morph.arrayIndex.index;
    } else {
        printf("namelist.c: createArrayVar(), array index can not be variable when initializing\n");
        exit(-17);
    }
    pCurrProcedure->SpzzVar += pArrVar->size * sizeof(int32_t);
    t_cnt *pConn = getLast(pCurrProcedure->childList);
    tBez *pBez = pConn->value;
    if (pBez == NULL) return NULL;
    pBez->pObj = pArrVar;
    return pArrVar;
}

tProc *createProc(tProc *pParent) {
    tProc *pP = (tProc *) malloc(sizeof(tProc));
    if (pP == NULL) {
        return NULL;
    }
    pP->structType = proc_struct;
    pP->IdxProc = idxProcCounter;
    idxProcCounter++;
    pP->pParent = pParent;
    pP->childList = listCreate();
    pP->pLLabl = listCreate();
    pP->SpzzVar = 0;
    pCurrProcedure = pP;
    return pP;
}

tBez *searchBez(tProc *pProc, char *pBez) {
    printf("namelist.c: searchBez()\n");
    if (pProc == NULL) {
        printf("namelist.c: searchBez() pProc was null\n");
        return NULL;
    }
    if (pProc->childList == NULL) {
        printf("namelist.c: searchBez() pProc->childList was null\n");
        return NULL;
    }
    tBez *tmpBez = NULL;
    t_cnt *tmpConnector = getFirst(pProc->childList);
    if (tmpConnector == NULL) {
        return NULL;
    }
    while (tmpConnector != NULL) {
        tmpBez = (tBez *) tmpConnector->value;
        if (strcmp(tmpBez->pName, pBez) == 0) {
            return tmpBez;
            break;
        }
        tmpConnector = getNext(pProc->childList);
    }
    return NULL;
}

tBez *searchBezGlobal(char *pBez) {
    if (pCurrProcedure == NULL) {
        return NULL;
    }
    tProc *pPr = pCurrProcedure;
    tBez *pB = NULL;
    while (pPr != NULL) {
        pB = searchBez(pPr, pBez);
        if (pB != NULL) {
            break;
        }
        pPr = pPr->pParent;
    }
    return pB;
}

// Konstantenbezeichner
int Bl1(void) {
    tBez *pBez;
    pBez = searchBez(pCurrProcedure, (char *) Morph.Val.pStr);
    if (pBez != NULL) {
        return FAIL;
    } else {
        pBez = createBez((char *) Morph.Val.pStr);
        if (pBez != NULL) {
            return OK;
        } else {
            return FAIL;
        }
    }
}

// Konstantenwert
int Bl2(void) {
    printf("namelist.c: Bl2 Konstantenwert\n");
    t_cnt *pConnector = getLast(pCurrProcedure->childList);
    tBez *pBez = (tBez *) pConnector->value;
    tConst *pConst = searchConst(Morph.Val.Num);
    if (pConst != NULL) {
        pBez->pObj = pConst;
    } else {
        pConst = createConst(Morph.Val.Num);
        if (pConst == NULL) return FAIL;
        pBez->pObj = pConst;
    }
    return OK;
}

// Variablenbezeichner, auch für arrays
int Bl3(void) {
    printf("namelist.c: Variablenbezeichner with Morph.Val.pStr %s\n", Morph.Val.pStr);
    tBez *pBez;
    pBez = searchBez(pCurrProcedure, (char *) Morph.Val.pStr);
    if (pBez != NULL) return FAIL;
    pBez = createBez(Morph.Val.pStr);
    if (pBez == NULL) return FAIL;
    if (Morph.arrayIndexType == 0) { // normal var
        tVar *pVar = createVar();
        if (pVar == NULL) return FAIL;
    } else {
        tArr *pArr = createArrayVar();
        if (pArr == NULL) return FAIL;
    }
    printf("namelist.c: Variablenbezeichner 7\n");
    return OK;
}

// Prozedurbezeichner
int Bl4(void) {
    printf("namelist.c: Bl4 Prozedurbezeichner %p\n", getPCode());
    tBez *pBez;
    pBez = searchBez(pCurrProcedure, (char *) Morph.Val.pStr);
    if (pBez != NULL) return FAIL;
    pBez = createBez((char *) Morph.Val.pStr);
    if (pBez == NULL) {
        printf("namelist.c: Bl4 failed creating Bezeichner\n");
        exit(-1);
    }
    tProc *pProc = createProc(pCurrProcedure);
    pBez->pObj = pProc;
    pCurrProcedure = pProc;
    return OK;
}

// Ende der Prozedurvereinbarung
int Bl5(void) {
    printf("namelist.c: Bl5 for procedure number %d\n", pCurrProcedure->IdxProc);
    t_cnt *tmpConnector = NULL;
    t_cnt *tmpPrevConnector = NULL;
    for (tmpConnector = getFirst(pCurrProcedure->childList);
         tmpConnector != NULL;
         tmpConnector = getNext(pCurrProcedure->childList)) {
        free(tmpConnector->value);
        free(tmpPrevConnector);
        tmpPrevConnector = tmpConnector;
    }
    if (tmpPrevConnector != NULL) {
        free(tmpPrevConnector);
    }
    code(retProc);
    codeEndProcedure();
    if (pCurrProcedure->pParent != NULL) {
        pCurrProcedure = pCurrProcedure->pParent;
    }
    return OK;
}

// Beginn des Anweisungsteils
int Bl6(void) {
    printf("bl6 %d\n", pCurrProcedure == NULL);
    code(entryProc, 0, pCurrProcedure->IdxProc, pCurrProcedure->SpzzVar);
    return OK;
}

// Endebehandlung
int pr1(void) {
    printf("namelist.c: pr1 %p\n", getPCode());
    Bl5();
    t_cnt *tmpConnector = getFirst(pConstList);
    while (tmpConnector != NULL) {
        tConst *pConst = tmpConnector->value;
        wr2ToCodeConst(pConst->Val);
        tmpConnector = getNext(pConstList);
    }
    wr2ToCodeAtBegin(idxProcCounter);
    writeToFile();
    return OK;
}

// factor numeral
int fa1(void) {
    printf("namelist.c: fa1 %p\n", getPCode());
    tConst *pConst = searchConst(Morph.Val.Num);
    if (pConst == NULL) {
        pConst = createConst(Morph.Val.Num);
    }
    code(puConst, pConst->Idx);
    return OK;
}

// factor ident
int fa2(void) {
    printf("namelist.c: fa2 %p\n", getPCode());
    tBez *pBez = searchBezGlobal(Morph.Val.pStr);
    if (pBez == NULL) {
        exit(-6);
    }
    if (pBez->structType == proc_struct) {
        exit(-7);
    }

    tConst *pConst = (tConst *) pBez->pObj;
    if (pConst->structType == const_struct) {
        code(puConst, pConst->Idx);
    } else if (pConst->structType == var_struct) { // variable
        generateVariableValue(pBez);
    } else if (pConst->structType == arr_struct) { // array
        // push address
        generateVariableAddress(pBez);
        // generate the rest of array block
        generateArrayBlock();
        code(swap);
    } else {
        exit(-8);
    }
    return OK;
}

// Linke Seite der Zuweisung
int st1(void) {
    printf("namelist.c: st1 %p\n", getPCode());
    tBez *pBez = searchBezGlobal(Morph.Val.pStr);
    if (pBez == NULL) {
        printf("can not find bezeichner %s", Morph.Val.pStr);
        exit(-6);
    }
    if (pBez->structType == proc_struct) {
        printf("non valid type of struct %d", pBez->structType);
        exit(-7);
    }
    tVar *pVar = (tVar *) pBez->pObj;
    if (pVar->structType == var_struct) {
        generateVariableAddress(pBez);
    } else if (pVar->structType == arr_struct) {
        generateVariableAddress(pBez);
        generateArrayBlock();
    } else {
        printf("non valid type of struct %d", pVar->structType);
        exit(-7);
    }
    return OK;
}

// Rechte Seite der Zuweisung
int st2(void) {
    printf("namelist.c: st2 %p\n", getPCode());
    code(storeVal);
    return OK;
}

// Prozeduraufruf
int st8(void) {
    printf("namelist.c: st8\n");
    tBez *pBez = searchBezGlobal(Morph.Val.pStr);
    if (pBez == NULL) {
        exit(-6);
    }
    tProc *pProc = (tProc *) pBez->pObj;
    if (pProc == NULL) {
        printf("procedure bezeichner was found, but object was null!!");
        exit(-6);
    }
    if (pProc->structType != proc_struct) {
        printf("non valid type of struct %d", pBez->structType);
        exit(-7);
    }
    code(call, pProc->IdxProc);
    return OK;
}

// Eingabe ?
int st9(void) {
    printf("namelist.c: st9 %p\n", getPCode());
    tBez *pBez = searchBezGlobal(Morph.Val.pStr);
    if (pBez == NULL) {
        printf("can not find bezeichner %s", Morph.Val.pStr);
        exit(-6);
    }
    if (pBez->structType == proc_struct) {
        printf("not proc: non valid type of struct %d", pBez->structType);
        exit(-7);
    }
    tVar *pVar = (tVar *) pBez->pObj;
    if (pVar->structType == var_struct) {
        generateVariableAddress(pBez);
    } else if (pVar->structType == arr_struct) {
        generateVariableAddress(pBez);
        generateArrayBlock();
    } else {
        printf("not var: non valid type of struct %d", pVar->structType);
        exit(-7);
    }
    code(getVal);
    return OK;
}

// Ausgabe
int st10(void) {
    printf("namelist.c: st10\n");
    code(putVal);
    return OK;
}

// if
// if, nach Condition
int st3(void) {
    printf("st3\n");
    tLabl *labl = createLabel(jnot_struct, getPCode());
    insertBehindValue(pLabelList, labl);
    code(jnot, 0);
    return OK;
}

// if, nach Statement
int st4(void) {
    printf("st4\n");
    tLabl *label = (tLabl *) getLast(pLabelList)->value;
    short relativeAddress = getPCode() - label->iJmp;
    if (label->structType == jnot_struct) {
        relativeAddress -= 3;
    }
    // save the adress
    wr2ToCodeAtP(relativeAddress, label->iJmp + 1);
    return OK;
}

// loops
// while
int st5(void) {
    printf("st5 beschreibt anfang einer condition rest5 %p\n", getPCode());
    tLabl *labl = createLabel(st5_struct, getPCode());
    insertBehindValue(pLabelList, labl);
    return OK;
}

// while, nach Condition
int st6(void) {
    printf("rest6 %p\n", getPCode());
    tLabl *labl = createLabel(jnot_struct, getPCode());
    insertBehindValue(pLabelList, labl);
    code(jnot, 0);
    return OK;
}

// while, nach Statement
int st7(void) {
    printf("rest7 %p\n", getPCode());
    tLabl *label = (tLabl *) getLast(pLabelList)->value;
    if (label->structType != jnot_struct) {
        printf("not jnot_struct");
        exit(-1);
    }
    int extension  = getBufferExtension();
    short relativeAddress = getPCode() - label->iJmp - extension;
    printf("relative adresse %d %d p:%p label:%p\n", relativeAddress, extension, getPCode(), label->iJmp);
    wr2ToCodeAtP(relativeAddress, label->iJmp + extension + 1);
    removeLast(pLabelList);

    label = (tLabl *) getLast(pLabelList)->value;
    if (label->structType != st5_struct) {
        printf("not st5_struct");
        exit(-1);
    }
    code(jmp, label->iJmp - getPCode() + extension - 3);
    removeLast(pLabelList);
    return OK;
}

int ex1(void) { // negative sign
    printf("namelist.c: ex1 %p\n", getPCode());
    code(vzMinus);
    return OK;
}

int ex2(void) { // addition
    printf("namelist.c: ex2 %p\n", getPCode());
    code(OpAdd);
    return OK;
}

int ex3(void) {  // subtraction
    printf("namelist.c: ex3 %p\n", getPCode());
    code(OpSub);
    return OK;
}

int te1(void) { // mul
    printf("namelist: te1 %p\n", getPCode());
    code(OpMult);
    return OK;
}

int te2(void) { // div
    printf("namelist: te2 %p\n", getPCode());
    code(OpDiv);
    return OK;
}

int co1(void) {
    printf("namelist: co1 %p\n", getPCode());
    code(odd);
    return OK;
}

tMorph compareOperator;

int co2_to_co7(void) {
    printf("namelist: co2_to_co7 %p\n", getPCode());
    compareOperator = Morph;
    return OK;
}

int co8(void) {
    printf("namelist: co8 %p\n", getPCode());
    switch (compareOperator.MC) {
        case mcSymb :
            if (compareOperator.Val.Symb == zLE) {
                printf("co8 Symbol <=\n");
                code(cmpLE);
            } else if (compareOperator.Val.Symb == zGE) {
                printf("co8 Symbol >=\n");
                code(cmpGE);
            } else if (isprint(compareOperator.Val.Symb)) {
                printf("co8 Symbol %c\n", (char) compareOperator.Val.Symb);
                if (compareOperator.Val.Symb == '=') {
                    code(cmpEQ);
                } else if (compareOperator.Val.Symb == '#') {
                    code(cmpNE);
                } else if (compareOperator.Val.Symb == '<') {
                    code(cmpLT);
                } else if (compareOperator.Val.Symb == '>') {
                    code(cmpGT);
                }
            } else {
                printf("ERROR Symbol \n");
            }
            break;
        case mcNum :
            printf("ERROR Zahl %ld\n", compareOperator.Val.Num);
            break;
        case mcIdent:
            printf("ERROR Ident %s\n", (char *) compareOperator.Val.pStr);
            break;
        case mcEmpty:
            printf("ERROR mcEmpty\n");
            break;
    }
    return OK;
}