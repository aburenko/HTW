#include <iostream>
#include <iomanip>
#include <cstring>
#include "fraction.hpp"

using namespace std;

Fraction::Fraction(long top, long down) {
    this->top=top;
    this->down=down;
}

Fraction::Fraction(const Fraction& other) {
    this->top=other.top;
    this->down=other.down;
} 

void Fraction::show() const {
    cout << top << '/' << down << endl;
}
    
void Fraction::setValue(long top, long down) {
    this->top=top;
    this->down=down;
}

void Fraction::simplify() {
    long factor = gcf(top,down);
    top = top/factor;
    down = down/factor;
}

Fraction Fraction::add(const Fraction& other) const {
    long topLeft = other.down*this->top; 
    long topRight = other.top*this->down;
    long down = other.down*this->down;
    
    Fraction result(topLeft+topRight, down);
    result.simplify();
    return result;
}

Fraction Fraction::subtract(const Fraction& other) const {
    long topLeft = other.down*this->top; 
    long topRight = other.top*this->down;
    long down = other.down*this->down;
    
    Fraction result(topLeft-topRight, down);
    result.simplify();
    return result;
}

Fraction Fraction::multiply(const Fraction& other) const {
    
    Fraction result(other.top*this->top, other.down*this->down);
    result.simplify();
    return result;
}

Fraction Fraction::divide(const Fraction& other) const {
    
    Fraction result(other.down*this->top, other.top*this->down);
    result.simplify();
    return result;
}

long Fraction::gcf(long first, long second)
{
  if (first <0)first =- first;
  if (second<0)second=-second;
  cout << 'F' << ' ' << 'S' << endl;
  while (second)
  {
    int tmp=first % second;
    first=second;
    second=tmp;
    cout << first << ' ' << second << endl;
  }
  cout << endl;
  return first;
} 
