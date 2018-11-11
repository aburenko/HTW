/*
  Name: Burenko Anton
  Matrikelnummer: 43733
  Studiengruppe: 17/041/01
*/
#include<QString>
#include<QStringList>
using namespace std;

#include "book.h"


Book::Book (int id, QString initTitle, QString initAuthor,
            int initPagesNumber, int initYearPublished,
            int initLoanedById)
    : Medium(id, initTitle, initAuthor,
             initYearPublished, initLoanedById)
{
   pagesNumber = initPagesNumber;
}

void Book::setPages (int newPagesNumber) {
    pagesNumber = newPagesNumber;
}

QString Book::getClassSpecialInfo() const {
    return QString("Book") + ','
            + QString::number(pagesNumber);

    /*  number \  variable
     * --------\-----------
     *    0    \  pagesNumber
     *    1    \   title
     *    2    \   author
     *    3    \ yearPublished
     *    4    \ loanedByID
     *    5    \    ID
     */
}

bool Book::parseObj(Medium *&p, QStringList &lineArguments) {
    // initializing variables for parameters
    int pagesNumber;
    QString title;
    QString author;
    int yearPublished;
    int loanedById;
    int id;
    // save arguments to variables
    for(int i = 0; i<lineArguments.size(); i++) {
        if      (i == 0) // pagesNumber(int)
            pagesNumber = lineArguments.at(i).toInt();
        else if (i == 1) // title(QString)
            title = lineArguments.at(i);
        else if (i == 2) // author(QString)
            author = lineArguments.at(i);
        else if (i == 3) // yearPublished(int)
            yearPublished = lineArguments.at(i).toInt();
        else if (i == 4) // loanedById(int)
            loanedById = lineArguments.at(i).toInt();
        else if (i == 5) // id(int)
            id = lineArguments.at(i).toInt();
        else
            return false;
    }
    // create Book with gotten parameters and point to it
    p = new Book(id, title, author, pagesNumber,
                 yearPublished, loanedById);
    return true;
}

QString Book::getDurOrPag() const {
    return QString::number(pagesNumber);
}

QString Book::getTypeName() const {
    return "Book";
}

void Book::setDurOrPag(double newValue) {
    pagesNumber = newValue;
}

void Book::setQuality(int) {

}
