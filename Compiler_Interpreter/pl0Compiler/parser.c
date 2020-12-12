/*
 *
 * Name: Anton Burenko
 * s-Nummer: s76905
 * Studiengruppe: 17/041/01
 * Dozent: Prof. Dr.-Ing. Arnold Beck
 *
 * */
#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

tBog gTerm[] = {
/* 0*/ {BgGr, {(ul) gFact}, NULL, 1, 3},
/* 1*/
       {BgSy, {(ul) '*'},   NULL, 0, 2},
/* 2*/
       {BgSy, {(ul) '/'},   NULL, 0, 0},
/* 3*/
       {BgEn, {(ul) 0},     NULL, 0, 0}
};

tBog gExpr[] = {
/* 0*/ {BgSy, {(ul) '+'},   NULL, 3, 1},
/* 1*/
       {BgSy, {(ul) '-'},   NULL, 3, 2},
/* 2*/
       {BgGr, {(ul) gTerm}, NULL, 4, 0},
/* 3*/
       {BgGr, {(ul) gTerm}, NULL, 4, 0},
/* 4*/
       {BgNl, {(ul) NULL},  NULL, 5, 9},
/* 5*/
       {BgSy, {(ul) '+'},   NULL, 7, 6},
/* 6*/
       {BgSy, {(ul) '-'},   NULL, 8, 0},
/* 7*/
       {BgGr, {(ul) gTerm}, NULL, 4, 0},
/* 8*/
       {BgGr, {(ul) gTerm}, NULL, 4, 0},
/* 9*/
       {BgEn, {(ul) 0},     NULL, 0, 0}
};

tBog gFact[] = {
/* 0*/ {BgMo, {(ul) mcIdent}, NULL, 5, 1},
/* 1*/
       {BgMo, {(ul) mcNum},   NULL, 5, 2},
/* 2*/
       {BgSy, {(ul) '('},     NULL, 3, 0},
/* 3*/
       {BgGr, {(ul) gExpr},   NULL, 4, 0},
/* 4*/
       {BgSy, {(ul) ')'},     NULL, 5, 0},
/* 5*/
       {BgEn, {(ul) 0},       NULL, 0, 0}
};

tBog gCondition[] = {
/* 0*/ {BgSy, {(ul) zODD},  NULL, 2,  1},
/* 1*/
       {BgGr, {(ul) gExpr}, NULL, 3,  0},
/* 2*/
       {BgGr, {(ul) gExpr}, NULL, 10, 0},
/* 3*/
       {BgSy, {(ul) '='},   NULL, 9,  4},
/* 4*/
       {BgSy, {(ul) '#'},   NULL, 9,  5},
/* 5*/
       {BgSy, {(ul) '<'},   NULL, 9,  6},
/* 6*/
       {BgSy, {(ul) zLE},   NULL, 9,  7},
/* 7*/
       {BgSy, {(ul) '>'},   NULL, 9,  8},
/* 8*/
       {BgSy, {(ul) zGE},   NULL, 9,  0},
/* 9*/
       {BgGr, {(ul) gExpr}, NULL, 10, 0},
/* 10*/
       {BgEn, {(ul) 0},     NULL, 0,  0}
};

tBog gStatement[] = {
/* 0*/ {BgMo, {(ul) mcIdent},    NULL, 7,  1},
/* 1*/
       {BgSy, {(ul) zIF},        NULL, 8,  2},
/* 2*/
       {BgSy, {(ul) zWHL},       NULL, 9,  3},
/* 3*/
       {BgSy, {(ul) zBGN},       NULL, 16, 4},
/* 4*/
       {BgSy, {(ul) zCLL},       NULL, 10, 5},
/* 5*/
       {BgSy, {(ul) '?'},        NULL, 11, 6},
/* 6*/
       {BgSy, {(ul) '!'},        NULL, 12, 0},
/* 7*/
       {BgSy, {(ul) zERG},       NULL, 13, 0},
/* 8*/
       {BgGr, {(ul) gCondition}, NULL, 14, 0},
/* 9*/
       {BgGr, {(ul) gCondition}, NULL, 15, 0},
/* 10*/
       {BgMo, {(ul) mcIdent},    NULL, 21, 0},
/* 11*/
       {BgMo, {(ul) mcIdent},    NULL, 21, 0},
/* 12*/
       {BgGr, {(ul) gExpr},      NULL, 21, 0},
/* 13*/
       {BgGr, {(ul) gExpr},      NULL, 21, 0},
/* 14*/
       {BgSy, {(ul) zTHN},       NULL, 18, 0},
/* 15*/
       {BgSy, {(ul) zDO},        NULL, 19, 0},
/* 16*/
       {BgGr, {(ul) gStatement}, NULL, 17, 20},
/* 17*/
       {BgSy, {(ul) ';'},        NULL, 16, 20},
/* 18*/
       {BgGr, {(ul) gStatement}, NULL, 21, 0},
/* 19*/
       {BgGr, {(ul) gStatement}, NULL, 21, 0},
/* 20*/
       {BgSy, {(ul) zEND},       NULL, 21, 0},
/* 21*/
       {BgEn, {(ul) 0},          NULL, 0,  0}
};

tBog gBlock[] = {
/* 0*/ {BgSy, {(ul) zCST},       NULL, 2,  1},
/* 1*/
       {BgNl, {(ul) NULL},       NULL, 7,  0},
/* 2*/
       {BgMo, {(ul) mcIdent}, Bl1,     3,  0}, // Bl1
/* 3*/
       {BgSy, {(ul) '='},        NULL, 4,  0},
/* 4*/
       {BgMo, {(ul) mcNum},   Bl2,     0,  0}, // Bl2
/* 5*/
       {BgSy, {(ul) ','},        NULL, 2,  0},
/* 6*/
       {BgSy, {(ul) ';'},        NULL, 7,  0},
/* 7*/
       {BgSy, {(ul) zVAR},       NULL, 9,  8},
/* 8*/
       {BgNl, {(ul) NULL},       NULL, 12, 0},
/* 9*/
       {BgMo, {(ul) mcIdent}, Bl3,     10, 0}, // Bl3
/* 10*/
       {BgSy, {(ul) ','},        NULL, 9,  11},
/* 11*/
       {BgSy, {(ul) ';'},        NULL, 12, 0},
/* 12*/
       {BgSy, {(ul) zPRC},    NULL,     14, 13}, // Bl4
/* 13*/
       {BgNl, {(ul) NULL},    Bl5,     18, 0}, // Bl5
/* 14*/
       {BgMo, {(ul) mcIdent},    Bl4, 15, 0},
/* 15*/
       {BgSy, {(ul) ';'},        NULL, 16, 0},
/* 16*/
       {BgGr, {(ul) gBlock},     NULL, 17, 0},
/* 17*/
       {BgSy, {(ul) ';'},        NULL, 12, 0},
/* 18*/
       {BgGr, {(ul) gStatement}, NULL, 19, 0},
/* 19*/
       {BgEn, {(ul) 0},          NULL, 0,  0}
};

tBog gProgramm[] = {
/* 0*/ {BgGr, {(ul) gBlock}, NULL, 1, 0},
/* 1*/
       {BgSy, {(ul) '.'},    NULL, 2, 0},
/* 2*/
       {BgEn, {(ul) 0},      NULL, 0, 0}
};

int parse(tBog *pGraph);

int recDepth = 0;

void pLS() {
    for (int i = 0; i < recDepth * 2; ++i) {
        printf("=");
    }
}

void showCurrMorph() {
    pLS();
    switch (Morph.MC) {
        case mcSymb :
            if (Morph.Val.Symb == zERG) printf("Symbol :=\n");
            else if (Morph.Val.Symb == zLE) printf("Symbol <=\n");
            else if (Morph.Val.Symb == zGE) printf("Symbol >=\n");
            else if (Morph.Val.Symb == zBGN) printf("Symbol _BEGIN\n");
            else if (Morph.Val.Symb == zCLL) printf("Symbol _CALL\n");
            else if (Morph.Val.Symb == zCST) printf("Symbol _CONST\n");
            else if (Morph.Val.Symb == zDO) printf("Symbol _DO\n");
            else if (Morph.Val.Symb == zEND) printf("Symbol _END\n");
            else if (Morph.Val.Symb == zIF) printf("Symbol _IF\n");
            else if (Morph.Val.Symb == zODD) printf("Symbol _ODD\n");
            else if (Morph.Val.Symb == zPRC) printf("Symbol _PROCEDURE\n");
            else if (Morph.Val.Symb == zTHN) printf("Symbol _THEN\n");
            else if (Morph.Val.Symb == zVAR) printf("Symbol _VAR\n");
            else if (Morph.Val.Symb == zWHL) printf("Symbol _WHILE\n");
            if (isprint(Morph.Val.Symb))printf("Symbol %c\n", (char) Morph.Val.Symb);
            break;
        case mcNum :
            printf("Zahl %ld\n", Morph.Val.Num);
            break;
        case mcIdent:
            printf("Ident %s\n", (char *) Morph.Val.pStr);
            break;
        case mcEmpty:
            printf("mcEmpty\n");
            break;
    }
}

tMorph Morph = {0};

int parse(tBog *pGraph) {
    initNameList();
    if (pGraph == NULL) {
        printf("init graphs\n");
        pGraph = gProgramm;
    }
    tBog *pBog = pGraph;
    int succ = 0;
    if (Morph.MC == mcEmpty) {
        printf("call lex\n");
        Morph = Lex();
        showCurrMorph();
    }
    while (1) {
        pLS();
        printf("do switch\n");
        switch (pBog->BgD) {
            case BgNl: {
                pLS();
                printf("was BgNl\n");
                succ = 1;
                break;
            }
            case BgSy: {
                pLS();
                printf("was BgSy\n");
                showCurrMorph();
                succ = (Morph.Val.Symb == pBog->BgX.S);
                break;
            }
            case BgMo: {
                pLS();
                printf("was BgMo\n");
                succ = (Morph.MC == (tMC) pBog->BgX.M);
                showCurrMorph();
                break;
            }
            case BgGr: {
                pLS();
                printf("was BgGr, call new bogen where next is next is %d, alt is %d\n", pBog->iNext, pBog->iAlt);
                recDepth++;
                succ = parse(pBog->BgX.G);
                recDepth--;
                break;
            }
            case BgEn: {
                pLS();
                printf("was BgEn erreicht next is %d, alt is %d\n", pBog->iNext, pBog->iAlt);
                return 1;
            } /* Ende erreichet - Erfolg */
        }
        pLS();
        printf("parse after switch\n");
        if (succ && pBog->fx != NULL) {
            pLS();
            printf("call function\n");
            succ = pBog->fx();
            printf("function finished\n");
        }
        pLS();
        printf("parse after func call\n");
        if (!succ) {/* Alternativbogen probieren */
            if (pBog->iAlt != 0) {
                pLS();
                printf("alternativbogen probieren next is %d, alt is %d\n", pBog->iNext, pBog->iAlt);
                pBog = pGraph + pBog->iAlt;
            } else {
                pLS();
                printf("bogen nicht geklappt\n");
                return -1;
            }
        } else /* Morphem formal akzeptiert (eaten) */
        {
            if (pBog->BgD == BgSy || pBog->BgD == BgMo) {
                pLS();
                printf("call lexer\n");
                Morph = Lex();
            }
            printf("---------\n");
            pLS();
            printf("eaten next is %d, alt is %d\n", pBog->iNext, pBog->iAlt);
            pBog = pGraph + pBog->iNext;
        }
    }/* while */
}