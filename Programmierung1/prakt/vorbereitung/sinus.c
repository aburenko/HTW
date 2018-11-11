#include<stdio.h>
#include<math.h>
#include<stdlib.h>

char buf[5];

int main() {
    fgets(buf, 4, stdin);
    
    double x = atof(buf);
    double sinus = 0.0;
    double summand = x;
    int fak = 2;
    while(fabs(summand) > 0.00009) {
        sinus += summand;
        summand *= -(x*x)/((fak+1)*(fak));
        fak=fak+2;
    }
    printf("%lf\n", sinus);
    printf("%lf\n", sin(x));
    return 0;
}
