/*func.h*/
// list element
typedef struct unit{
    char unitName[200+1];
    int unitID;
    int unitCount;
}unit;
// list connector
typedef struct tcnt {
    struct tcnt * pnxt;
    unit * pdata;
}tcnt;
// list seed
typedef struct {
    tcnt * pfirst;
    tcnt * plast;
}tlist;

// initialize variables for global use
char buf[128];
tlist * list;

// funcListMan.c Man-manipulations
// FUNKTIONS to add,change,delete element or create list
void listCreate(); // allocate memory for neu list and initialize its variables to NULL
void listSortBy(char type); // sort list by N = Name I = ID
int insFirst(unit * m); // insert at the begin
int insLast(unit * m); // insert at the end
int insert(unit * m, int elementNummer); // insert after <elementNummer> r=0...n-1
int insAlpha(unit * m); // insert alphabetic 
int insAfter(unit *m, tcnt * tcntPrev); // insert after <pointer>
int listChangeParameter(unit * m, int option); //overwrites one parameter 1...3
int deleteElement(int elementNummer); // delete element <elementNummer> r=0...n-1
int unitWriteParameter(int option, unit * m, char * ptr); // write a parameter to unit
int unitCopyParameter(int option, unit *dest, tcnt *src); // copy a parameter from tcnt
unit * putUnit(); // create new element(unit) and return it

// funcListDB.c DB-database
// FUNKTIONS for DB files and whole list manipulations 
int listWriteInDB(); // write list in form of CSV into DB
int listReadFromDB(); // read -||- from DB 
int listCreateDBBackUP(FILE *original); 
int listFree(); // clear list variables
void listOutput(); // console output

// funcPrintCGI.c
// FUNKTIONS for operating html form
void printHead(); // head,title,style
void printBody(); // table,add element
void proccessPosted(); // get POST from html-form
char charToLow(char ch); // return low case alpha
void searchCore(char *pstr); // complete search request
void sortCore(char type); // complete sort request
void listChangeParameterCore(char *pstr); // complete request to change a parameter
void addElemCore(char *pstr); // complete add element request
void replaceAvailibleCharacters(char *ch); // replace some characters