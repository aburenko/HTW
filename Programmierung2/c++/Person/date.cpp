#include <iostream>
#include <iomanip>
#include <cstring>
#include "date.hpp"

using namespace std;

Date::Date (unsigned int day, unsigned int month, unsigned int year) {
    if (year < 100) year +=1900;
    if (month > 12) month %= 13;
    if (day > 31) day %= 32;
    this->year = year;
    this->month = month;
    this->day = day;
}

void Date::show () const {
    if(day<10)cout<<'0';
    cout << day << ".";
    if(month<10)cout<< '0';
    cout << month << "." << year << endl;
}

void Date::updateDate(unsigned int day, unsigned int month, unsigned int year) {
    if (year < 100) year +=1900;
    if (month > 12) month %= 13;
    if (day > 31) day %= 32;
    this->year = year;
    this->month = month;
    this->day = day;
}
