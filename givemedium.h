/*
  Name: Burenko Anton
  Matrikelnummer: 43733
  Studiengruppe: 17/041/01
*/
#ifndef GIVEMEDIUM_H
#define GIVEMEDIUM_H

#include <QDialog>
#include <QListWidgetItem>
#include "person.h"

namespace Ui {
class GiveMedium;
}

class GiveMedium : public QDialog
{
    Q_OBJECT

public:
    explicit GiveMedium(QString initTitle, int initMediumId,
                        const QLinkedList<Person *> &pL,
                        QWidget *parent = 0);
    ~GiveMedium();

signals:
    void sig_giveMedium(QString title, int mediumId, int PersonId, QString personName);

private slots:
    void on_personList_itemDoubleClicked(QListWidgetItem *item);

    void on_cancel_clicked();

private:
    int mediumId;
    QString title;
    Ui::GiveMedium *ui;
    QLinkedList<Person *> personList;
};

#endif // GIVEMEDIUM_H
