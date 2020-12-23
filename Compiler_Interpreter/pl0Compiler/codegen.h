/*
 *
 * Name: Anton Burenko
 * s-Nummer: s76905
 * Studiengruppe: 17/041/01
 * Dozent: Prof. Dr.-Ing. Arnold Beck
 *
 * */
#ifndef CODEGEN_HEADER
#define CODEGEN_HEADER

typedef enum CODE_ENUM {
    puValVrLocl = 0x00,
    puValVrMain = 0x01,
    puValVrGlob = 0x02,
    puAdrVrLocl = 0x03,
    puAdrVrMain = 0x04,
    puAdrVrGlob = 0x05,
    puConst = 0x06,
    storeVal = 0x07,
    putVal = 0x08,
    call = 0x16,
    retProc = 0x17,
    jmp = 0x18,
    jnot = 0x19,
    entryProc = 0x1A
} tCode;

// Schreibt am aktuellen Programmcounter
void wr2ToCode(short x);

// Schreibt an der  Übergebenen Stelle
void wr2ToCodeAtP(short x, char *pD);

void wr2ToCodeAtBegin(short x);

void wr2ToCodeConst(long x);

void codeEndProcedure();

int code(tCode Code, ...);

void writeToFile(void);

static char *pCode = NULL;
static char *pCodeBegin = NULL;
static char *pCurrProcedureBegin = NULL;

static int LenCode = 128;

#define MAX_LEN_OF_CODE 81

#endif