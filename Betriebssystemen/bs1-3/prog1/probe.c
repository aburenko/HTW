#include<stduo.h>

int main()
{
  double sin = 0;
  printf("Geben Sie X von sinx an");
  scanf("%d", sin);
  for(i=0;i<4;i++)
  {
    sin = sin + (-1)^i; //zu erweitern
  }
  printf("%d", sin);
  return 0;
}

