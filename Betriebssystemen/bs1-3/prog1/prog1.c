#include <stdio.h>
#include <ctype.h>
int main()
{
  int i,j;
  for (i=0; i<4; i++)
      printf("Idec hex Char ");
  for (i=0; i<128/4; i++) //32
  {
    printf("\n| ");
    for (j=0; j<128; j += 128/4) 
    {
      printf("%3d %2X ",i+j, i+j);
      if ( isgraph(i+j) )
          printf(" %c  | ", i+j);
      else printf(" .  | ");
    }
  }
  printf("\n %d  %d\n",i, j);
  return 0;
}
