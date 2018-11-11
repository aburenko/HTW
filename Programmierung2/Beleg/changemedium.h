/*
  Name: Burenko Anton
  Matrikelnummer: 43733
  Studiengruppe: 17/041/01
*/
#ifndef CHANGEMEDIUM_H
#define CHANGEMEDIUM_H

#include <QDialog>
#include <medium.h>

namespace Ui {
class ChangeMedium;
}

class ChangeMedium : public QDialog
{
    Q_OBJECT

public:
    explicit ChangeMedium(Medium *m,QWidget *parent = 0);
    ~ChangeMedium();

private slots:
    // cancel
    void on_pushButton_2_clicked();
    // submit
    void on_pushButton_clicked();

private:
    Ui::ChangeMedium *ui;
    // pointer to edited Medium
    Medium *currMedium;
    // its' type
    QString mType;
    // functions
    bool checkInput(); // true - input correct
    void saveInput(); // saves input in currMedium
};

#endif // CHANGEMEDIUM_H
