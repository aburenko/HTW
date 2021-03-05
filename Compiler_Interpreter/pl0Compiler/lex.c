/*
 *
 * Name: Anton Burenko
 * s-Nummer: s76905
 * Studiengruppe: 17/041/01
 * Dozent: Prof. Dr.-Ing. Arnold Beck
 *
 * */

/****************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "lex.h"

static int arrayIndexType = 0; /* 0-init 1-number 2-variable */
static FILE *pIF;            /* Quellfile 				*/
static tMorph Morph;
static tMorph MorphInit;        /* Morphem   				*/
static signed char X;            /* Aktuelles Eingabezeichen 		*/
static int Z = 0;            /* Aktueller Zustand des Automaten 	*/
static char vBuf[128 + 1], *pBuf;    /* Ausgabepuffer */
static char vBufArrayIndex[128 + 1], *pBufArrayIndex;    /* Extra Ausgabepuffer für Array Index*/
static int Ende;            /* Flag 				*/
static int line, col;            /* Flag 				*/
int startLine, startCol = 0;

/* Zeichenklassenvektor
 * 0 Sonderzeichen
 * 1 Ziffern
 * 2 Buchstaben
 * 3 :
 * 4 =
 * 5 <
 * 6 >
 * 7 Sonstige Steuerzeichen
 * 8 Nicht Schlüsselwortbuchstaben J|K|M|Q|X|Y|Z
 * 9  "("
 * 10 ")"
 * 11 "*"
 * 12 "["
 * 13 "]"
 * */
static char vZKl[128] =
/*      0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F     */
/*---------------------------------------------------------*/
/* 0 */{7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,/* 0*/
/*10*/  7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,/*10*/
/*20*/  7, 0, 0, 0, 0, 0, 0, 0, 9, 10, 11, 0, 0, 0, 0, 0,/*20*/
/*30*/  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 0, 5, 4, 6, 0,/*30*/
/*40*/  0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 8, 8, 2, 8, 2, 2,/*40*/
/*50*/  2, 8, 2, 2, 2, 2, 2, 2, 8, 8, 8, 12, 0, 13, 0, 0,/*50*/
/*60*/  0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 8, 8, 2, 8, 2, 2,/*60*/
/*70*/  2, 8, 2, 2, 2, 2, 2, 2, 8, 8, 8, 0, 0, 0, 0, 0}/*70*/;


// funtionübersicht
static void fl(void); // lesen
static void fb(void); // beenden
static void fgl(void); // schreiben als Großbuchstaben, lesen
static void fsl(void); // schreiben, lesen
static void fslA(void); // schreiben für Array index, lesen
static void fslAZ(void); // schreiben für Array index, lesen zahlen
static void fslAI(void); // schreiben für Array index, lesen indents
static void fslb(void); // schreiben, lesen, beenden



/* Automatentabelle
 * Jeder Eintrag der Automatentabelle besteht aus einem Byte.
 * Das niederwertige Halbbyte (4bit) enthält den Folgezustand.
 * Das höherwertige Halbbyte (4bit) enthält einen Funktionsindex, multipliziert mit 16, oder um 4 bit nach links verschoben.
 */
static NS vSMatrix[][14] =
        /* 0 Sonderzeichen bzw start*/
        {{{0, fslb}, {2, fsl}, {9,  fsl}, {3, fsl}, {0, fslb}, {4, fsl}, {5, fsl}, {0, fl}, {1, fsl}, {18, fl}, {0, fslb}, {0, fslb}, {0, fslb}, {0, fslb}},
                /* 1 Identifier */
         {{0, fb},   {1, fsl}, {1,  fsl}, {0, fb},  {0, fb},   {0, fb},  {0, fb},  {0, fb}, {1, fsl},  {0, fb}, {0, fb}, {0, fb}, {0, fb}, {0, fb}},
                /* 2 Zahl */
         {{0, fb},   {2, fsl}, {2,  fgl}, {0, fl},  {0, fl},   {0, fb},  {0, fb},  {0, fb}, {0, fl},  {0, fb}, {0, fb}, {0, fb}, {0, fb},{0, fb}},
                /* 3 : */
         {{0, fb},   {0, fb},  {0,  fb},  {0, fb},  {6, fsl},  {0, fl},  {0, fl},  {0, fl}, {0, fl}, {0, fl},  {0, fl}, {0, fb}, {0, fb}, {0, fb}},
                /* 4 < */
         {{0, fb},   {0, fb},  {0,  fb},  {0, fb},  {7, fsl},  {0, fb},  {0, fb},  {0, fb}, {0, fl}, {0, fb}, {0, fb}, {0, fb}, {0, fb}, {0, fb}},
                /* 5 > */
         {{0, fb},   {0, fb},  {0,  fb},  {0, fb},  {8, fsl},  {0, fl},  {0, fb},  {0, fb}, {0, fb}, {0, fb}, {0, fb}, {0, fb}, {0, fb}, {0, fb}},
                /* 6 Ergibtzeichen */
         {{0, fb},   {0, fb},  {0,  fb},  {0, fb},  {0, fb},   {0, fb},  {0, fb},  {0, fb}, {0, fb}, {0, fb}, {0, fb}, {0, fb}, {0, fb}, {0, fb}},
                /* 7 KleinerGleich */
         {{0, fb},   {0, fb},  {0,  fb},  {0, fb},  {0, fb},   {0, fb},  {0, fb},  {0, fb}, {0, fb}, {0, fb}, {0, fb}, {0, fb}, {0, fb}, {0, fb}},
                /* 8 GroesserGleich */
         {{0, fb},   {0, fb},  {0,  fb},  {0, fb},  {0, fb},   {0, fb},  {0, fb},  {0, fb}, {0, fb}, {0, fb}, {0, fb}, {0, fb}, {0, fb}, {0, fb}},
                /* 9 keywords*/
         {{0, fb},   {1, fsl}, {10, fsl}, {0, fb},  {0, fb},   {0, fb},  {0, fb},  {0, fb}, {1, fsl}, {0, fb}, {0, fb}, {0, fb}, {0, fb}, {0, fb}},
                /* 10 keywords*/
         {{0, fb},   {1, fsl}, {11, fsl}, {0, fb},  {0, fb},   {0, fb},  {0, fb},  {0, fb}, {1, fsl}, {0, fb}, {0, fb}, {0, fb}, {0, fb}, {0, fb}},
                /* 11 keywords*/
         {{0, fb},   {1, fsl}, {12, fsl}, {0, fb},  {0, fb},   {0, fb},  {0, fb},  {0, fb}, {1, fsl}, {0, fb}, {0, fb}, {0, fb}, {0, fb}, {0, fb}},
                /* 12 keywords*/
         {{0, fb},   {1, fsl}, {13, fsl}, {0, fb},  {0, fb},   {0, fb},  {0, fb},  {0, fb}, {1, fsl}, {0, fb}, {0, fb}, {0, fb}, {0, fb}, {0, fb}},
                /* 13 keywords*/
         {{0, fb},   {1, fsl}, {14, fsl}, {0, fb},  {0, fb},   {0, fb},  {0, fb},  {0, fb}, {1, fsl}, {0, fb}, {0, fb}, {0, fb}, {0, fb}, {0, fb}},
                /* 14 keywords*/
         {{0, fb},   {1, fsl}, {15, fsl}, {0, fb},  {0, fb},   {0, fb},  {0, fb},  {0, fb}, {1, fsl}, {0, fb}, {0, fb}, {0, fb}, {0, fb}, {0, fb}},
                /* 15 keywords*/
         {{0, fb},   {1, fsl}, {16, fsl}, {0, fb},  {0, fb},   {0, fb},  {0, fb},  {0, fb}, {1, fsl}, {0, fb}, {0, fb}, {0, fb}, {0, fb}, {0, fb}},
                /* 16 keywords*/
         {{0, fb},   {1, fsl}, {17, fsl}, {0, fb},  {0, fb},   {0, fb},  {0, fb},  {0, fb}, {1, fsl}, {0, fb}, {0, fb}, {0, fb}, {0, fb}, {0, fb}},
                /* 17 keywords*/
         {{0, fb},   {1, fsl}, {1,  fsl}, {0, fb},  {0, fb},   {0, fb},  {0, fb},  {0, fb}, {1, fsl}, {0, fb}, {0, fb}, {0, fb}, {0, fb}, {0, fb}},
                /* 18 Comment Zustand Stern */
         {{0, fb},   {0, fb},  {0,  fb},  {0, fb}, {0, fb},   {0, fb},  {0, fb},  {0, fb}, {0, fb}, {0, fb}, {0, fb}, {19, fl}, {0, fb}, {0, fb}},
                /* 19 Comment Zustand zweites Stern: liest alle Ziechen zwischen Sternen*/
         {{19, fl},   {19, fl},  {19, fl},  {19, fl},  {19, fl},   {19, fl},  {19, fl},  {19, fl}, {19, fl}, {19, fl}, {19, fl}, {20, fl}, {19, fl}, {19, fl}},
                /* 20 Comment Endzustand )  */
         {{0, fb},   {0, fb},  {0,  fb},  {0, fb},  {0, fb},   {0, fb},  {0, fb},  {0, fb}, {0, fb}, {0, fb}, {0, fl}, {0, fb}, {0, fb}, {0, fb}}};


/*---- Initialisierung der lexiaklischen Analyse ----*/
void initLex(char *fname) {
    pIF = fopen(fname, "r+");
    if (pIF == NULL) {
        printf("error reading file\n");
        exit(-1);
    }
    if (pIF) {
        X = fgetc(pIF);
    }
    printf("initLex mit %c \n", X);
    Morph.MC = mcEmpty;
}

typedef struct KeywordPair {
    char *name;
    tZS tZSident;
} kwp;

static kwp keyword[] = {{"BEGIN",     zBGN},
                        {"CALL",      zCLL},
                        {"CONST",     zCST},
                        {"DO",        zDO},
                        {"END",       zEND},
                        {"IF",        zIF},
                        {"ODD",       zODD},
                        {"PROCEDURE", zPRC},
                        {"THEN",      zTHN},
                        {"VAR",       zVAR},
                        {"WHILE",     zWHL}};

void to_upper(char *string) {
    while (*string) {
        *string = toupper((unsigned char) *string);
        string++;
    }
}

int binary_search(int size, char *target){
    int bottom= 0;
    int mid;
    int top = size - 1;

    while(bottom <= top){
        mid = (bottom + top)/2;
        if (strcmp(keyword[mid].name, target) == 0){
            return mid;
        } else if (strcmp(keyword[mid].name, target) > 0){
            top    = mid - 1;
        } else if (strcmp(keyword[mid].name, target) < 0){
            bottom = mid + 1;
        }
    }

    return -1;
}

static void fb(void) {
    printf("fb ");
    switch (Z) {
        /* Symbol */
        case 3: // :
        case 4: // <
        case 5: // >
        case 0: // Sonderzeichen
            Morph.Val.Symb = vBuf[0];
            Morph.MC = mcSymb;
            break;
        case 1: /* Identifier */
            Morph.Val.pStr = vBuf;
            Morph.MC = mcIdent;
            break;
        case 2: /* Zahl */
            Morph.Val.Num = atol(vBuf);
            Morph.MC = mcNum;
            break;
        case 6: /* Ergibtzeichen */
            Morph.Val.Symb = (long) zERG;
            Morph.MC = mcSymb;
            break;
        case 7: /* KleinerGleich */
            Morph.Val.Symb = (long) zLE;
            Morph.MC = mcSymb;
            break;
        case 8: /* GroesserGleich */
            Morph.Val.Symb = (long) zGE;
            Morph.MC = mcSymb;
            break;
        case 18: // (
            Morph.Val.Symb = '(';
            Morph.MC = mcSymb;
            break;
        case 9:
        case 10:
        case 11:
        case 12:
        case 13:
        case 14:
        case 15:
        case 16:
        case 17: /*keywords*/
            to_upper(vBuf);
//            printf("lex: buf was %s\n", vBuf);
            int index = binary_search(sizeof(keyword) / sizeof(kwp), vBuf);
            if (index != -1) {
                Morph.MC = mcSymb;
                Morph.Val.Symb = keyword[index].tZSident;
            } else {
                Morph.MC = mcIdent;
                Morph.Val.pStr = vBuf;
            }
            break;
    }
    Ende = 1;
}

static void fl(void) {
    printf("fl ");
    X = fgetc(pIF);
    if (X == '\n') line++, col = 0;
    else col++;
}

static void fgl(void) {
    printf("fgl-");
    *pBuf = (char) toupper(X);
    *(++pBuf) = 0;
    fl();
}

static void fsl(void) {
    printf("fsl-");
    *pBuf = (char) X;
    *(++pBuf) = 0;
    fl();
}

// for numbers
static void fslAZ(void) {
    if (arrayIndexType != 2) { arrayIndexType = 1;}
    else {printf("unknown error in fslAZ occured");exit(-15);}
    printf("fslAZ-");
    fslA();
}

// for identifiers
static void fslAI(void) {
    if (arrayIndexType != 1) { arrayIndexType = 2;}
    else {printf("unknown error in fslAZ occured");exit(-15);}
    printf("fslAI-");
    fslA();
}
static void fslA(void) {
    *pBufArrayIndex = (char) X;
    *(++pBufArrayIndex) = 0;
    fl();
}

static void fslb(void) {
    printf("fslb-");
    fsl();
    fb();
}

/*---- Lexikalische Analyse ----*/
tMorph Lex(void) {
    // init
    arrayIndexType  = 0;
    Morph = MorphInit;
    pBuf = vBuf;
    pBufArrayIndex = vBufArrayIndex;
    Ende = 0;
    startLine = line;
    startCol = col;
    do {
        int KlassVonX = vZKl[X & 0x7f];
        printf("[%c] Z:%d K:%d ->", X, Z, KlassVonX);
        /* Berechnung des Folgezustands */
        NS ns = vSMatrix[Z][KlassVonX];
        /* Ausfuehrung der Aktion */
        ns.func();
        /* Automat schaltet */
        Z = ns.state;
    } while (Ende == 0);
    printf("END Z:%d  \n", Z);
    Morph.PosLine = startLine;
    Morph.PosCol = startCol;
    return Morph;
}
