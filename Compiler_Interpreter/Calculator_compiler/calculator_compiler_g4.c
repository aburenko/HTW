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

double Rexpr(double tmp)
{
    if (m.cval=='-' && m.mc==mop )
    {lex(NULL); tmp -=term();tmp=Rexpr(tmp);} else
    if (m.cval=='+' && m.mc==mop )
    {lex(NULL); tmp+=term();tmp=Rexpr(tmp);}
    return tmp;
}

double expr(void) {
    double tmp = term();
    return Rexpr(tmp);
}

double Rterm(double tmp)
{
    if (m.cval == '*' && m.mc == mop)
    {
        lex(NULL);
        tmp *= fac();
        tmp = Rterm(tmp);
    }
    else if (m.cval == '/' && m.mc == mop)
    {
        lex(NULL);
        tmp /= fac();
        tmp = Rterm(tmp);
    }
    return tmp;
}

double term() {
    double tmp = fac();
    return Rterm(tmp);
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
