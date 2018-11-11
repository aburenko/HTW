#include<stdio.h>
#include<math.h>
#include<stdlib.h>

char vBuf[128];

int main() {
/*
  double d = 0;
  printf("Geben Sie Durchmesser in mm: ");
  fgets(vBuf, 128, stdin); d = atof(vBuf);
  double circleArea = 0;
  //von mm in cm
  d *= 0.1; 
  //berechen Flaeche  
  circleArea = M_PI*d*d/4;

  printf("%lf\n", circleArea);
*/

  int d = 0;
  printf("Geben Sie Durchmesser in mm: ");
  fgets(vBuf, 128, stdin); d = atoi(vBuf);
  int a,b = 0;
  
  b = (314*d*d)/4;  
  
  printf("%04d.%04d\n", a, b);
  return 0;
}
