/*
 *
 * Name: Anton Burenko
 * s-Nummer: s76905
 * Studiengruppe: 17/041/01
 * Dozent: Prof. Dr.-Ing. Arnold Beck
 *
 * */
#include <stdio.h>
#include <ctype.h>
#include "parser.h"

static tMorph Morph = {0};

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("file was %s\n", argv[1]);
        return -2;
    }
    printf("file was %s\n", argv[1]);
    initLex(argv[1]);
    int return_value = parse(NULL);
    printf("return value was %d\n", return_value);
    puts("");
//    do {
//        Morph = Lex();
//        printf("Line%4d, Col%3d: ", Morph.PosLine, Morph.PosCol);
//        switch (Morph.MC) {
//            case mcSymb :
//                if (Morph.Val.Symb == zERG) printf(".Symbol :=\n");
//                else if (Morph.Val.Symb == zLE) printf(".Symbol <=\n");
//                else if (Morph.Val.Symb == zGE) printf(".SSymbol >=\n");
//                else if (Morph.Val.Symb == zBGN) printf("Symbol _BEGIN\n");
//                else if (Morph.Val.Symb == zCLL) printf("Symbol _CALL\n");
//                else if (Morph.Val.Symb == zCST) printf("Symbol _CONST\n");
//                else if (Morph.Val.Symb == zDO) printf("Symbol _DO\n");
//                else if (Morph.Val.Symb == zEND) printf("Symbol _END\n");
//                else if (Morph.Val.Symb == zIF) printf("Symbol _IF\n");
//                else if (Morph.Val.Symb == zODD) printf("Symbol _ODD\n");
//                else if (Morph.Val.Symb == zPRC) printf("Symbol _PROCEDURE\n");
//                else if (Morph.Val.Symb == zTHN) printf("Symbol _THEN\n");
//                else if (Morph.Val.Symb == zVAR) printf("Symbol _VAR\n");
//                else if (Morph.Val.Symb == zWHL) printf("Symbol _WHILE\n");
//                if (isprint(Morph.Val.Symb))printf("Symbol %c\n", (char) Morph.Val.Symb);
//                break;
//            case mcNum :
//                printf("Zahl %ld\n", Morph.Val.Num);
//                break;
//            case mcIdent:
//                printf("Ident %s\n", (char *) Morph.Val.pStr);
//                break;
//            case mcEmpty:
//                printf("mcEmpty\n");
//                break;
//        }
//    } while (!(Morph.MC == mcSymb && Morph.Val.Symb == -1));
    return 0;
}

