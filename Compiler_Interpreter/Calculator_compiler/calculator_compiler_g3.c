/*
 *
 * Name: Anton Burenko
 * s-Nummer: s76905
 * Studiengruppe: 17/041/01
 * Aufgabe: expression1
 * Dozent: Prof. Dr.-Ing. Arnold Beck
 *
 * */
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

typedef struct morph {
    int mc;
    union {
        double dval;
        char cval;
    };
} MORPHEM;

enum mcodes {
    mempty, mop, mdbl
};

static MORPHEM m;

double fac();

double term();

void lex(char *pX) {
    static char *px;

/* Initialisierung*/
    if (pX != NULL) {
        m.mc = mempty;
        px = pX;
    }

/* lexiaklische Analyse */
    if (*px == '\0') {
        m.mc = mempty;
    } else {
        for (; *px == ' ' || *px == '\t'; px++);

        if (isdigit(*px) || *px == '.')
            // numeral
        {
            m.dval = strtod(px, &px);
            m.mc = mdbl;
        } else
            // Symbol
            switch (*px) {
                case '+':
                case '-':
                case '*':
                case '/':
                case '(':
                case ')':
                    m.cval = *px++;
                    m.mc = mop;
                    break;
                    // end or wrong char
                default :
                    m.mc = mempty;
            }
    }
}

double expr(void) {
    double tmp = term();
    while (m.mc == mop && (m.cval == '+' || m.cval == '-')) {
        if (m.cval == '-') {
            lex(NULL);
            tmp -= term();
        }
        else if (m.cval == '+') {
            lex(NULL);
            tmp += term();
        }
    }
    return tmp;
}

double term() {
    double tmp = fac();
    while (m.mc == mop && (m.cval == '*' || m.cval == '/')) {
        if (m.cval == '*') {
            lex(NULL);
            tmp *= fac();
        } else if (m.cval == '/') {
            lex(NULL);
            tmp /= fac();
        }
    }
    return tmp;
}

double fac() {
    double tmp;
    if (m.mc == mop) {
        if (m.cval == '(') {
            lex(NULL);
            tmp = expr();
            if (m.mc != mop || m.cval != ')')exit(1);
            lex(NULL);
        } else exit(2);
    } else if (m.mc == mdbl) {
        tmp = m.dval;
        lex(NULL);
    } else exit(3);
    return tmp;
}


int main(int argc, char *argv[]) {
    char *pBuf = "12/2*3";
    printf("%s\n", pBuf);
    lex(pBuf);
    printf("%-10.4f\n", expr());
    free(pBuf);
    return 0;
}
