#include <iostream>
using namespace std;
#include "cstrg.hpp"

int main()
{
    STRING M1="Max";
    STRING M2("Moritz");
    STRING M3;
    M3=M1+" und "+M2;
    cout << M1 << endl;
    cout << "Wilhelm Busch:\n"<< M3<<"\n";
    M1="______________";
    M1[0]='+';
    M1[M1.getLength()-1]=M1[0];
    cout << M1<<'\n';
    return 0;
}
