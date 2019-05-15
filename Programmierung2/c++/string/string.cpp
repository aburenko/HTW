#include <iostream>
#include <cstring>
#include "String.hpp"

using namespace std;

STRING::STRING () {
    pBuf = NULL;
    Len  = 0;
}

STRING::STRING (const char* pStr) {
    if (pStr != NULL) {
        Len = strlen(pStr);
        pBuf = new char[Len];
        strcpy(pBuf, pStr);
    }
}

STRING::STRING (const STRING& other) {
    this->Len = other.Len;
    this->pBuf = new char[Len];
    strcpy(this->pBuf,other.pBuf);
}

STRING::STRING (char C, int n) {
    pBuf = new char[n];
    for (int i=0; i<n; i++) {
        pBuf[i] = C;
    }
    Len = n;
}

STRING::~STRING () {
    delete []pBuf;
}

void STRING::show () const {
    if (pBuf == NULL) return; 
    
    char *pTemp = pBuf;
    while(*pTemp!='\0') {
        cout << *pTemp;
        pTemp++;
    }
    cout << endl;
}

char& STRING::CIdx(unsigned int i) {
    cout << Len << endl;
    if( i >= Len) {
        cout << "Indexzugriffsfehler" << endl;
        static char DUMMY = '0';
        return DUMMY;
    }
    return pBuf[i];
}
    
STRING& STRING::operator= (const STRING& other) {
    this->Len = other.Len;
    delete []pBuf;
    this->pBuf = new char[Len];
    strcpy(this->pBuf,other.pBuf);
}
