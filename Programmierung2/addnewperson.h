/*
  Name: Burenko Anton
  Matrikelnummer: 43733
  Studiengruppe: 17/041/01
*/
#ifndef ADDNEWPERSON_H
#define ADDNEWPERSON_H

#include <QDialog>
#include "person.h"
#include "mainwindow.h"

namespace Ui {
class AddNewPerson;
}

class AddNewPerson : public QDialog
{
    Q_OBJECT

public:
    void refeshMainList(); // TESTING
    explicit AddNewPerson(QWidget *parent = 0);
    ~AddNewPerson();

private slots:
    void on_completeButton_clicked();

    void on_cancelButton_clicked();

signals:
    void newPersonSignal(Person * newPerson);

private:
    Ui::AddNewPerson *ui;
    MainWindow *mainWindowUi;
    QLinkedList<Person> personList;
};

#endif // ADDNEWPERSON_H
