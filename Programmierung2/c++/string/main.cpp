#include <iostream>
// #include <>
#include "String.hpp"

using namespace std;

int main() {
    
    STRING A("abcDADS");
    A.show();
    STRING B = A;
    B.show();
    STRING C('L',5);
    C.show();
    C.CIdx(4) = '5';
    C.show();
    B=C;
    B.show();
    return 0;
}
