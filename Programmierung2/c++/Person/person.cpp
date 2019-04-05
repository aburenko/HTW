#include <iostream>
#include "date.hpp"
#include "person.hpp"

using namespace std;

Person::Person (string nameStr, int year, int month, int day) 
    : bornDate (year, month, day), name (nameStr)
{

}

void Person::show () 
{
   cout << name << endl;
   bornDate.show();
} 
