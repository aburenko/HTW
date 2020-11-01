// Arnold Beck

/****************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "lex.h"

static FILE *pIF;            /* Quellfile 				*/
static tMorph Morph, MorphInit;        /* Morphem   				*/
static signed char X;            /* Aktuelles Eingabezeichen 		*/
static int Z = 0;            /* Aktueller Zustand des Automaten 	*/
static char vBuf[128 + 1], *pBuf;    /* Ausgabepuffer */
static int Ende;            /* Flag 				*/
static int line, col;            /* Flag 				*/

/*---- Initialisierung der lexiaklischen Analyse ----*/
void initLex(char *fname) {
    pIF = fopen(fname, "r+");
    if (pIF == NULL) {
        printf("error reading file\n");
        exit(-1);
    }
    if (pIF) X = fgetc(pIF);
    Morph.MC = mcEmpty;
}

/* Zeichenklassenvektor
 * 0 Sonderzeichen
 * 1 Ziffern
 * 2 Buchstaben
 * 3 :
 * 4 =
 * 5<
 * 6>
 * 7 Sonstige Steuerzeichen
 * */
static char vZKl[128] =
/*      0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F     */
/*---------------------------------------------------------*/
/* 0 */{7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,/* 0*/
/*10*/  7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,/*10*/
/*20*/  7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,/*20*/
/*30*/  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 0, 5, 4, 6, 0,/*30*/
/*40*/  0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,/*40*/
/*50*/  2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0,/*50*/
/*60*/  0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,/*60*/
/*70*/  2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0}/*70*/;


// funtionübersicht
static void fl(void); // lesen
static void fb(void); // beenden
static void fgl(void); // schreiben als Großbuchstaben, lesen
static void fsl(void); // schreiben, lesen
static void fslb(void); // schreiben, lesen, beenden



/* Automatentabelle
 * Jeder Eintrag der Automatentabelle besteht aus einem Byte.
 * Das niederwertige Halbbyte (4bit) enthält den Folgezustand.
 * Das höherwertige Halbbyte (4bit) enthält einen Funktionsindex, multipliziert mit 16, oder um 4 bit nach links verschoben.
 */
static NS vSMatrix[][8] =
        /* 0*/
        {{{0, fslb}, {2, fsl}, {1, fsl}, {3, fsl}, {0, fslb}, {4, fsl}, {5, fsl}, {0, fl}},
                /* 1 */
         {{0, fb},   {1, fsl}, {1, fsl}, {0, fb},  {0, fb},   {0, fb},  {0, fb},  {0, fb}},
                /* 2 */
         {{0, fb},   {2, fsl}, {2, fgl}, {0, fl},  {0, fl},   {0, fb},  {0, fb},  {0, fb}},
                /* 3 */
         {{0, fb},   {0, fb},  {0, fb},  {0, fb},  {6, fsl},  {0, fl},  {0, fl},  {0, fl}},
                /* 4 */
         {{0, fb},   {0, fb},  {0, fb},  {0, fb},  {7, fsl},  {0, fl},  {0, fl},  {0, fl}},
                /* 5 */
         {{0, fb},   {0, fb},  {0, fb},  {0, fb},  {8, fsl},  {0, fl},  {0, fl},  {0, fl}},
                /* 6 */
         {{0, fb},   {0, fb},  {0, fb},  {0, fb},  {0, fb},   {0, fl},  {0, fl},  {0, fl}},
                /* 7 */
         {{0, fb},   {0, fb},  {0, fb},  {0, fb},  {0, fb},   {0, fl},  {0, fl},  {0, fl}},
                /* 8 */
         {{0, fb},   {0, fb},  {0, fb},  {0, fb},  {0, fb},   {0, fl},  {0, fl},  {0, fl}}};


/* Ausgabefunktionen des Automaten */
static void fl(void) {
    X = fgetc(pIF);
    if (X == '\n') line++, col = 0;
    else col++;
}

static void fb(void) {
    Morph.PosCol = col;
    Morph.PosLine = line;
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
    }
    Ende = 1; // entfällt bei Variante mit Zustand zEnd
}


static void fgl(void) {
    *pBuf = (char) toupper(X);// oder *Buf=(char)X&0xdf;
    *(++pBuf) = 0;
    fl();
}

static void fsl(void) {
    *pBuf = (char) X;
    *(++pBuf) = 0;
    fl();
}

static void fslb(void) {
    fsl();
    fb();
}

/*---- Lexikalische Analyse ----*/
tMorph Lex(void) {
    int Zn;
    Morph = MorphInit;
    pBuf = vBuf;
    Ende = 0;
    do {
        int KlassVonX = vZKl[X & 0x7f];
        /* Berechnung des Folgezustands */
        NS ns = vSMatrix[Z][KlassVonX];
        /* Ausfuehrung der Aktion */
        ns.func();
        //printf("Z:%d K:%d F:%d-> ", Z, KlassVonX, ns.func);
        /* Automat schaltet */
        Z = ns.state;
    } while (Ende == 0);
    return Morph;
}
