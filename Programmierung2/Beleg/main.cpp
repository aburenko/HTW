/*
  Name: Burenko Anton
  Matrikelnummer: 43733
  Studiengruppe: 17/041/01
*/
#include "mainwindow.h"
#include <QApplication>
#include <QString>
#include <QLinkedList>

using namespace std;

#include "medium.h"
#include "person.h"
#include "addnewperson.h"

int main(int argc, char *argv[])
{
    // show main window
    QApplication a(argc, argv);
    MainWindow w;
    w.show();


    return a.exec();
}
