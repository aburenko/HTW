// Arnold Beck
/* Morphemcodes */
typedef enum T_MC {
    mcEmpty, mcSymb, mcNum, mcIdent
} tMC;

typedef enum T_ZS {
    zNIL,
    zERG = 128, zLE, zGE,
    zBGN, zCLL, zCST, zDO, zEND, zIF, zODD, zPRC, zTHN, zVAR, zWHL
} tZS;

typedef struct {
    tMC MC;        /* Morphemcode */
    int PosLine;/* Zeile       */
    int PosCol;    /* Spalte      */
    union VAL {
        long Num;
        char *pStr;
        int Symb;
    } Val;
    int MLen;   /* Morpheml�nge*/
} tMorph;

typedef void (*FX)(void);

typedef struct NextState {
    int state;
    FX func;
} NS;

void initLex();

tMorph Lex(void);

