#include<stdio.h>
#include<stdlib.h>

//structs
typedef struct connector {
    struct connector *pnext;
    struct connector *pprev;
    float value;
    void *pdata;
} t_cnt;

typedef struct list {
    t_cnt *pfirst;
    t_cnt *pcurr;
} t_list;

//functions
t_list *listCreate();
void insertBehindValue(t_list *list, float valueNew);
void printList(t_list *list);
void savefloatlist(t_list *list);
void readfloatlist(t_list *list);

int main() {
    t_list *list = listCreate();
    
//     insertBehindValue(list, 1.0);
//     insertBehindValue(list, 2.5);
//     insertBehindValue(list, 0.4333);
//     savefloatlist(list);
    readfloatlist(list);
    printList(list);
    return 0;
}

t_list *listCreate() {
    t_list *list = malloc(sizeof(t_list));
    if(list==NULL) {puts("error malloc"); exit(-1);}
    list->pfirst = (t_cnt*)NULL;
    return list;
}

void insertBehindValue(t_list *list, float valueNew) {
    t_cnt *connectorNew = malloc(sizeof(t_cnt));
    if(connectorNew==NULL) {puts("error malloc"); exit(-1);} 
    connectorNew->value = valueNew;
    if(list->pfirst == NULL) {
        list->pfirst = connectorNew;
        list->pfirst->pprev = list->pfirst->pnext = connectorNew;
    }
    else {
        connectorNew->pnext = list->pfirst;
        connectorNew->pprev = list->pfirst->pprev;
        list->pfirst->pprev->pnext = connectorNew;
        list->pfirst->pprev = connectorNew;
    }
}

void printList(t_list *list) {
    if(list->pfirst == NULL) return;
    list->pcurr = list->pfirst;
    do {
        printf("%lf\n", list->pcurr->value);
        list->pcurr = list->pcurr->pnext;
    } while(list->pcurr != list->pfirst);
}

void savefloatlist(t_list *list) {
    if(list->pfirst == NULL) return;
    list->pcurr = list->pfirst;
    FILE *file = fopen("floatdata.dat","w");
    do {
        fprintf(file ,"%lf ", list->pcurr->value);
        list->pcurr = list->pcurr->pnext;
    } while(list->pcurr != list->pfirst);
    fclose(file);
}

void readfloatlist(t_list *list) {
    float floattmp = 0.0;
    FILE *file = fopen("floatdata.dat","r");
    int i;
    while(fscanf(file ,"%f ", &floattmp) == 1) {
        insertBehindValue(list, floattmp);
    }
    fclose(file);
}