/*
 *
 * Name: Anton Burenko
 * s-Nummer: s76905
 * Studiengruppe: 17/041/01
 * Dozent: Prof. Dr.-Ing. Arnold Beck
 *
 * */
#ifndef PARSER_HEADER
#define PARSER_HEADER

#include "namelist.h"

typedef unsigned long ul;

typedef enum BOGEN_DESC {
    BgNl = 0, // NIL
    BgSy = 1, // Symbol
    BgMo = 2, // Morphem
    BgGr = 4, // Graph
    BgEn = 8,// Graphende (altenativ 0 oder -1 als Folgebogen)
} tBg;

typedef struct BOGEN {
    tBg BgD; // Bogentyp (Nil, Symbol, Name/Zahl, Graph)
    union BGX // Bogenbeschreibung
    {
        unsigned long X; // für Initialisierung notwendig
        int S; // Symbol (Ascii oder Wortsymbolcode aus enum)
        tMC M; // Morphemtyp (Zahl oder Bezeichner)
        struct BOGEN *G; // Verweis auf Graph
    } BgX;

    int (*fx)(void); // Funktionspointer (Funktion, wenn Bogen akzeptiert)
    int iNext; // Folgebogen, wenn Bogen akzeptiert
    int iAlt; // Alternativbogen, wenn Bogen nicht akzeptiert
// oder 0 oder -1, wenn es keinen
// Alternativbogen gibt.
} tBog;

extern tBog gTerm[];
extern tBog gExpr[];
extern tBog gCondition[];
extern tBog gStatement[];
extern tBog gBlock[];
extern tBog gProgramm[];
extern tBog gFact[];

int parse(tBog *pGraph);

#endif