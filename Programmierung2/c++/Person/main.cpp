#include<iostream>
#include "date.hpp"
#include "person.hpp"

using namespace std;

int main () 
{
    Date d1 (5,8,1998);
    d1.show();
    d1.updateDate(2,2,99);
    d1.show();
    //moving to Person
    Person p1("Valentin", 10, 10, 91);
    p1.show();
}
