#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct{
  char name[30+1];
  char shortForm[3+1];
  char currencyName[3+1];
  double valueBuy;
  double valueSell;
}Currency;

Currency vWrg[]=
{
  #include  "waehrung.dat" 
};

void sortName(Currency * vWrg, int size) 
{
    int a,b,c = 0;
    Currency tmpCurr;
    
    for(a=0; a<size-1; a++) 
    {
        for(b=a+1; b<size; b++)
        {    
                if(strcmp(vWrg[a].name, vWrg[b].name) > 0)
                {
                  tmpCurr = vWrg[a];
                  vWrg[a] = vWrg[b];
                  vWrg[b] = tmpCurr;
                }
        }
    }
} 

void sortCurrencyName(Currency * vWrg, int size) 
{
    int a,b,c = 0;
    Currency tmpCurr;
    
    for(a=0; a<size-1; a++) 
    {
        for(b=a+1; b<size; b++)
        {    
                if(strcmp(vWrg[a].currencyName, vWrg[b].currencyName) > 0)
                {
                  tmpCurr = vWrg[a];
                  vWrg[a] = vWrg[b];
                  vWrg[b] = tmpCurr;
                }
        }
    }
} 

void printArrOut (Currency * vWrg, int size, char str[]) {
    printf("\nSortiert nach %s", str);
    printf("\n================");
    printf("\n%-30s  %-3s %-3s %-8s %-8s\n\n",
        "Land","lkz"," Wkz", "  Ankauf", " Verkauf"
    );  
    int i;
    for(i=0;i<size;i++)
       printf("%-30s ,%-3s ,%-3s ,%-8lf ,%-8lf\n",
             vWrg[i].name, 
             vWrg[i].shortForm,
             vWrg[i].currencyName,
             vWrg[i].valueBuy,
             vWrg[i].valueSell
            );
}

int main()
{
    int size = sizeof(vWrg)/sizeof(Currency);
    printf("%d %d \n", sizeof(vWrg), sizeof(Currency) );
    sortName(vWrg, size);
    printArrOut(vWrg, size, "Land");
     
    sortCurrencyName(vWrg, size);
    printArrOut(vWrg, size, "Currency name");
    
    return 0;
}
