#include<stdio.h>
#include<stdlib.h>

char buf[128];

char* crtBitStr(unsigned int x) {
    int msk=1;
    static char arr[sizeof(x)*8+sizeof(x)-2];

    int i,j,a,tmp=0;
    tmp=x;
    a=sizeof(x)*8+sizeof(x)-2;
    for(i=0; i<sizeof(x); i++) {
        for(j=0; j<8; j++) {
            if(tmp&msk) { //wahr => 1
                arr[a]='1';
            } else { // => 0
                arr[a]='0';
            }
            a--;
            tmp>>=1;
        }
        arr[a] = '|';
        a--;
    }
    return arr;
}

int main()
{
  unsigned int x;
  printf("Eingabe einer int-Zahl: ",x);
  fgets(buf,128,stdin); x=atoi(buf);
  printf("sizeof(x): %d\n", sizeof(x));
  printf("***\n");
  printf("dez: %d\n", x);
  printf("hex: %08X\n", x);
  printf("bin: %s\n", crtBitStr(x));
  printf("+++\n");
  
  return 0;	   
}
