/*
  Name: Burenko Anton
  Matrikelnummer: 43733
  Studiengruppe: 17/041/01
*/
#ifndef DVD_H
#define DVD_H

#include "cd.h"

class DVD : public CD {
private:
    int videoQuality;
public:
    DVD (int id, QString initTitle, QString initAuthor,
         double initDuration, int initVideoQuality,
         int initYearPublished, int initLoanedById = 0);

    // getters
    QString getQuality() const;
    QString getTypeName() const;
    QString getClassSpecialInfo() const;

    // setters
    void setQuality(int newVideoQuality);

    //parser
    static bool parseObj(Medium *&p, QStringList &lineArguments);
};

#endif // DVD_H
