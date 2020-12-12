/*
 *
 * Name: Anton Burenko
 * s-Nummer: s76905
 * Studiengruppe: 17/041/01
 * Dozent: Prof. Dr.-Ing. Arnold Beck
 *
 * */
#include <stdio.h>

typedef enum CODE_ENUM {
    puValVrLocl = 0x00,
    puValVrMain = 0x01,
    puValVrGlob = 0x02,
    puAdrVrLocl = 0x03,
    puAdrVrMain = 0x04,
    puAdrVrGlob = 0x05,
    puConst = 0x06,
    call = 0x16,
    jmp = 0x18,
    jnot = 0x19,
    entryProc = 0x1A
} tCode;

// Schreibt am aktuellen Programmcounter
void wr2ToCode(short x);

// Schreibt an der  Übergebenen Stelle
void wr2ToCodeAtP(short x, char *pD);

int code(tCode Code, ...);

char *pCode = NULL;
