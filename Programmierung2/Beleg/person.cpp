/*
  Name: Burenko Anton
  Matrikelnummer: 43733
  Studiengruppe: 17/041/01
*/
#include <QString>
#include <QLinkedList>
#include <QRegExp>
#include <QDebug>
using namespace std;
#include "medium.h"
#include "person.h"

Person::Person(int &idCounter, QString initName, int d, int m,
               int y, int initNumberOfLoanedMedium)
    : birthday(y, m, d)
{
    name = initName;
    numberOfLoanedMedium = initNumberOfLoanedMedium;
    id = ++idCounter;
}

Person::Person(QString initName, int d, int m, int y,
               const int initId,
               int initNumberOfLoanedMedium)
    : birthday(y, m, d)
{
    name = initName;
    numberOfLoanedMedium = initNumberOfLoanedMedium;
    id = initId;
}


QString Person::getName() const {
    return name;
}

QString Person::getIdStr() const {
    return QString::number(id);
}

int Person::getId() const {
    return id;
}

QString Person::getBirthday() const {
    return birthday.toString("dd.MM.yyyy");
}

QDate const& Person::getBirthdayDF() const {
    return birthday;
}

QString Person::getNumberOfLoanedMedium() const {
    return QString::number(numberOfLoanedMedium);
}

QString Person::getDataInCSV() const
{
    QString stringCSV;
    // combine members to one string in format CSV
    stringCSV = name + ',' + birthday.toString("dd.MM.yyyy")
                + ',' + QString::number(numberOfLoanedMedium)
                + ',' + QString::number(id) + '\n';

/*  number \  variable
 * --------\-----------
 *    0    \   name
 *    1    \ birthday
 *    2    \ numberOfLoanedMedium
 *    3    \   id
 */
    // give string in format of CSV back
    return stringCSV;
}

void Person::setId(int newId) {
    id = newId;
}

bool Person::parseObj(Person *&p, QStringList &lineArguments) {
    // initializing variables for parameters
    QRegExp birthdayRegExp("(\\.)");
    int birthArr[3];
    int id;
    int numberOfLoanedMedium;
    QString name;
    // convert all Strings to needed format
    // the numbers of argument is defined by CSV file
    // (Look table in the function "Person::getDataInCSV")
    for(int i = 0; i<lineArguments.size(); i++) {
        if      (i == 0) // name (QString)
            name = lineArguments.at(i);
        else if (i == 1) { // birthday(int dd,int mm,int yy)
            // separate values of birthday date in one List
            QStringList birthdaySepStr = lineArguments.at(i).split(birthdayRegExp);
            for(int j = 0; j < birthdaySepStr.size(); j++) { // save to int array
                birthArr[j] = birthdaySepStr.at(j).toInt();
            }
        }
        else if (i == 2)   //numberOfLoanedMedium (int)
            numberOfLoanedMedium = lineArguments.at(i).toInt();
        else if (i == 3)   // id (int)
            id = lineArguments.at(i).toInt();
        else
            return false;
    }
    // create Person with gotten parameters
    p = new Person(name, birthArr[0], birthArr[1], birthArr[2],
            id, numberOfLoanedMedium);
    return true;
}

void Person::addNumberOfLoanedMedium() {
    numberOfLoanedMedium++;
}

void Person::reduceNumberOfLoanedMedium() {
    numberOfLoanedMedium--;
}

void Person::setName(QString newName) {
    name = newName;
}

void Person::setDate(QDate newDate) {
    birthday = newDate;
}
