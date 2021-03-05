/*
 *
 * Name: Anton Burenko
 * s-Nummer: s76905
 * Studiengruppe: 17/041/01
 * Dozent: Prof. Dr.-Ing. Arnold Beck
 *
 * */
/* Morphemcodes */

#ifndef LEX_HEADER
#define LEX_HEADER

typedef enum T_MC {
    mcEmpty, mcSymb, mcNum, mcIdent
} tMC;

typedef enum T_ZS {
    zNIL,
    zERG = 128, zLE, zGE,
    zBGN, zCLL, zCST, zDO, zEND, zIF, zODD, zPRC, zTHN, zVAR, zWHL, zArrayNumber, zArrayVariable
} tZS;

typedef struct {
    tMC MC;        /* Morphemcode */
    int PosLine;   /* Zeile       */
    int PosCol;    /* Spalte      */
    union VAL {
        long Num;
        char *pStr;
        int Symb;
    } Val;
    int MLen;   /* Morphemlaenge*/
    int arrayIndexType; /* 0-init 1-number 2-variable */
    union ARRAY_INDEX { // used only for arrays
        long index;
        char *ident;
    } arrayIndex;
} tMorph;

typedef void (*FX)(void);

typedef struct NextState {
    int state;
    FX func;
} NS;

void initLex();

tMorph Lex(void);

#endif