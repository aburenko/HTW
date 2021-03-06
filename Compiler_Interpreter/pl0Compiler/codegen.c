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

char * getPCode() {
    return pCode;
}

int getBufferExtension() {
    int temp = bufferExtension;
    bufferExtension  = 0;
    return temp;
}

void wr2ToCodeConst(long x) {
    wr2ToCode(x & 0x0000ffff);
    wr2ToCode((x & 0xffff0000) >> 16);
}

void codeEndProcedure(void) {
    printf("codeEndProcedure called\n");
    short procedureLength = pCode - pCurrProcedureBegin;
    printf("codeEndProcedure length was %d\n", procedureLength);
    wr2ToCodeAtP(procedureLength, pCurrProcedureBegin + 1);
}

void writeToFile(void) {
    char * destinationPath = "compiled.cl0";
    FILE *file = fopen(destinationPath, "w");

    for (int i = 0; i < pCode - pCodeBegin; i++) {
        fputc((char)pCodeBegin[i], file);
    }
    fclose(file);
}

int code(tCode Code, ...) {
    short sarg;
    printf("code called %#02x\n", Code);
    if (pCode == NULL) {
        pCodeBegin = pCode = malloc(LenCode);
        if (pCode == NULL) {
            printf("pCode was null, exit\n");
            exit(-4);
        }
        for (int i = 0; i < 2; ++i) {
            wr2ToCode(0);
        }
    }
    if (pCode - pCodeBegin + MAX_LEN_OF_CODE >= LenCode)
        // Ueberwachung des Zwischencodegenerierungspuffers
    {
        char *oldPCode = pCode;
        int lenFromProcBegin = pCode - pCurrProcedureBegin;
        char *xCode = realloc(pCodeBegin, (LenCode += 1024));
        if (xCode == NULL) {
            printf("xCode was null, exit\n");
            exit(-5);
        };
        pCode = xCode + (pCode - pCodeBegin);
        pCurrProcedureBegin = pCode - lenFromProcBegin;
        pCodeBegin = xCode;
        bufferExtension = abs(pCode - oldPCode);
        printf("buffer extended\n");
    }
    *pCode++ = (char) Code;

    va_list ap;
    va_start(ap, Code);
    switch (Code) {
/* Befehle mit 3 Parametern */
        case entryProc:
            printf("new proc begin was set\n");
            pCurrProcedureBegin = pCode - 1;
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
