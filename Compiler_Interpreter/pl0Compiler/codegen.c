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
#include <stdio.h>
#include "codegen.h"

void wr2ToCodeAtP(short x, char *pD) {
    *pD = (char) (x & 0xff);
    *(pD + 1) = (char) (x >> 8);
}

void wr2ToCode(short x) {
    wr2ToCodeAtP(x, pCode);
    pCode += 2;
}

void wr2ToCodeAtBegin(short x) {
    wr2ToCodeAtP(x, pCodeBegin);
}

void writeToFile(void) {
    FILE *file = fopen("compiler_output", "w");

    for (int i = 0; i < pCode - pCodeBegin; i++) {
        fputc((char)pCodeBegin[i], file);
    }
    fclose(file);
}

int code(tCode Code, ...) {
    printf("code called %#02x\n", Code);
    if (pCode == NULL) {
        pCodeBegin = pCode = malloc(LenCode);
        if (pCode == NULL) {
            printf("pCode was null, exit");
            exit(-4);
        }
        for (int i = 0; i < 2; ++i) {
            wr2ToCode(0);
        }
    }
    va_list ap;
    short sarg;
    if (pCode - pCodeBegin + MAX_LEN_OF_CODE >= LenCode)
        // Ueberwachung des Zwischencodegenerierungspuffers
    {
        char *xCode = realloc(pCodeBegin, (LenCode += 1024));
        if (xCode == NULL) {
            printf("xCode was null, exit");
            exit(-5);
        };
        pCode = xCode + (pCode - pCodeBegin);
        pCodeBegin = xCode;
    }
    *pCode++ = (char) Code;
    va_start(ap, Code);

    switch (Code) {
/* Befehle mit 3 Parametern */
        case entryProc:
            sarg = va_arg(ap, int);
            wr2ToCode(sarg);
/* Befehle mit 2 Parametern */
        case puValVrGlob:
        case puAdrVrGlob:
            sarg = va_arg(ap, int);
            wr2ToCode(sarg);
/* Befehle mit 1 Parameter */
        case puValVrMain:
        case puAdrVrMain:
        case puValVrLocl:
        case puAdrVrLocl:
        case puConst:
        case jnot:
        case call:
        case jmp:
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
