#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<ctype.h>

char buf[128];

int funcif (char y) {
  printf("char y : %d\n",y); 
  if(y>='0' && y<='9') return 0;
  else if (y>='a' && y<='z') return 1;
  else if (y>='A' && y<='Z')  return 2;
  else return 3;
}

int funcswitch (char y) {
    switch(y) {
        case '0' ... '9': return 0;
        case 'a' ... 'z': return 1;
        case 'A' ... 'Z': return 2;
        default : return 3;
    }
}
 
int funcswitch2 (char y) {
    int i;
    switch(y) {
        case '0': 
        case '1': 
        case '2': 
        case '3': 
        case '4': 
        case '5': 
        case '6': 
        case '7': 
        case '8': 
        case '9': i=0; break;
        case 'a' ... 'z': i=1; break;
        case 'A' ... 'Z': i=2; break;
        default : i=3; break;
    }
    return i;
}

int funcctype (char y) {
  printf("char y : %d\n",y); 
  if(isdigit(y)) return 0;
  else if (islower(y)) return 1;
  else if (isupper(y))  return 2;
  else return 3;
}

int main()
{
  printf("===================================\n");
  printf("= 0-digit === 1-lower === 2-upper =\n");
  printf("===================================\n");
  while((buf[0]!='q') || (buf[1]!='q')) {
    fgets(buf,128,stdin); 
    char x=buf[0];
    printf("%d\n", funcctype(x));
  }
  return 0;	   
}
