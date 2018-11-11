/*
  Name: Burenko Anton
  Matrikelnummer: 43733
  Studiengruppe: 17/041/01
*/
#include "changeperson.h"
#include "ui_changeperson.h"

ChangePerson::ChangePerson(Person * personPtr,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChangePerson)
{
    ui->setupUi(this);
    currPerson = personPtr;
    // load data into Table
    ui->idEdit    ->setText(currPerson->getIdStr());
    ui->nameEdit  ->setText(currPerson->getName());
    ui->dateEdit  ->setDate(currPerson->getBirthdayDF());
    ui->numberEdit->setText(currPerson->getNumberOfLoanedMedium());
}

ChangePerson::~ChangePerson()
{
    delete ui;
}

void ChangePerson::on_cancelButton_clicked()
{
    this->close();
}

void ChangePerson::on_saveButton_clicked()
{
    if (checkInput() == false)
        return;
    saveInput();
    this->close();
}

bool ChangePerson::checkInput() {
    // if field is empty
    if (ui->nameEdit->text() == QString())
        return false;
    return true;
}

void ChangePerson::saveInput() {
    // save into current Person
    currPerson->setDate(ui->dateEdit->date());
    currPerson->setName(ui->nameEdit->text());
}

