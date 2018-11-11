#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//#include"debug.h"


void sortStr();
void outStr();
void addNewElement();

typedef char tStr[16];
char vStr[][15+1] = {"Max", "Moritz", "Bolte", "Hans Huckebein", "Helene", "Antonius", "Boeck", "Maecke", "Lempel", "Schlich"};

int main () {
    tStr * p;
    p = malloc(sizeof(vStr));
    memcpy(p, vStr, sizeof(vStr));
    int sizePP;
    sortStr(p,sizeof(vStr)/16);
    outStr(p,sizeof(vStr)/16);
    char buf[30+1] = "go";
    char key[]="quit";
    while(1){
        fgets(buf,30,stdin);
        buf[strlen(buf)-1] = 0;
        if(strcmp(buf, key) == 0){ 
            break;
        }
        addNewElement(p,sizeof(vStr)+16*(1+sizePP),0,buf);
            sizePP++;
    }
    printf("_________----_____-\n");
    outStr(p,sizeof(vStr)/16+sizePP);

    return 0;
}

void addNewElement (tStr * p, int size, int num, char * strTmp) {
    p = realloc(p, size+16);
    memmove(p+num+1,p+num,size-num*16);
    memcpy(p+num,strTmp,16);
}


void sortStr(tStr * p, int size) 
{
    int a,b = 0;
    char tmp[16];
    for(a=0; a<size-1; a++) 
    {
//         DEBUG_INT(a)
//         DEBUG_CHR('\n')
        for(b=a+1; b<size; b++)
        {    
            if(strcmp(vStr[a],vStr[b])>0)
            {
                strcpy(tmp, vStr[a]);
                strcpy(vStr[a], vStr[b]);
                strcpy(vStr[b], tmp);
            }
        }
    }
} 

void outStr(tStr * p, int size) 
{
    int a,b = 0;
    tStr * pTmp = p;
    for(a=0; a<size; a++) 
    {
        printf("%s\n", pTmp);
    	pTmp++;
    }
}