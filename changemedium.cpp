/*
  Name: Burenko Anton
  Matrikelnummer: 43733
  Studiengruppe: 17/041/01
*/
#include "changemedium.h"
#include "ui_changemedium.h"
#include <QDebug>

ChangeMedium::ChangeMedium(Medium *m, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChangeMedium)
{
    ui->setupUi(this);
    // save pointer to Medium
    currMedium = m;
    mType = m->getTypeName();
    // fill data from medium into table
    ui->typeEdit    ->setText (m->getTypeName());
    ui->idEdit      ->setText (m->getId());
    ui->titleEdit   ->setText (m->getTitle());
    ui->AuthorEdit  ->setText (m->getAuthor());
    ui->durOrPagEdit->setValue(m->getDurOrPag().toDouble());
    ui->qualityEdit ->setValue(m->getQuality().toInt());
    ui->yearEdit    ->setValue(m->getYear().toInt());
    ui->givenToEdit ->setText (m->getLoanedById());
    // enable quality field
    if(mType == "DVD")
        ui->qualityEdit->setEnabled(true);
}

ChangeMedium::~ChangeMedium()
{
    delete ui;
}
// close
void ChangeMedium::on_pushButton_2_clicked()
{
    this->close();
}
//save
void ChangeMedium::on_pushButton_clicked()
{
    if (checkInput() == false)
        return;
    saveInput();
    this->close();
}

bool ChangeMedium::checkInput() {
    // if one of fields is empty
    if (ui->titleEdit->text()  == QString()
     || ui->AuthorEdit->text() == QString())
        return false;
    return true;
}

void ChangeMedium::saveInput() {
    // save input into current Medium
    currMedium->setTitle(ui->titleEdit->text());
    currMedium->setAuthor(ui->AuthorEdit->text());
    currMedium->setDurOrPag(ui->durOrPagEdit->value());
    QString quality = ui->qualityEdit->text();
    // check for empty input
    if(quality != "-")
        currMedium->setQuality(quality.toInt());
    currMedium->setYear(ui->yearEdit->text().toInt());
}
