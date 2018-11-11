/*
  Name: Burenko Anton
  Matrikelnummer: 43733
  Studiengruppe: 17/041/01
*/
#ifndef CD_H
#define CD_H

#include "medium.h"

class CD : public Medium {
private:
    double duration;
public:
    CD (int id, QString initTitle, QString initAuthor,
        double initDuration, int initYearPublished,
        int initLoanedById = 0);

    // getters
    QString getDurationString() const;
    QString getDurOrPag() const;
    QString getTypeName() const;
    QString getClassSpecialInfo() const;

    // setters
    void setQuality(int);
    void setDuration (int newDuration);
    void setDurOrPag(double newValue);

    //parser
    static bool parseObj(Medium *&p, QStringList &lineArguments);
};

#endif // CD_H
