/*
  Name: Burenko Anton
  Matrikelnummer: 43733
  Studiengruppe: 17/041/01
*/
#ifndef ADDNEWMEDIUM_H
#define ADDNEWMEDIUM_H

#include <QDialog>

#include "medium.h"
#include "book.h"
#include "cd.h"
#include "dvd.h"

namespace Ui {
class AddNewMedium;
}

class AddNewMedium : public QDialog
{
    Q_OBJECT

public:
    explicit AddNewMedium(QWidget *parent = 0);
    ~AddNewMedium();

signals:
    // "signals" a pointer to new Medium
    void newMediumSignal(Medium * newMedium);
private slots:
    // slots for radio buttons
    void on_radioButtonCD_clicked();
    void on_radioButtonBook_clicked();
    void on_radioButtonDVD_clicked();
    // slot for add function
    void on_addButton_clicked();

    void on_cancelButton_clicked();

private:
    Ui::AddNewMedium *ui;
};

#endif // ADDNEWMEDIUM_H
