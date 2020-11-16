/*
 *
 * Name: Anton Burenko
 * s-Nummer: s76905
 * Studiengruppe: 17/041/01
 * Dozent: Prof. Dr.-Ing. Arnold Beck
 *
 * */
#include "parser.h"
#include <stdlib.h>

static tMorph Morph;

void initGraphs();

int pars(tBog* pGraph)
{
    initGraphs();
    tBog* pBog=pGraph;
    int succ=0;
    if (Morph.MC==mcEmpty) Morph = Lex();
    while(1)
    {
        switch(pBog->BgD)
        {
            case BgNl:succ=1; break;
            case BgSy:succ=(Morph.Val.Symb==pBog->BgX.S);break;
            case BgMo:succ=(Morph.MC==(tMC)pBog->BgX.M); break;
            case BgGr:succ=pars(pBog->BgX.G); break;
            case BgEn:return 1; /* Ende erreichet - Erfolg */
        }
        if (succ && pBog->fx != NULL) succ=pBog->fx();
        if (!succ)/* Alternativbogen probieren */
            if (pBog->iAlt != 0)
                pBog=pGraph+pBog->iAlt;
            else return -1;
        else /* Morphem formal akzeptiert (eaten) */
        {
            if (pBog->BgD & BgSy || pBog->BgD & BgMo) Lex();
            pBog=pGraph+pBog->iNext;
        }
    }/* while */
}

void initGraphs() {
    tBog gTerm[]={
/* 0*/ {BgGr, {(ul)gFact},     NULL, 1, 3},
/* 1*/ {BgSy, {(ul)'*'}, NULL, 0, 2},
/* 2*/ {BgSy, {(ul)'/'}, NULL, 0, 0},
/* 3*/ {BgEn, {(ul)gTerm},      NULL, 0, 0}
    };

    tBog gExpr[]={
/* 0*/ {BgSy, {(ul)'+'},  NULL, 3, 1},
/* 1*/ {BgSy, {(ul)'-'},  NULL, 3, 2},
/* 2*/ {BgGr, {(ul)gTerm},      NULL, 4, 0},
/* 3*/ {BgGr, {(ul)gTerm},      NULL, 4, 0},
/* 4*/ {BgNl, {(ul)NULL}, NULL, 5, 9},
/* 5*/ {BgSy, {(ul)'+'},  NULL, 7, 6},
/* 6*/ {BgSy, {(ul)'-'},  NULL, 8, 0},
/* 7*/ {BgGr, {(ul)gTerm},      NULL, 4, 0},
/* 8*/ {BgGr, {(ul)gTerm},      NULL, 4, 0},
/* 9*/ {BgEn, {(ul)mcIdent},    NULL, 0, 0}
    };

    tBog gFact[]={
/* 0*/ {BgMo, {(ul)mcIdent},     NULL, 5, 1},
/* 1*/ {BgMo, {(ul)mcNum },      NULL, 5, 2},
/* 2*/ {BgSy, {(ul)'(' },  NULL, 3, 0},
/* 3*/ {BgGr, {(ul)gExpr },      NULL, 4, 0},
/* 4*/ {BgSy, {(ul)')' },  NULL, 5, 0},
/* 5*/ {BgEn, {(ul)0 },    NULL, 0, 0}
    };

    tBog gCondition[]={
/* 0*/ {BgSy,  {(ul)'ODD'}, NULL, 2, 1},
/* 1*/ {BgGr,  {(ul)gExpr},       NULL, 3, 0},
/* 2*/ {BgGr,  {(ul)gExpr},       NULL, 10, 0},
/* 3*/ {BgSy,  {(ul)'='},   NULL, 9, 4},
/* 4*/ {BgSy,  {(ul)'#'},   NULL, 9, 5},
/* 5*/ {BgSy,  {(ul)'<'},   NULL, 9, 6},
/* 6*/ {BgSy,  {(ul)'<='},  NULL, 9, 7},
/* 7*/ {BgSy,  {(ul)'>'},  NULL, 9, 8},
/* 8*/ {BgSy,  {(ul)'>='},  NULL, 9, 0},
/* 9*/ {BgGr,  {(ul)gExpr},       NULL, 10, 0},
/* 10*/ {BgEn, {(ul)NULL}, NULL, 0, 0}
    };

    tBog gStatement[]={
/* 0*/ {BgMo,  {(ul)mcIdent},          NULL, 7, 1},
/* 1*/ {BgSy, {(ul)"IF"},        NULL, 8, 2},
/* 2*/ {BgSy, {(ul)"WHILE"},     NULL, 9, 3},
/* 3*/ {BgSy,  {(ul)"BEGIN"},    NULL, 16, 4},
/* 4*/ {BgSy,  {(ul)'CALL'},    NULL, 10, 5},
/* 5*/ {BgSy,  {(ul)'?'},       NULL, 11, 6},
/* 6*/ {BgSy,  {(ul)'!'},      NULL, 12, 0},

/* 7*/ {BgSy,  {(ul)":="}, NULL, 13, 0},
/* 8*/ {BgGr,  {(ul)gCondition}, NULL, 14, 0},
/* 9*/ {BgGr,  {(ul)gCondition}, NULL, 15, 0},
/* 10*/ {BgMo,  {(ul)mcIdent},   NULL, 21, 0},
/* 11*/ {BgMo,  {(ul)mcIdent},   NULL, 21, 0},
/* 12*/ {BgGr,  {(ul)gExpr},     NULL, 21, 0},

/* 13*/ {BgGr,  {(ul)gExpr},        NULL, 21, 0},
/* 14*/ {BgSy, {(ul)"THEN"},  NULL, 18, 0},
/* 15*/ {BgSy, {(ul)"DO"},    NULL, 19, 0},
/* 16*/ {BgGr, {(ul)gStatement},    NULL, 17, 20},
/* 17*/ {BgSy, {(ul)';'},    NULL, 16, 0},

/* 18*/ {BgGr, {(ul)gStatement},     NULL, 21, 0},
/* 19*/ {BgGr, {(ul)gStatement},    NULL, 21, 0},
/* 20*/ {BgSy, {(ul)"END"},  NULL, 21, 0},
/* 21*/ {BgEn, {(ul)NULL},   NULL, 0, 0}
    };

    const tBog gBlock[]={
/* 0*/ {BgSy,  {(ul)'CONST'}, NULL, 2, 1},
/* 1*/ {BgNl,  {(ul)NULL},   NULL, 7, 8},

/* 2*/ {BgMo,  {(ul)mcIdent},    NULL, 3, 0},
/* 3*/ {BgSy,  {(ul)'='}, NULL, 4, 0},
/* 4*/ {BgMo,  {(ul)mcNum},     NULL, 0, 0},
/* 5*/ {BgSy,  {(ul)','}, NULL, 2, 0},
/* 6*/ {BgSy,  {(ul)';'}, NULL, 7, 0},

/* 7*/ {BgSy,  {(ul)'VAR'}, NULL, 9, 0},
/* 8*/ {BgNl,  {(ul)NULL}, NULL, 12, 13},
/* 9*/ {BgMo,  {(ul)mcIdent},    NULL, 10, 11},
/* 10*/ {BgSy, {(ul)','}, NULL, 9, 0},
/* 11*/ {BgSy, {(ul)';'}, NULL, 12, 0},

/* 12*/ {BgSy, {(ul)'PROCEDURE'},NULL, 14, 0},
/* 13*/ {BgNl, {(ul)NULL},        NULL, 18, 0},
/* 14*/ {BgMo, {(ul)mcIdent},          NULL, 15, 0},
/* 15*/ {BgSy, {(ul)';'},        NULL, 16, 0},
/* 16*/ {BgGr, {(ul)gBlock},            NULL, 17, 0},
/* 17*/ {BgSy, {(ul)';'},        NULL, 13, 0},

/* 18*/ {BgGr, {(ul)gStatement}, NULL, 19, 0},
/* 19*/ {BgNl, {(ul)NULL}, NULL, 0, 0}
    };

    tBog gProgramm[]={
/* 0*/ {BgGr, {(ul)gBlock},       NULL, 1, 0},
/* 1*/ {BgSy, {(ul)'.' },  NULL, 2, 0},
/* 2*/ {BgEn, {(ul)0 },    NULL, 0, 0}
    };
}
