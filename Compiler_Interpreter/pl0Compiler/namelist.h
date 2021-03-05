/*
 *
 * Name: Anton Burenko
 * s-Nummer: s76905
 * Studiengruppe: 17/041/01
 * Dozent: Prof. Dr.-Ing. Arnold Beck
 *
 * */
#ifndef NAMELIST_HEADER
#define NAMELIST_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "codegen.h"
#include "lex.h"

#define OK 1
#define FAIL 0

extern tMorph Morph;

typedef enum eStructType {
    var_struct, const_struct, proc_struct, bez_struct, jnot_struct, jmp_struct, st5_struct
} tStructType;

// Namenslisteneintrag
typedef struct {
    tStructType structType;
    short IdxProc;
    void *pObj;
    char *pName;
} tBez;

// basic list elements ======================
typedef struct connector {
    struct connector *pnext;
    void *value;
} t_cnt;

typedef struct tLABL
{
    tStructType structType;
    char* iJmp;
} tLabl;

typedef struct list {
    t_cnt *pfirst;
    t_cnt *pcurr;
} t_list;

// basic elements ===========================
//typedef char* tKz;


// Variablenbeschreibung
typedef struct tVAR {
    tStructType structType;
    int Dspl; // Relativadresse
    int type; // 0 - var, 1 - arr
} tVar;

// Konstantenbeschreibung
typedef struct tCONST {
    tStructType structType;
    long Val;
    int Idx;
} tConst;

// Prozedurbeschreibung
typedef struct tPROC {
    tStructType structType;
    short IdxProc;
    struct tPROC *pParent;
    t_list *childList;
    t_list *pLLabl;
    int SpzzVar;
} tProc;

//functions
t_list *listCreate();

void insertBehindValue(t_list *list, void *valueNew);

void printList(t_list *list);

// global var
static tProc *mainProc = NULL;
static tProc *pCurrProcedure = NULL;
static t_list *pConstList = NULL;
static t_list *pLabelList = NULL;
static short idxCnstCounter = 0;
static short idxProcCounter = 0;

// functions from lecture
void initNameList(void);

tBez *createBez(char *pBez);

tConst *createConst(long Val);

tVar *createVar(void);

tProc *createProc(tProc *pParent);

tConst *searchConst(long Val);

tBez *searchBez(tProc *pProc, char *pBez);

tBez *searchBezGlobal(char *pBez);

int Bl1(void);

int Bl2(void);

int Bl3(void);
int Bl3_E(void);
int Bl3_SWAP(void);
int Bl3_SIZE(void);

int Bl4(void);

int Bl5(void);

int Bl6(void);


int pr1(void); // Endebehandlung

int st1(void); // Linke Seite der Zuweisung
int st2(void); // Rechte Seite der Zuweisung
int st8(void); // Prozeduraufruf
int st9(void); // Eingabe
int st10(void); // Ausgabeq

// conditionals
int st3(void); // if, nach Condition
int st4(void); // if, nach Statement

// loops
int st5(void); // while
int st6(void); // while, nach Condition
int st7(void); // while, nach Statement

int s_get(void);

int ex1(void); // negative sign
int ex2(void); // addition
int ex3(void); // subtraction

int te1(void); // mul
int te2(void); // div

int fa1(void); // factor numeral
int fa2(void); // factor ident

int co1(void); // Codegenerierung odd
int co2_to_co7(void);// Vergleichsoperator
int co8(void); // Codegenerierung des gespeicherten Vergleichsbefehles

#endif