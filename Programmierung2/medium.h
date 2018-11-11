/*
  Name: Burenko Anton
  Matrikelnummer: 43733
  Studiengruppe: 17/041/01
*/
#ifndef MEDIUM_HPP
#define MEDIUM_HPP
#include <QString>
#include <QLinkedList>
// basic class
class Medium {
private:
    int id;
    QString title;
    QString author;
    int yearPublished;
    int loanedById;
public:
    Medium() {}
    Medium (int id, QString initTitle, QString initAuthor,
            int initYearPublished,
            int initLoanedById = 0);

    // getter functions
    // gets single parameter
    bool isAvailable() const;
    QString getTitle() const;
    QString getAuthor() const;
    QString getId() const;
    QString getLoanedById() const;
    QString getYear() const;
    virtual QString getQuality() const;
    virtual QString getTypeName() const = 0;
    virtual QString getDurOrPag() const = 0; // get Duration or Pages
    virtual QString getClassSpecialInfo() const = 0;
    // get String in CSV format
    QString getBasicInCSV() const;
    QString getDataInCSV() const;
    // setter functions
    void setId(int newId);
    void setTitle(QString newTitle);
    void setAuthor(QString newAuthor);
    void setYear(int newYear);
    void setLoanedById(int newId);
    virtual void setQuality(int newQuality) = 0;
    virtual void setDurOrPag(double newValue) = 0;
};

#endif // MEDIUM_HPP
