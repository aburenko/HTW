#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct t_waehrnung {
    char country[30+1];
    char shortn[3+1];
    char currency[3+1];
    float fbuy;
    float fsell;
} t_w;

t_w arrW[] = {
    #include  "waehrung.dat" 
};

void printarr(int size);
void assignsell(int size);
void sort(int size);

int main() {
    int size = sizeof(arrW)/sizeof(t_w);
    assignsell(size);
    printarr(size);
    sort(size);
    printarr(size);
    return 0;
}

void assignsell(int size) {
    int i = 0;
    for(;i<size;i++) {
        arrW[i].fsell = arrW[i].fbuy*0.92;
    }
}

void printarr(int size) {
    int i = 0;
    for(;i<size;i++) {
        printf("%-30s %4s %4s %8lf %8lf\n", 
            arrW[i].country,
            arrW[i].currency,
            arrW[i].shortn,
            arrW[i].fbuy,
            arrW[i].fsell
        );
    }
    puts("");
}

void sort(int size) {
    int i,o;
    t_w t_w_tmp;
    for(o=0;o<size-1;o++) {
        for(i=o+1; i<size; i++) {
            if(strcmp(arrW[o].country,arrW[i].country) > 0) {
                t_w_tmp = arrW[o];
                arrW[o] = arrW[i];
                arrW[i] = t_w_tmp;
            }
        }
    }
}

