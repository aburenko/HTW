/*
  Name: Burenko Anton
  Matrikelnummer: 43733
  Studiengruppe: 17/041/01
*/
#include<QDebug>
#include<QString>
#include<QStringList>
using namespace std;
#include "cd.h"

CD::CD (int id, QString initTitle, QString initAuthor,
        double initDuration, int initYearPublished,
        int initLoanedById)
    : Medium(id, initTitle, initAuthor,
             initYearPublished, initLoanedById)
{
   duration = initDuration;
}

QString CD::getDurationString() const {
    return  QString::number(duration)   ;
}

void CD::setDuration (int newDuration) {
    duration = newDuration;
}

QString CD::getClassSpecialInfo() const {
    return QString("CD") + ',' + getDurationString();

    /*  number \  variable
     * --------\-----------
     *    0    \  duration
     *    1    \   title
     *    2    \   author
     *    3    \ yearPublished
     *    4    \ loanedByID
     *    5    \     id
     */

}

bool CD::parseObj(Medium *&p, QStringList &lineArguments) {
    double duration;
    QString title;
    QString author;
    int yearPublished;
    int loanedById;
    int id;
    // create Book with gotten parameters and point to it
    for(int i = 0; i<lineArguments.size(); i++) {
        if      (i == 0) // duration(double)
            duration = lineArguments.at(i).toDouble();
        else if (i == 1) // title(QString)
            title = lineArguments.at(i);
        else if (i == 2) // author(QString)
            author = lineArguments.at(i);
        else if (i == 3) // yearPublished(int)
            yearPublished = lineArguments.at(i).toInt();
        else if (i == 4) // loanedById(int)
            loanedById = lineArguments.at(i).toInt();
        else if (i == 5) {// id(int)
            id = lineArguments.at(i).toInt();
        }
        else
            return false;
    }
    // create new CD with variables
    p = new CD(id, title, author, duration, yearPublished,
               loanedById);
    return true;
}

QString CD::getDurOrPag() const {
    return QString::number(duration);
}

QString CD::getTypeName() const {
    return "CD";
}

void CD::setDurOrPag(double newValue) {
    duration = newValue;
}

void CD::setQuality(int) {

}
