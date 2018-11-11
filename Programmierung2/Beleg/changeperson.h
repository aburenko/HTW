/*
  Name: Burenko Anton
  Matrikelnummer: 43733
  Studiengruppe: 17/041/01
*/
#ifndef CHANGEPERSON_H
#define CHANGEPERSON_H

#include <QDialog>
#include "person.h"

namespace Ui {
class ChangePerson;
}

class ChangePerson : public QDialog
{
    Q_OBJECT

public:
    explicit ChangePerson(Person * personPtr, QWidget *parent = 0);
    ~ChangePerson();

private slots:
    void on_cancelButton_clicked();

    void on_saveButton_clicked();

private:
    Ui::ChangePerson *ui;
    // pointer to edited Person
    Person *currPerson;
    // functions
    bool checkInput(); // true - input correct
    void saveInput(); // saves input in currMedium
};

#endif // CHANGEPERSON_H
