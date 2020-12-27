/*
 *
 * Name: Anton Burenko
 * s-Nummer: s76905
 * Studiengruppe: 17/041/01
 * Dozent: Prof. Dr.-Ing. Arnold Beck
 *
 *
 * Erweiterungen laut dem S-Nummer 43733
 * 43733%3+1 = 3 => 3. Erkennung und Überlesen von Kommentaren im Pascalstil (*..... kommentar ....*)
 * 43733%2+1 = 2 => 2. Arrays von Zahlen
 *
 * */
#include <stdio.h>
#include <ctype.h>
#include "parser.h"

void listTest() {
    pCurrProcedure = createProc(NULL);
    t_list *list = listCreate();
    pCurrProcedure->childList = list;
    tBez * bez = createBez("C");
    insertBehindValue(list, bez);
    searchBez(pCurrProcedure, "C");
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("file was %s\n", argv[1]);
        return -2;
    }
    printf("file was %s\n", argv[1]);
    initLex(argv[1]);
    int return_value = parse((tBog *)NULL);
    printf("return value was %d\n", return_value);
    puts("");
    return 0;
}

