#include <iostream>
#include <iomanip>
#include <cstring>
#include "fraction.hpp"


using namespace std;

int main() {
    Fraction a(2,4);
    Fraction b(2,3);
    Fraction res = a.add(b);
    res.show();
    res = a.subtract(b);
    res.show();
    res = a.multiply(b);
    res.show();
    res = a.divide(b);
    res.show();
    
    return 0;
}
