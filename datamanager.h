/*
  Name: Burenko Anton
  Matrikelnummer: 43733
  Studiengruppe: 17/041/01
*/
#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QFile>
#include <QTableWidget>
#include <QRegExp>
#include <QTextStream>
#include <QStringList>
#include <iterator>
#include <QDebug>
#include <typeinfo>
#include <iostream>
#include "person.h"
#include "book.h"
#include "cd.h"
#include "dvd.h"

class DataManager
{
private:
    QFile fileMedium;
    QFile filePerson;
    QFile fileCounters;
    QTextStream textStream;

    // template to save an QLinkedList to DB
    template <class T>
    bool saveObject(const QLinkedList<T> &TList);

    // filling infos into QLinkedList from DB
    bool loadPersonData(QLinkedList<Person *> &personList);
    bool loadMediumData(QLinkedList<Medium *> &mediumList);
    bool loadCounters(int &personCounter, int &mediumCounter);

    // saves Counter to fileCounter
    bool saveCounters(int personCounter, int mediumCounter);

public:
    DataManager();
    // writes to files
    void saveData(const QLinkedList<Medium *> &mediumList, const QLinkedList<Person *> &personList,
                  int personCounter, int mediumCounter);

    // to load from file
    void loadData(QLinkedList<Medium*> &mediumList, QLinkedList<Person*> &personList,
                  int &personCounter, int &mediumCounter);

    // load data from Lists to Tables
    void loadTableMedium(const QLinkedList<Medium *> &mList, QTableWidget *&mT);
    void loadTablePerson(QLinkedList<Person *> const &personList, QTableWidget *&personTable);

    // get info from Tables and save in Linked List
    void saveTable(QLinkedList<Person *> &personList, QTableWidget const *personTable);
    void saveTable(QLinkedList<Medium *> &mediumList, QTableWidget const *mediumTable);

    // insert in Linked List alphabetically
    void insertPersonSortedById(QLinkedList<Person *> &personList, Person &p);

    // give medium with mediumId to person with personId
    void connect(QLinkedList<Medium *> &mL, QLinkedList<Person *> &pL,
                 int mediumId, int personId);

    // give medium back with mediumId to person with personId
    void disconnect(QLinkedList<Medium *> &mL, QLinkedList<Person *> &pL,
                 int mediumId, int personId);

    // search in table with the key
    void searchTable(QTableWidget * table, QString key);

    // sort
    void sortListBDate(QLinkedList<Person *> &personList);
};

// template function to save an object to DB
template <class T>
bool DataManager::saveObject(const QLinkedList<T> & TList) {
    QFile * pFile;
    // choose a file in case of class
    if (typeid(T) == typeid(Person*))
        pFile = &filePerson;
    else if (typeid(T) == typeid(Medium*))
        pFile = &fileMedium;
    else return false;
    // open the choosen file
    if(!pFile->open(QIODevice::WriteOnly | QIODevice::Text))
        return false;
    // set the textSteam to the File
    textStream.setDevice(pFile);
    // write each information to the textstream/file
    foreach (T item, TList)
        textStream << item->getDataInCSV();
    // clear and check the stream
    textStream.flush();
    if (textStream.status() != QTextStream::Ok)
        return false;
    // close file
    pFile->close();
    return true;
}

#endif // DATAMANAGER_H
