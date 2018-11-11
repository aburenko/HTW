/*
  Name: Burenko Anton
  Matrikelnummer: 43733
  Studiengruppe: 17/041/01
*/
#ifndef PERSON_H
#define PERSON_H

#include <QDate>
#include <QStringList>
#include "medium.h"

class Person
{
private:
    QString name;
    QDate birthday;
    int numberOfLoanedMedium;
    int id;
public:
    // constuctors --------
    // for id counter
    Person(int &idCounter, QString initName, int d, int m, int y,
           int initNumberOfLoanedMedium = 0);
    // for setting Person manually without a counter
    Person(QString initName, int d, int m, int y,
           const int initId,
           int initNumberOfLoanedMedium = 0);
    // getters ------------
    QString getName() const;
    QString getBirthday() const;
    QString getNumberOfLoanedMedium() const;
    QString getIdStr() const;
    QDate const& getBirthdayDF() const; // Date Format
    QString getDataInCSV() const; // convert members to one CSV QString
    int getId() const;
    // setters ------------
    void setId(int newId);
    void setName(QString newName);
    void setDate(QDate newDate);
    void addNumberOfLoanedMedium();
    void reduceNumberOfLoanedMedium();
    // static functions ---
    // creates new Person with lineArguments and sets pointer p to it
    static bool parseObj(Person *&p, QStringList &lineArguments);
};

#endif // PERSON_H
