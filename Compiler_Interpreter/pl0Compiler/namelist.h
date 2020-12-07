/*
 *
 * Name: Anton Burenko
 * s-Nummer: s76905
 * Studiengruppe: 17/041/01
 * Dozent: Prof. Dr.-Ing. Arnold Beck
 *
 * */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lex.h"

#define OK 1
#define FAIL 0

extern tMorph Morph;

// basic elements ===========================
//typedef char* tKz;

typedef enum eStructType {
    var_struct, const_struct, proc_struct, bez_struct
} tStructType;

// Namenslisteneintrag
typedef struct {
    tStructType structType;
    short IdxProc;
    void *pObj;
    char *pName;
} tBez;

// Variablenbeschreibung
typedef struct tVAR {
    int Dspl; // Relativadresse
} tVar;

// Konstantenbeschreibung
typedef struct tCONST {
    long Val;
    int Idx;
} tConst;


// basic list ===============================
//structs
typedef struct connector {
    struct connector *pnext;
    void *value;
} t_cnt;

typedef struct list {
    t_cnt *pfirst;
    t_cnt *pcurr;
} t_list;

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
static int idxCnstCounter = 0;
static int idxProcCounter = 0;

// functions from lecture
void initNameList(void);

tBez *createBez(char *pBez);

tConst *createConst(long Val);

tConst *searchConst(long Val);

tVar *createVar(void);

tProc *createProc(tProc *pParent);

tBez *searchBez(tProc *pProc, char *pBez);

tBez *searchBezGlobal(char *pBez);

int Bl1(void);

int Bl2(void);

int Bl3(void);

int Bl4(void);

int Bl5(void);
