#include<iostream>
#include"Figur.hpp"
using namespace std;

int main() {
    
    Square s(3.5);
    Circle c(3.5);
    Rectangle r(8.8,5);
    Figur* pa[] = {&s,&c,&r};
    for(int i=0; i<3; i++)
        cout << *pa[i];
    return 0;
}
