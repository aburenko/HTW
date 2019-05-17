#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"list.h"

int main() {
    tList *pList = CreateList(); 
    while(buf[0] != 'Q') {
        puts("Enter (I)nsert / (O)ut / (Q)uit:");
        fgets(buf, 128, stdin);
        if(buf[0]=='I') {
            puts("Your element:");
            fgets(buf, 128, stdin);
            buf[strlen(buf)-1] = 0;
            char *ptmp = malloc(strlen(buf)+1);
            if(ptmp == NULL) {
                puts("Kein Spreicher :)");
                return -1;
            }
            strcpy(ptmp, buf);
            InsertHead(pList, ptmp);
        }
        else if(buf[0]=='O') {
            char *ptmp = GetFirst(pList);
            if(ptmp == NULL) {
                puts("List is empty :)");
                continue;
            }
            printf("Out: %s", ptmp);
            RemoveItem(pList);
        }
        else {
            puts("I or O to use functions");
        }
    }
    char *ptmp = GetFirst(pList);
    while(ptmp != NULL) {
        RemoveItem(pList);
        ptmp = GetFirst(pList);
    }
    DeleteList(pList);
    return 0;
}
