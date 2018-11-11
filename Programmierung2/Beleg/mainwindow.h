/*
  Name: Burenko Anton
  Matrikelnummer: 43733
  Studiengruppe: 17/041/01
*/
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "person.h"
#include "datamanager.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    // adds new unit Person or Medium
    void addedNewPerson(Person *newPerson);
    void addedNewMedium(Medium * newMedium);
    // implement loaning a meidum by a person
    void giveMediumSlot(QString title, int mediumId, int personId, QString personName);

private slots:

    void on_actionPerson_triggered();

    void on_actionMedium_triggered();

    void on_deleteMediumButton_clicked();

    void on_deletePersonButton_clicked();

    void sectionClickedMedium(int i);

    void sectionClickedPerson(int i);

    void on_savePersonButton_clicked();

    void on_saveMediumButton_clicked();

    void on_actionRead_from_triggered();

    void on_actionWrite_to_triggered();

    void on_giveButton_clicked();

    void on_returnButton_clicked();

    void on_searchButton_clicked();

    void on_refreshButton_clicked();

private:
    // catch close event
    void closeEvent(QCloseEvent *event);
    // refresh tables on main window
    void refreshTables();

    Ui::MainWindow *ui;
    DataManager mainDataManager;
    QLinkedList<Medium*> mediumList;
    QLinkedList<Person*> personList;

    int personCounter;
    int mediumCounter;
};

#endif // MAINWINDOW_H
