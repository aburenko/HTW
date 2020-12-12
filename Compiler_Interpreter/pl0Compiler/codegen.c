/*
 *
 * Name: Anton Burenko
 * s-Nummer: s76905
 * Studiengruppe: 17/041/01
 * Dozent: Prof. Dr.-Ing. Arnold Beck
 *
 * */
#include <stdlib.h>
#include <stdarg.h>
#include "codegen.h"

#define MAX_LEN_OF_CODE 1024

void wr2ToCode(short x) {
    *pCode++ = (unsigned char) (x & 0xff);
    *pCode++ = (unsigned char) (x >> 8);
}

void wr2ToCodeAtP(short x, char *pD) {
    *pD = (unsigned char) (x & 0xff);
    *(pD + 1) = (unsigned char) (x >> 8);
}
// TODO was ist vCode und LenCode?
int code(tCode Code, ...) {
    if (pCode == NULL) {
        pCode = malloc(MAX_LEN_OF_CODE);
    }
    va_list ap;
    short sarg;
    if (pCode - vCode + MAX_LEN_OF_CODE >= LenCode)
        // Ueberwachung des Zwischencodegenerierungspuffers
    {
        char *xCode = realloc(vCode, (LenCode += 1024));
        if (xCode == NULL) {
            printf("xCode was null, exit");
            exit(-5);
        };
        pCode = xCode + (pCode - vCode);
        vCode = xCode;
    }
    *pCode++ = (char) Code;
    va_start(ap, Code);

    switch (Code) {
/* Befehle mit 3 Parametern */
        case entryProc:
            sarg = va_arg(ap,
                          int);
            wr2ToCode(sarg);
/* Befehle mit 2 Parametern */
        case puValVrGlob:
        case puAdrVrGlob:
            sarg = va_arg(ap,
                          int);
            wr2ToCode(sarg);
/* Befehle mit 1 Parameter */
        case puValVrMain:
        case puAdrVrMain:
        case puValVrLocl:
        case puAdrVrLocl:
        case puConst:
        case jmp :
        case jnot:
        case call:
            sarg = va_arg(ap, int);
            wr2ToCode(sarg);
            break;
/* ohne Parameter */
        default :
            break;
    }
    va_end(ap);
    // OK
    return 1;
}
