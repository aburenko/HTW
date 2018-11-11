/*
  Name: Burenko Anton
  Matrikelnummer: 43733
  Studiengruppe: 17/041/01
*/
#include <QString>
#include<QStringList>
using namespace std;
#include "dvd.h"

DVD::DVD (int id, QString initTitle, QString initAuthor, double initDuration,
          int initVideoQuality, int initYearPublished, int initLoanedById)
      : CD(id, initTitle, initAuthor,
           initDuration, initYearPublished,
           initLoanedById)
{
   videoQuality = initVideoQuality;
}

QString DVD::getClassSpecialInfo() const {
    return QString("DVD") + ',' + getDurationString()
            + ',' + QString::number(videoQuality);

    /*  number \  variable
     * --------\-----------
     *    0    \  duration
     *    1    \  quality
     *    2    \   title
     *    3    \   author
     *    4    \ yearPublished
     *    5    \ loanedByID
     *    6    \    ID
     */
}

bool DVD::parseObj(Medium *&p, QStringList &lineArguments) {
    int quality;
    double duration;
    QString title;
    QString author;
    int yearPublished;
    int loanedById;
    int id;
    // save parameters into variables
    for(int i = 0; i<lineArguments.size(); i++) {
        if      (i == 0) // duration(double)
            duration = lineArguments.at(i).toDouble();
        else if (i == 1) // quality(int)
            quality = lineArguments.at(i).toInt();
        else if (i == 2) // title(QString)
            title = lineArguments.at(i);
        else if (i == 3) // author(QString)
            author = lineArguments.at(i);
        else if (i == 4) // yearPublished(int)
            yearPublished = lineArguments.at(i).toInt();
        else if (i == 5) // loanedById(int)
            loanedById = lineArguments.at(i).toInt();
        else if (i == 6) // id(int)
            id = lineArguments.at(i).toInt();
        else
            return false;
    }
    // create a pointer on new DVD with given parameters
    p = new DVD(id, title, author, duration, quality,
                yearPublished, loanedById);
    return true;
}

QString DVD::getQuality() const {
    return QString::number(videoQuality);
}


QString DVD::getTypeName() const {
    return "DVD";
}

void DVD::setQuality(int newQuality) {
    videoQuality = newQuality;
}
