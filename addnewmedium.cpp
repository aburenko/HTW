/*
  Name: Burenko Anton
  Matrikelnummer: 43733
  Studiengruppe: 17/041/01
*/
#include "addnewmedium.h"
#include "ui_addnewmedium.h"

#include <QMessageBox>
#include <QDebug>

AddNewMedium::AddNewMedium(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddNewMedium)
{
    ui->setupUi(this);
}

AddNewMedium::~AddNewMedium()
{
    delete ui;
}

void AddNewMedium::on_radioButtonBook_clicked()
{
    // set availible parameters to Book
    ui->durationEdit->setEnabled(false);
    ui->qualityEdit->setEnabled(false);
    ui->pagesEdit   ->setEnabled(true);
}

void AddNewMedium::on_radioButtonCD_clicked()
{
    // set availible parameters to CD
    ui->durationEdit->setEnabled(true);
    ui->qualityEdit ->setEnabled(false);
    ui->pagesEdit   ->setEnabled(false);
}


void AddNewMedium::on_radioButtonDVD_clicked()
{
    // set availible parameters to DVD
    ui->durationEdit->setEnabled(true);
    ui->qualityEdit ->setEnabled(true);
    ui->pagesEdit   ->setEnabled(false);
}

void AddNewMedium::on_addButton_clicked()
{
    // get basic medium variables
    QString title  = ui->titleEdit->text().trimmed();
    QString author = ui->authorEdit->text().trimmed();
    int year   = ui->yearEdit->text().toInt();
    // check if fields are fulfilled
    if (title.isEmpty() || author.isEmpty()) {
        QMessageBox::information(this, "can not continue", "please fill out all fields");
        return;
    }
    // create  a pointer to new Medium
    Medium * newMedium;
    // check if Book is checked
    if (ui->radioButtonBook->isChecked()) {
        // get specific variables for book
        int pages = ui->pagesEdit->text().toInt();
        //create and emit new Book
        newMedium = new Book (0, title, author, pages, year);
    }
    else {
        // if not book that we initializing duration for CD or DVD
        double duration = ui->durationEdit->value();
        if (ui->radioButtonCD->isChecked()) {
            // creat
            newMedium = new CD(0, title, author, duration, year);
        }
        else { // if not book and not CD then DVD
            // get quality for DVD
            int quality  = ui->qualityEdit ->text().toInt();
            newMedium = new DVD(0, title, author, duration, quality, year);
        }
    }
    // emit signal with new Medium
    emit newMediumSignal(newMedium);
    this->close();
}

void AddNewMedium::on_cancelButton_clicked()
{
    this->close();
}
