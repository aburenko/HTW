/*
  Name: Burenko Anton
  Matrikelnummer: 43733
  Studiengruppe: 17/041/01
*/
#ifndef BOOK_H
#define BOOK_H

#include "medium.h"

class Book : public Medium {
private:
    int pagesNumber;
public:
    Book (int id, QString initTitle, QString initAuthor,
          int initPagesNumber, int initYearPublished,
          int initLoanedById = 0);
    ~Book() {}

    // getters
    QString getDurOrPag() const;
    QString getTypeName() const;
    QString getClassSpecialInfo() const;

    // setters
    void setQuality(int);
    void setPages (int newPagesNumber);
    void setDurOrPag(double newValue);

    // parser
    static bool parseObj(Medium *&p, QStringList &lineArguments);
};

#endif // BOOK_H
