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
    printf("namelist.c: getFirst() 1\n");
    list->pcurr = list->pfirst;
    printf("namelist.c: getFirst() 2\n");
    return list->pfirst;
}

t_cnt *getNext(t_list *list) {
    printf("namelist.c: getNext() 1\n");
    list->pcurr = list->pcurr->pnext;
    printf("namelist.c: getNext() 2\n");
    return list->pcurr;
}


t_cnt *getLast(t_list *list) {
    printf("namelist.c: getLast()\n");
    printf("namelist.c: getLast() 1\n");
    if (list == NULL) return NULL;
    printf("namelist.c: getLast() 2\n");
    t_cnt *tmpConnector = getFirst(list);
    if (tmpConnector == NULL) {
        printf("namelist.c: getLast() tmpConnector was NULL 2.5\n");
        return NULL;
    }
    printf("namelist.c: getLast() 3\n");
    for (;
            tmpConnector->pnext != NULL;
            tmpConnector = getNext(list));
    printf("namelist.c: getLast() 4\n");
    return tmpConnector;
}

t_cnt *getPreLast(t_list *list) {
    printf("namelist.c: getPreLast()\n");
    printf("namelist.c: getPreLast() 1\n");
    if (list == NULL) return NULL;
    printf("namelist.c: getPreLast() 2\n");
    t_cnt *tmpConnector = getFirst(list);
    if (tmpConnector == NULL) {
        printf("namelist.c: getPreLast() tmpConnector was NULL 2.5\n");
        return NULL;
    }
    printf("namelist.c: getPreLast() 3\n");
    t_cnt *tmpConnectorPrevious = tmpConnector;
    while (tmpConnector->pnext != NULL) {
        tmpConnectorPrevious = tmpConnector;
        tmpConnector = getNext(list);
    }
    if (tmpConnectorPrevious == tmpConnector) {
        printf("namelist.c: was equal!!() 4\n");
        exit(-10);
    }
    printf("namelist.c: getPreLast() 4\n");
    return tmpConnectorPrevious;
}

void printBezeichnerList(t_list *list) {
    printf("bez listing: start\n");
    if (list == NULL) {
        printf("bez list was null\n");
        return;
    }
    t_cnt *tmpConnector = getFirst(list);
    if (tmpConnector == NULL) {
        printf("first elem was null\n");
        return;
    }
    while (tmpConnector != NULL) {
        tBez *pBez = (tBez *) tmpConnector->value;
        printf("bez listing: %s\n", pBez->pName);
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
    printf("namelist.c: 5 %s\n", newBez->pName);
    return newBez;
}

void testPCurrProcedure(void) {
    printf("namelist.c: testPCurrProcedure TEST BEGIN\n");
    printBezeichnerList(pCurrProcedure->childList);
    getLast(pCurrProcedure->childList);
    getFirst(pCurrProcedure->childList);
    tBez *pBezTmp = searchBez(pCurrProcedure, "C");
    printBezeichnerList(pCurrProcedure->childList);
    printf("namelist.c: testPCurrProcedure TEST END\n");
}

tConst *createConst(long Val) {
    printf("namelist.c: createConst with val %ld\n", Val);
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

    t_cnt *pConn = getLast(pCurrProcedure->childList);
    tBez *pBez = pConn->value;
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
    if (pProc == NULL) {
        printf("namelist.c: searchBez() pProc was null\n");
        return NULL;
    }
    if (pProc->childList == NULL) {
        printf("namelist.c: searchBez() pProc->childList was null\n");
        return NULL;
    }
//    printBezeichnerList(pProc->childList);
    tBez *tmpBez = NULL;
    t_cnt *tmpConnector = getFirst(pProc->childList);
    if (tmpConnector == NULL) {
        return NULL;
    }
    printf("namelist.c: searchBez() 1\n");
    while (tmpConnector != NULL) {
        tmpBez = (tBez *) tmpConnector->value;
        printf("namelist.c: searchBez() 1.1 %s = %s ?\n", pBez,  tmpBez->pName);
        if (strcmp(tmpBez->pName, pBez) == 0) {
            printf("namelist.c: searchBez() found a match, break\n");
            return tmpBez;
            break;
        }
        printf("namelist.c: searchBez() iter\n");
        tmpConnector = getNext(pProc->childList);
    }
    printf("namelist.c: searchBez() nothihg found\n");
    return NULL;
}

tBez *searchBezGlobal(char *pBez) {
    printf("namelist.c: search global %s\n", pBez);
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
    printf("namelist.c: Konstantenbezeichner\n");
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
    printf("namelist.c: Bl2 Konstantenwert END\n");
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
    printf("namelist.c: Variablenbezeichner 7\n");
    return OK;
}

// Prozedurbezeichner
int Bl4(void) {
    printf("namelist.c: Bl4 Prozedurbezeichner\n");
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
    printf("namelist.c: Bl4 Prozedurbezeichner with number %d created\n", pCurrProcedure->IdxProc);
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
    if (tmpPrevConnector != NULL)
    {
        free(tmpPrevConnector);
    }
    printf("namelist.c: Bl5 after for\n");
    printf("namelist.c: Bl5 Codegen\n");
    code(retProc);
    codeEndProcedure();
    printf("namelist.c: Bl5 End\n");
    if (pCurrProcedure->pParent != NULL) {
        pCurrProcedure = pCurrProcedure->pParent;
    }
    return OK;
}

// Beginn des Anweisungsteils
int Bl6(void) {
    printf("bl6 %d\n", pCurrProcedure == NULL);
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

int fa2(void) {
    printf("namelist.c: fa2\n");
    tBez *pBez = searchBezGlobal(Morph.Val.pStr);
    if (pBez == NULL) {
        printf("can not find bezeichner %s", Morph.Val.pStr);
        exit(-6);
    }
    if (pBez->structType == proc_struct) {
        printf("non valid type of struct %d", pBez->structType);
        exit(-7);
    }

    tConst *pConst = (tConst *) pBez->pObj;
    if (pConst->structType == const_struct) {
        code(puConst, pConst->Idx);
    } else if (pConst->structType == var_struct) {
        tVar *pVar = (tVar *) pBez->pObj;
        int procedureWhereFound= pBez->IdxProc;
        if (procedureWhereFound == 0) {
            code(puValVrMain, pVar->Dspl);
        } else if (procedureWhereFound == pCurrProcedure->IdxProc) {
            code(puValVrLocl, pVar->Dspl);
        } else {
            code(puValVrGlob, pVar->Dspl, pCurrProcedure->IdxProc);
        }
    } else {
        printf("non valid type of struct %d", pBez->structType);
        exit(-8);
    }
    return OK;
}

int st1(void) {
    printf("namelist.c: st1\n");
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
    if (pVar->structType != var_struct) {
        printf("non valid type of struct %d", pVar->structType);
        exit(-7);
    }
    int procedureWhereFound = pBez->IdxProc;
    if (procedureWhereFound == 0) {
        code(puAdrVrMain, pVar->Dspl);
    } else if (procedureWhereFound == pCurrProcedure->IdxProc) {
        code(puAdrVrLocl, pVar->Dspl);
    } else {
        code(puAdrVrMain, pVar->Dspl, pCurrProcedure->IdxProc);
    }
    return OK;
}


int st2(void) {
    printf("namelist.c: st2\n");
    code(storeVal);
    return OK;
}

tLabl *createLabel(tStructType structType, char *iJump) {
    tLabl *labl = (tLabl *) malloc(sizeof(tLabl));
    labl->structType = structType;
    labl->iJmp = iJump;
    return labl;
}

int st3(void) {
    printf("st3\n");
    tLabl *labl = createLabel(jnot_struct, getPCode());
    insertBehindValue(pLabelList, labl);
    code(jnot, 0);
    return OK;
}

int st4(void) {
    printf("st4\n");
    tLabl *label = (tLabl *) getLast(pLabelList)->value;
    short relativeAddress = getPCode() - label->iJmp;
    if (label->structType == jnot_struct) {
        relativeAddress -= 3;
    }
    // save the relative adress
    wr2ToCodeAtP(relativeAddress, label->iJmp + 1);
    return OK;
}

int st5(void) {
    printf("st5 beschreibt anfang einer condition\n");
    tLabl *labl = createLabel(st5_struct, getPCode());
    insertBehindValue(pLabelList, labl);
    return OK;
}

int st6(void) {
    printf("st6\n");
    tLabl *labl = createLabel(jnot_struct, getPCode());
    insertBehindValue(pLabelList, labl);
    code(jnot, 0);
    return OK;
}

int st7(void) {
    printf("st7\n");
    tLabl *label = (tLabl *) getLast(pLabelList)->value;
    short relativeAddress = getPCode() - label->iJmp;
    wr2ToCodeAtP(relativeAddress, label->iJmp + 1);
    label = (tLabl *) getPreLast(pLabelList)->value;
    code(jmp, label->iJmp - getPCode() - 3);
    return OK;
}

int st8(void) {
    printf("namelist.c: st8\n");
    tBez *pBez = searchBezGlobal(Morph.Val.pStr);
    if (pBez == NULL) {
        printf("can not find bezeichner %s", Morph.Val.pStr);
        exit(-6);
    }
    printf("namelist.c: st8 middle\n");
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
    printf("namelist.c: st8 end\n");
    return OK;
}

int st9(void) {
    printf("namelist.c: st9\n");
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
    if (pVar->structType != var_struct) {
        printf("not var: non valid type of struct %d", pVar->structType);
        exit(-7);
    }
    int procedureWhereFound = pBez->IdxProc;
    if (procedureWhereFound == 0) {
        code(puAdrVrMain, pVar->Dspl);
    } else if (procedureWhereFound == pCurrProcedure->IdxProc) {
        code(puAdrVrLocl, pVar->Dspl);
    } else {
        code(puAdrVrMain, pVar->Dspl, pCurrProcedure->IdxProc);
    }
    code(getVal);
    return OK;
}

int st10(void) {
    printf("namelist.c: st10\n");
    code(putVal);
    return OK;
}

int ex1(void) { // negative sign
    printf("namelist.c: ex1\n");
    code(vzMinus);
    return OK;
}

int ex2(void) { // addition
    printf("namelist.c: ex2\n");
    code(OpAdd);
    return OK;
}

int ex3(void) {  // subtraction
    printf("namelist.c: ex3\n");
    code(OpSub);
    return OK;
}

int te1(void) { // mul
    printf("namelist: te1\n");
    code(OpMult);
    return OK;
}

int te2(void) { // div
    printf("namelist: te2\n");
    code(OpDiv);
    return OK;
}

int co1(void) {
    printf("namelist: co1\n");
    code(odd);
    return OK;
}

tMorph compareOperator;

int co2_to_co7(void) {
    printf("namelist: co2_to_co7\n");
    compareOperator = Morph;
    return OK;
}

int co8(void) {
    printf("namelist: co8\n");
    switch (compareOperator.MC) {
        case mcSymb :
            if (compareOperator.Val.Symb == zLE) {
                printf("co8 Symbol <=\n");
                code(cmpLE);
            }
            else if (compareOperator.Val.Symb == zGE) {
                printf("co8 Symbol >=\n");
                code(cmpGE);
            }
            else if (isprint(compareOperator.Val.Symb)) {
                printf("co8 Symbol %c\n", (char) compareOperator.Val.Symb);
                if (compareOperator.Val.Symb == '=') {
                    code(cmpEQ);
                } else if(compareOperator.Val.Symb == '#') {
                    code(cmpNE);
                } else if(compareOperator.Val.Symb == '<') {
                    code(cmpLT);
                } else if(compareOperator.Val.Symb == '>') {
                    code(cmpGT);
                }
            }
            else {
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