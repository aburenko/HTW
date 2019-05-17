#include<stdio.h>
#include<stdarg.h>
#include<stdlib.h>
#include "figuren.h"

double A(int kz, ...);

int main(int argc, int argv[]) {
//     if(argc < 2) {
//         printf("usage: %s <figure> <arguments> ...\n", argv[0]);
//         exit(EXIT_FAILURE);
//     }
//     char *argforfunc[];
//     int i;
//     for(i=1; i<=argc; i++)
//         argforfunc[i-1] = argv[i];
    printf("%lf\n", A('q',3.0));
    printf("%lf\n", A('r',3.0,2.0));
    printf("%lf\n", A('t',8.0,7.0,1.5));
    printf("%lf\n", A('p',5.0,6.0));
    printf("%lf\n", A('v',4,2.0));
    printf("%lf\n", A('d',4.0,3.0));
    printf("%lf\n", A('k',3.0));
    
    return 0;
}


double A(int kz, ...) {
    va_list ap;
    int n;
    double a, b, c, h, r;
    va_start(ap, kz);
    switch(kz) {
        case 'q':
            a = va_arg(ap,double);
            return Quadrat(a);
            break;
        case 'r':
            a = va_arg(ap,double);
            b = va_arg(ap,double);
            return Rechteck(a,b);
            break;
        case 't':
            a = va_arg(ap,double);
            c = va_arg(ap,double);
            h = va_arg(ap,double);
            return Trapez(a,c,h);
            break;
        case 'p':
            a = va_arg(ap,double);
            h = va_arg(ap,double);
            return Parallelogr(a,h);
            break;
        case 'v':
            n = va_arg(ap,int);
            a = va_arg(ap,double);
            return regVieleck(n,a);
            break;
        case 'd':
            c = va_arg(ap,double);
            h = va_arg(ap,double);
            return Dreieck(c,h);
            break;
        case 'k':
            r = va_arg(ap,double);
            return Kreis(r);
            break;
        default:
            puts("please use : q,r,t,p,v,d or k");
            exit(EXIT_FAILURE);
    }
}
