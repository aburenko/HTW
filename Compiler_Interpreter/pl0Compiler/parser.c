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
/* 0*/ {BgGr, {(ul) gFact}, NULL, 1, 0, "term0"},
/* 1*/
       {BgNl, {(ul) NULL},   NULL, 2, 0, "term1"},
/* 2*/
       {BgSy, {(ul) '*'},   NULL, 4, 3, "term2"},
/* 3*/
       {BgSy, {(ul) '/'},   NULL, 5, 6, "term3"},
/* 4*/
       {BgGr, {(ul) gFact},   te1, 1, 0, "term4"},
/* 5*/
       {BgGr, {(ul) gFact},   te2, 1, 0, "term5"},
/* 6*/
       {BgEn, {(ul) 0},     NULL, 0, 0, "term6"}
};

tBog gExpr[] = {
/* 0*/ {BgSy, {(ul) '+'},   NULL, 3, 1, "expression 0"},
/* 1*/
       {BgSy, {(ul) '-'},   NULL, 3, 2, "expression 1"},
/* 2*/
       {BgGr, {(ul) gTerm}, NULL, 4, 0, "expression 2"},
/* 3*/
       {BgGr, {(ul) gTerm}, ex1, 4, 0, "expression 3"},
/* 4*/
       {BgNl, {(ul) NULL},  NULL, 5, 9, "expression 4"},
/* 5*/
       {BgSy, {(ul) '+'},   NULL, 7, 6, "expression 5"},
/* 6*/
       {BgSy, {(ul) '-'},   NULL, 8, 0, "expression 6"},
/* 7*/
       {BgGr, {(ul) gTerm}, ex2, 4, 0, "expression 7"},
/* 8*/
       {BgGr, {(ul) gTerm}, ex3, 4, 0, "expression 8"},
/* 9*/
       {BgEn, {(ul) 0},     NULL, 0, 0, "expression 9"}
};

tBog gFact[] = {
/* 0*/ {BgMo, {(ul) mcIdent}, fa2, 5, 1, "fact 0"},
/* 1*/
       {BgMo, {(ul) mcNum},   fa1, 5, 2, "fact 1"},
/* 2*/
       {BgSy, {(ul) '('},     NULL, 3, 0, "fact 2"},
/* 3*/
       {BgGr, {(ul) gExpr},   NULL, 4, 0, "fact 3"},
/* 4*/
       {BgSy, {(ul) ')'},     NULL, 5, 0, "fact 4"},
/* 5*/
       {BgEn, {(ul) 0},       NULL, 0, 0, "fact 5"}
};

tBog gCondition[] = {
/* 0*/ {BgSy, {(ul) zODD},  NULL, 2,  1, "condition 00"},
/* 1*/
       {BgGr, {(ul) gExpr}, NULL, 3,  0, "condition 01"},
/* 2*/
       {BgGr, {(ul) gExpr}, co1, 10, 0, "condition 02"},
/* 3*/
       {BgSy, {(ul) '='},   co2_to_co7, 9,  4, "condition 03"},
/* 4*/
       {BgSy, {(ul) '#'},   co2_to_co7, 9,  5, "condition 04"},
/* 5*/
       {BgSy, {(ul) '<'},   co2_to_co7, 9,  6, "condition 05"},
/* 6*/
       {BgSy, {(ul) zLE},   co2_to_co7, 9,  7, "condition 06"},
/* 7*/
       {BgSy, {(ul) '>'},   co2_to_co7, 9,  8, "condition 07"},
/* 8*/
       {BgSy, {(ul) zGE},   co2_to_co7, 9,  0, "condition 08"},
/* 9*/
       {BgGr, {(ul) gExpr}, co8, 10, 0, "condition 09"},
/* 10*/
       {BgEn, {(ul) 0},     NULL, 0,  0, "condition 10"}
};

tBog gStatement[] = {
/* 0*/ {BgMo, {(ul) mcIdent},    st1, 7,  1, "statement 0"},
/* 1*/
       {BgSy, {(ul) zIF},        NULL, 8,  2, "statement 01"},
/* 2*/
       {BgSy, {(ul) zWHL},       st5, 9,  3, "statement 02"},
/* 3*/
       {BgSy, {(ul) zBGN},       NULL, 16, 4, "statement 03"},
/* 4*/
       {BgSy, {(ul) zCLL},       NULL, 10, 5, "statement 04"},
/* 5*/
       {BgSy, {(ul) '?'},        NULL, 11, 6, "statement 05"},
/* 6*/
       {BgSy, {(ul) '!'},        NULL, 12, 0, "statement 06"},
/* 7*/
       {BgSy, {(ul) zERG},       NULL, 13, 0, "statement 07"},
/* 8*/
       {BgGr, {(ul) gCondition}, st3, 14, 0, "statement 08"},
/* 9*/
       {BgGr, {(ul) gCondition}, st6, 15, 0, "statement 09"},
/* 10*/
       {BgMo, {(ul) mcIdent},    st8, 21, 0, "statement 10"},
/* 11*/
       {BgMo, {(ul) mcIdent},    st9, 21, 0, "statement 011"},
/* 12*/
       {BgGr, {(ul) gExpr},      st10, 21, 0, "statement 012"},
/* 13*/
       {BgGr, {(ul) gExpr},      st2, 21, 0, "statement 013"},
/* 14*/
       {BgSy, {(ul) zTHN},       NULL, 18, 0, "statement 014"},
/* 15*/
       {BgSy, {(ul) zDO},        NULL, 19, 0, "statement 015"},
/* 16*/
       {BgGr, {(ul) gStatement}, NULL, 17, 20, "statement 016"},
/* 17*/
       {BgSy, {(ul) ';'},        NULL, 16, 20, "statement 017"},
/* 18*/
       {BgGr, {(ul) gStatement}, st4, 21, 0, "statement 018"},
/* 19*/
       {BgGr, {(ul) gStatement}, st7, 21, 0, "statement 019"},
/* 20*/
       {BgSy, {(ul) zEND},       NULL, 21, 0, "statement 20"},
/* 21*/
       {BgEn, {(ul) 0},          NULL, 0,  0, "statement 21"}
};

tBog gBlock[] = {
/* 0*/ {BgSy, {(ul) zCST},       NULL, 2,  1, "block 0"},
/* 1*/
       {BgNl, {(ul) NULL},       NULL, 7,  0, "block 01"},
/* 2*/
       {BgMo, {(ul) mcIdent}, Bl1,     3,  0, "block 02"}, // Bl1
/* 3*/
       {BgSy, {(ul) '='},        NULL, 4,  0, "block 03"},
/* 4*/
       {BgMo, {(ul) mcNum},   Bl2,     5,  6, "block 04"}, // Bl2
/* 5*/
       {BgSy, {(ul) ','},        NULL, 2,  6, "block 05"},
/* 6*/
       {BgSy, {(ul) ';'},        NULL, 7,  0, "block 06"},
/* 7*/
       {BgSy, {(ul) zVAR},       NULL, 9,  8, "block 07"},
/* 8*/
       {BgNl, {(ul) NULL},       NULL, 12, 0, "block 08"},
/* 9*/
       {BgMo, {(ul) mcIdent}, Bl3,     10, 0, "block 09"}, // Bl3
/* 10*/
       {BgSy, {(ul) ','},        NULL, 9,  11, "block 10"},
/* 11*/
       {BgSy, {(ul) ';'},        NULL, 12, 0,  "block 011"},
/* 12*/
       {BgSy, {(ul) zPRC},    NULL,     14, 13,  "block 012"},
/* 13*/
       {BgNl, {(ul) NULL},    Bl6,     18, 0,  "block 013"},
/* 14*/
       {BgMo, {(ul) mcIdent},    Bl4, 15, 0,  "block 014"}, // Bl4
/* 15*/
       {BgSy, {(ul) ';'},        NULL, 16, 0,  "block 015"},
/* 16*/
       {BgGr, {(ul) gBlock},     NULL, 17, 0,  "block 016"},
/* 17*/
       {BgSy, {(ul) ';'},        Bl5, 12, 0,  "block 017"},
/* 18*/
       {BgGr, {(ul) gStatement}, NULL, 19, 0,  "block 018"},
/* 19*/
       {BgEn, {(ul) 0},          NULL, 0,  0,  "block 019"}
};

tBog gProgramm[] = {
/* 0*/ {BgGr, {(ul) gBlock}, NULL, 1, 0,  "program 0"},
/* 1*/
       {BgSy, {(ul) '.'},    pr1, 2, 0 , "program 1"}, // pr1
/* 2*/
       {BgEn, {(ul) 0},      NULL, 0, 0 , "program 2"}
};

int parse(tBog *pGraph);

void showCurrMorph() {
//    pLS();
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
    if (pGraph == NULL) {
        printf("init graphs and name list\n");
        pGraph = gProgramm;
        initNameList();
    }
    tBog *pBog = pGraph;
    int succ = 0;
    if (Morph.MC == mcEmpty) {
        Morph = Lex();
        showCurrMorph();
    }
    while (1) {
        switch (pBog->BgD) {
            case BgNl: {
                showCurrMorph();
                succ = 1;
                break;
            }
            case BgSy: {
                showCurrMorph();
                succ = (Morph.Val.Symb == pBog->BgX.S);
                break;
            }
            case BgMo: {
                showCurrMorph();
                succ = (Morph.MC == (tMC) pBog->BgX.M);
                break;
            }
            case BgGr: {
                printf("was BgGr, call new bogen %s where next is %d, alt is %d\n", pBog->name, pBog->iNext, pBog->iAlt);
                succ = parse(pBog->BgX.G);
                break;
            }
            case BgEn: {
                printf("was BgEn achieved next is %d, alt is %d\n", pBog->iNext, pBog->iAlt);
                return 1;
            } /* Ende erreichet - Erfolg */
        }
        if (succ && pBog->fx != NULL) {
            succ = pBog->fx();
        }
        if (!succ) {/* Alternativbogen probieren */
            if (pBog->iAlt != 0) {
                printf("alternativbogen %s probieren next is %d, alt is %d\n", pBog->name,pBog->iNext, pBog->iAlt);
                pBog = pGraph + pBog->iAlt;
            } else {
                printf("bogen %s nicht geklappt\n", pBog->name);
                return -1;
            }
        } else /* Morphem formal akzeptiert (eaten) */
        {
            if (pBog->BgD == BgSy || pBog->BgD == BgMo) {
                Morph = Lex();
            }
            printf("%s eaten next is %d, alt is %d\n",pBog->name, pBog->iNext, pBog->iAlt);
            printf("---------\n");
            pBog = pGraph + pBog->iNext;
        }
    }/* while */
}