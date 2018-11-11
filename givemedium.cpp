/*
  Name: Burenko Anton
  Matrikelnummer: 43733
  Studiengruppe: 17/041/01
*/
#include <QLinkedList>
#include <QStringList>
#include <QDebug>

using namespace std;

#include "givemedium.h"
#include "ui_givemedium.h"

GiveMedium::GiveMedium(QString initTitle, int initMediumId,
                       const QLinkedList<Person *> &pL,
                       QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GiveMedium)
{
    ui->setupUi(this);
    // intitialize start variables
    title = initTitle;
    mediumId = initMediumId;
    foreach (Person * item, pL) {
        ui->personList->addItem(item->getIdStr() + ": " + item->getName());
    }
}

GiveMedium::~GiveMedium()
{
    delete ui;
}

void GiveMedium::on_personList_itemDoubleClicked(QListWidgetItem *item)
{
    // if double clicked then selected
    // get id of selected person
    QStringList strItem = item->text().split(QRegExp("(\\: |\\\n)"));
    int personId = strItem.at(0).toInt();
    QString personName = strItem.at(1);
    // emit selected person id
    emit sig_giveMedium(title, mediumId, personId, personName);
    this->close();
}

void GiveMedium::on_cancel_clicked()
{
    this->close();
}
