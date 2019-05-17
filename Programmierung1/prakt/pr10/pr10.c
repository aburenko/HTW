#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#include"mat.h"

void outArt (tArt *, int);
void sortByName(tArt * Artikel, int size);
void sortByArtNum(tArt * Artikel, int size);

int main (int argc, char * argv[]) {
   FILE * pf = fopen(argv[1],"rb");
   if(!pf) return -1;
   
   fseek(pf,0,SEEK_END);
   int len=ftell(pf);
   fseek(pf,0,SEEK_SET);

   tArt * Artikel = malloc(len);
   char a;
   FILE * tmpf;
   

   fread(Artikel, sizeof(tArt), len/sizeof(tArt), pf);
   outArt(Artikel, len/sizeof(tArt));
   !(strcmp(argv[2], "name")) ? sortByName(Artikel, len/sizeof(tArt)) : sortByArtNum(Artikel, len/sizeof(tArt));
   outArt(Artikel, len/sizeof(tArt));
   
   fclose(pf);
}

void outArt (tArt * Artikel, int size) {
    int i;
    printf("%-30s %-20s %-5s %-15s %-15s\n", "Vbez","vNr","Lbst", "Soll", "Unterschrift");
    for(i=0;i<size;i++) {
        printf("%-30s %-20s %-5ld %-15s %-15s\n", Artikel[i].vBez,Artikel[i].vNr,Artikel[i].Lbst, "....", "............");
    }
}

void sortByName(tArt * Artikel, int size) 
{
    int a,b,c = 0;
    tArt tmpArt;
    
    for(a=0; a<size-1; a++) 
    {
        for(b=a+1; b<size; b++)
        {    
                if(strcmp(Artikel[a].vBez, Artikel[b].vBez) > 0)
                {
                  tmpArt = Artikel[a];
                  Artikel[a] = Artikel[b];
                  Artikel[b] = tmpArt;
                }
        }
    }
} 

void sortByArtNum(tArt * Artikel, int size) 
{
    int a,b,c = 0;
    tArt tmpArt;
    
    for(a=0; a<size-1; a++) 
    {
        for(b=a+1; b<size; b++)
        {    
                if(strcmp(Artikel[a].vNr, Artikel[b].vNr) > 0)
                {
                  tmpArt = Artikel[a];
                  Artikel[a] = Artikel[b];
                  Artikel[b] = tmpArt;
                }
        }
    }
} 
