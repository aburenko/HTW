#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main() {

    
	srand ( time(NULL) );
    long int r = rand();
    
    printf("%ld\n",r);
    return r;
}
