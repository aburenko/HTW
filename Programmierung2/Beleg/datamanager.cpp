/*
  Name: Burenko Anton
  Matrikelnummer: 43733
  Studiengruppe: 17/041/01
*/
#include <QString>
#include <QLinkedList>
#include <QMessageBox>
#include <QStringList>
#include <QLineEdit>
#include <iostream>
#include <QtDebug>
#include <iterator>
#include <list>
using namespace std;
// DEFINES
#define FILE_MEDIUM_DIR "medium.csv"
#define FILE_PERSON_DIR "person.csv"
#define FILE_COUNTERS_DIR "counters.csv"
#define CHARACTERS_TO_READ 255
// HEADERS
#include "medium.h"
#include "person.h"
#include "datamanager.h"

DataManager::DataManager()
{
    // initialize start variables
    fileMedium.setFileName(FILE_MEDIUM_DIR);
    filePerson.setFileName(FILE_PERSON_DIR);
    fileCounters.setFileName(FILE_COUNTERS_DIR);
}

void DataManager::saveData(const QLinkedList<Medium *> &mediumList, const QLinkedList<Person *> &personList,
                           int personCounter, int mediumCounter) {
    // save mediumList ---------------------------------
    saveObject(mediumList);
    // save personList ---------------------------------
    saveObject(personList);
    saveCounters(personCounter, mediumCounter);
}

void DataManager::loadData(QLinkedList<Medium *> &mediumList, QLinkedList<Person *> &personList,
                           int &personCounter, int &mediumCounter) {
    // load mediumList ---------------------------------
    loadPersonData(personList);
    // load personList ---------------------------------
    loadMediumData(mediumList);
    loadCounters(personCounter, mediumCounter);
}

bool DataManager::loadCounters(int &personCounter, int &mediumCounter) {
    if(!fileCounters.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;
    // define separator
    QRegExp csvRegExp("(\\,|\\\n)");
    // set the textSteam to the File
    textStream.setDevice(&fileCounters);
    QString currentLine = textStream.readLine(CHARACTERS_TO_READ); // get first line
    // split values to Arguments
    QStringList lineArguments = currentLine.split(csvRegExp);
    // convert and set to variables
    personCounter = lineArguments.at(0).toInt();
    mediumCounter = lineArguments.at(1).toInt();
    // close file
    fileCounters.close();
    return true;
}

void DataManager::insertPersonSortedById(QLinkedList<Person *> &personList, Person &p) {
    if (personList.empty()) { // if List is empty
        personList.append(&p);
    }
    else {
        int tmpPersonId = p.getId(); // get current Person id
        QLinkedList<Person*>::iterator i = personList.begin(); // create iterator
        // compare with the first object
        if ((*i)->getId() > tmpPersonId) {
            personList.prepend(&p);
            return;
        }
        // compare with others elements of the list
        for (i++ ; i != personList.end(); ++i) {
            if ((*i)->getId() > tmpPersonId) {
                personList.insert(i,&p);
                return;
            }
        }
        // append if greater than all objects of the list
        personList.append(&p);
    }
}

bool DataManager::loadPersonData(QLinkedList<Person *> &personList) {
    // open the choosen file
    if(!filePerson.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;
    // define separators
    QRegExp csvRegExp("(\\,|\\\n)");
    // set the textSteam to the File
    textStream.setDevice(&filePerson);
    // clear list for new data
    personList.clear();
    // start reading from the file line by line
    QString currentLine = textStream.readLine(CHARACTERS_TO_READ); // get first line
    while(currentLine != NULL) {
        QStringList lineArguments = currentLine.split(csvRegExp);
        // create pointer and parse argument to it
        Person *newPerson = NULL;
        if(!Person::parseObj(newPerson, lineArguments))
            return false;
        // add this person to the personList
        personList.append(newPerson);
        //insertPersonSortedById(TList, *newPerson);
        currentLine = textStream.readLine(CHARACTERS_TO_READ); // get next line
    }
    // close file
    filePerson.close();
    return true;
}

bool DataManager::loadMediumData(QLinkedList<Medium *> &mediumList) {
    // open the choosen file
    if(!fileMedium.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;
    // define separators
    QRegExp csvRegExp("(\\,|\\\n)");
    // set the textSteam to the File
    textStream.setDevice(&fileMedium);
    // clear list for new data
    mediumList.clear();
    QString currentLine = textStream.readLine(CHARACTERS_TO_READ); // get first line
    while(currentLine != NULL) {
        QStringList lineArguments = currentLine.split(csvRegExp);
        // chose the scenario for Medium: Book | CD | DVD
        QString mediumType = lineArguments.at(0);
        // check if String is valid
        if(mediumType != "Book" && mediumType != "CD" && mediumType != "DVD") // QString allows using of !=
             return false;
        lineArguments.removeFirst(); // remove medium Type from String List
        // create pointer and parse argument to it
        Medium *newMedium= NULL;
        if      (mediumType == "Book")
            Book::parseObj(newMedium, lineArguments);
        else if (mediumType == "CD")
            CD::parseObj(newMedium, lineArguments);
        else if (mediumType == "DVD")
            DVD::parseObj(newMedium, lineArguments);
        // add this medium to the mediumList
        mediumList.append(newMedium);
        currentLine = textStream.readLine(CHARACTERS_TO_READ); // get next line
    }
    // close file
    fileMedium.close();
    return true;
}

bool DataManager::saveCounters (int personCounter, int mediumCounter) {
    if(!fileCounters.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;
    // set the textSteam to the File
    textStream.setDevice(&fileCounters);
    // write counters information to the textstream/file
    textStream << QString::number(personCounter) << ","
               << QString::number(mediumCounter);
    // clear and check the stream
    textStream.flush();
    if (textStream.status() != QTextStream::Ok)
        return false;
    // close file
    fileCounters.close();
    return true;
}

void DataManager::loadTableMedium(const QLinkedList<Medium *> &mList, QTableWidget *&mT) {
    // initialize variables for table
    int col = 0;
    int row = 0;
    mT->setRowCount(0);
    foreach(Medium * i, mList) {
        col = 0;
        // add new row for new Medium
        mT->insertRow(mT->rowCount());
        // load Type Name
        mT->setItem(row, col++, new QTableWidgetItem(i->getTypeName().trimmed()));
        // load id
        mT->setItem(row, col++, new QTableWidgetItem(i->getId().trimmed()));
        // load Title
        mT->setItem(row, col++, new QTableWidgetItem(i->getTitle().trimmed()));
        // load Author
        mT->setItem(row, col++, new QTableWidgetItem(i->getAuthor().trimmed()));
        // load Pages or Duration
        mT->setItem(row, col++, new QTableWidgetItem(i->getDurOrPag().trimmed()));
        // load Quality
        mT->setItem(row, col++, new QTableWidgetItem(i->getQuality().trimmed()));
        // load Year
        mT->setItem(row, col++, new QTableWidgetItem(i->getYear().trimmed()));
        // load loanedById
        mT->setItem(row, col++, new QTableWidgetItem(i->getLoanedById()));
        row++;
    }
}
void DataManager::loadTablePerson(QLinkedList<Person *> const &personList, QTableWidget *&personTable) {
    // initialize variables for table
    QLinkedList<Person*>::const_iterator i = personList.constBegin(); // create iterator
    int col = 0;
    int row = 0;
    personTable->setRowCount(0);
    for (; i != personList.constEnd(); ++i) {
        col = 0;
        personTable->insertRow(personTable->rowCount());
        // load id
        personTable->setItem(row, col++, new QTableWidgetItem((*i)->getIdStr().trimmed()));
        // load Name
        personTable->setItem(row, col++, new QTableWidgetItem((*i)->getName().trimmed()));
        // load Birthday
        personTable->setItem(row, col++, new QTableWidgetItem((*i)->getBirthday().trimmed()));
        // load number of loaned Medium
        personTable->setItem(row, col++, new QTableWidgetItem((*i)->getNumberOfLoanedMedium().trimmed()));
        row++;
    }
}

void DataManager::saveTable(QLinkedList<Person *> &personList, QTableWidget const *personTable) {
    personList.clear();
    QRegExp birthdayRegExp("(\\.)");
    int birthArr[3];
    int id, numberOfLoanedMedium, row;
    QString name;
    QTableWidgetItem * tmpCell;
    // convert all Strings to needed format
    for(row = 0; row < personTable->rowCount(); row++) {
        // get id
        tmpCell = personTable->item(row, 0);
        id = tmpCell->text().toInt();
        // get name
        tmpCell = personTable->item(row, 1);
        name = tmpCell->text();
        // get birthday
        tmpCell = personTable->item(row, 2);
          // separate values of birthday date in one List
        QStringList birthdaySepStr = tmpCell->text().split(birthdayRegExp);
        for(int j = 0; j < birthdaySepStr.size(); j++) { // save to int array
            birthArr[j] = birthdaySepStr.at(j).toInt();
        }
        // get numberOfLoanedMedium
        tmpCell = personTable->item(row, 3);
        numberOfLoanedMedium = tmpCell->text().toInt();
        // create Person with gotten parameters and push to Linked Listr
        Person * p = new Person(name, birthArr[0], birthArr[1],
                birthArr[2], id, numberOfLoanedMedium);
        personList.append(p);
    }
}

void DataManager::saveTable(QLinkedList<Medium *> &mediumList, QTableWidget const *mediumTable) {
    mediumList.clear();
    QString type, title, author, tmpCellStr;
    int id, quality, givenTo, year;
    double durOrPag; // Duration or Pages
    int row, col;
    Medium * tmpPtr;
    // convert all Strings to needed format
    for(row = 0; row < mediumTable->rowCount(); row++) {
        for(col = 0; col < mediumTable->columnCount(); col++) {
            tmpCellStr = mediumTable->item(row, col)->text(); // get current cell
            switch (col) {
            case 0:
                type = tmpCellStr;
                break;
            case 1:
                id = tmpCellStr.toInt();
                break;
            case 2:
                title = tmpCellStr;
                break;
            case 3:
                author = tmpCellStr;
                break;
            case 4:
                if(type == "Book")
                    durOrPag = tmpCellStr.toInt();
                else if(type == "CD" || type == "DVD")
                    durOrPag = tmpCellStr.toDouble();
                break;
            case 5:
                quality = tmpCellStr.toInt();
                break;
            case 6:
                year = tmpCellStr.toInt();
                break;
            case 7:
                givenTo = tmpCellStr.toInt();
                break;
            default:
                break;
            }
        }
        if(type == "Book")
            tmpPtr = new Book(id, title, author, (int)durOrPag, year, givenTo);
        else if(type == "CD")
            tmpPtr = new CD(id, title, author, durOrPag, year, givenTo);
        else
            tmpPtr = new DVD(id, title, author, durOrPag, quality, year, givenTo);
        mediumList.append(tmpPtr);
    }
}

void DataManager::connect(QLinkedList<Medium *> &mL, QLinkedList<Person *> &pL,
                          int mediumId, int personId)
{
    // search medium and set person id to it
    foreach(Medium *m, mL) {
        if(m->getId().toInt()==mediumId) {
            m->setLoanedById(personId);
            break;
        }
    }
    // search person and increase number of medium with one
    foreach(Person *p, pL) {
        if(p->getId()==personId) {
            p->addNumberOfLoanedMedium();
            break;
        }
    }
}

void DataManager::disconnect(QLinkedList<Medium *> &mL, QLinkedList<Person *> &pL,
                          int mediumId, int personId)
{
    // search medium and set zero to it
    foreach(Medium *m, mL) {
        if(m->getId().toInt()==mediumId) {
            m->setLoanedById(0);
            break;
        }
    }
    // search person and decrease number of medium with one
    foreach(Person *p, pL) {
        if(p->getId()==personId) {
            p->reduceNumberOfLoanedMedium();
            break;
        }
    }
}

void DataManager::searchTable(QTableWidget * table, QString key) {
    QList<QTableWidgetItem *> LTempTable = table->findItems(key, Qt::MatchContains);
    // mark items with color
    foreach(auto rowPtr,LTempTable)
    {
        rowPtr->setBackground(Qt::red);
    }
}

bool dateLessThan(const Person *p1, const Person *p2)
{
    // custom sort according to date
    return p1->getBirthdayDF() < p2->getBirthdayDF();
}

void DataManager::sortListBDate(QLinkedList<Person *> &personList) {
    // create and fill in temporare Qlist
    QList<Person *> tmpL;
    foreach (Person *p, personList) {
        tmpL.append(p);
    }
    // sort List with custom sort function
    sort(tmpL.begin(), tmpL.end(), dateLessThan);
    // fill sorted back into personList
    personList.clear();
    foreach (Person *p, tmpL) {
        personList.append(p);
    }
}
