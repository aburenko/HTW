/*
  Name: Burenko Anton
  Matrikelnummer: 43733
  Studiengruppe: 17/041/01
*/
#include "ui_addnewperson.h"
#include <QMessageBox>
using namespace std;
#include "medium.h"
#include "addnewperson.h"

AddNewPerson::AddNewPerson(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddNewPerson)
{
    ui->setupUi(this);
}

AddNewPerson::~AddNewPerson()
{
    delete ui;
}

void AddNewPerson::on_completeButton_clicked()
{
    // get arguments
    QString name = ui->nameLineEdit->text();
    QString birthday = ui->birthdayEdit->text();
    // check of fields
    if(name.isEmpty() || birthday.isEmpty()) {
        QMessageBox::information(this,
            "can not continue", "please fill out all fields");
    }
    else {
        // parse birthday QString to int array
        int bDayArr [3];
        QStringList bDaySplit = birthday.split(QRegExp("(\\.)"));
        for(int i = 0; i < bDaySplit.size(); i++)
            bDayArr[i] = bDaySplit.at(i).toInt();
        // create new Person with this data and id 0
        Person *newPerson = new Person(name, bDayArr[0],
                bDayArr[1], bDayArr[2], 0);
        // emit pointer to this person
        emit newPersonSignal(newPerson);
        this->close();
    }
}

void AddNewPerson::on_cancelButton_clicked()
{
    this->close();
}
