/*
  Name: Burenko Anton
  Matrikelnummer: 43733
  Studiengruppe: 17/041/01
*/
#include<QString>
using namespace std;
#include "medium.h"

Medium::Medium (int id, QString initTitle, QString initAuthor,
                int initYearPublished,
                int initLoanedById)
{
    this->id = id;
    title = initTitle;
    author = initAuthor;
    yearPublished = initYearPublished;
    loanedById = initLoanedById;
}

bool Medium::isAvailable() const {
    // return availibility
    return loanedById > 0 ? true : false;
}

QString Medium::getTitle() const {
    return title;
}

QString Medium::getBasicInCSV() const {
    return title + ',' + author + ','
            + QString::number(yearPublished) + ','
            + QString::number(loanedById) + ',' + QString::number(id);
}

QString Medium::getDataInCSV() const {
    return getClassSpecialInfo() + ',' + getBasicInCSV() + '\n';
}

QString Medium::getAuthor() const {
    return author;
}

QString Medium::getLoanedById() const {
    return QString::number(loanedById);
}

QString Medium::getId() const {
    return QString::number(id);
}

QString Medium::getQuality() const {
    return "-";
}

QString Medium::getYear() const {
    return QString::number(yearPublished);
}

void Medium::setId(int newId) {
    id = newId;
}

void Medium::setLoanedById(int newId) {
    loanedById = newId;
}

void Medium::setTitle(QString newTitle) {
    title = newTitle;
}

void Medium::setAuthor(QString newAuthor) {
    author = newAuthor;
}

void Medium::setYear(int newYear) {
    yearPublished = newYear;
}
