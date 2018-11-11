#include <stdio.h>
#include <ctype.h>
int main()
{
  int i,j;
  for (i=0; i<128/4+2; i++) //32
  {
    printf("\n| ");
    for (j=0; j<128; j += 128/4) 
    {
      printf("%3d %2X ",i+j, j+i);
      if ( isgraph(i+j) )
          printf(" %c  | ", i+j);
      else printf(" .  | ");
    }
  }
  printf("\n %d  %d\n",i, j);
  return 0;
}
