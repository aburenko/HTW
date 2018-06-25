/*
  Name: Burenko Anton
  Matrikelnummer: 43733
  Studiengruppe: 17/041/01
*/
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "addnewperson.h"
#include "addnewmedium.h"
#include "givemedium.h"
#include "changemedium.h"
#include "changeperson.h"
#include <QTableWidget>
#include <QStringList>
#include <QMessageBox>
#include <QCloseEvent>

#include "medium.h"
#include "book.h"
#include "cd.h"
#include "dvd.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    // initialize variables
    personCounter = mediumCounter = 0;
    // load data from DB
    mainDataManager.loadData(mediumList, personList, personCounter, mediumCounter);
    // setup this window
    ui->setupUi(this);
    connect(ui->mediumTable->horizontalHeader(), SIGNAL(sectionClicked(int)),
            SLOT(sectionClickedMedium(int)));
    connect(ui->personTable->horizontalHeader(), SIGNAL(sectionClicked(int)),
            SLOT(sectionClickedPerson(int)));
    // fill data in tables
    mainDataManager.loadTablePerson(personList, ui->personTable);
    mainDataManager.loadTableMedium(mediumList, ui->mediumTable);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionPerson_triggered()
{
    // show new window
    AddNewPerson window;
    // connect add functions
    connect(&window, SIGNAL(newPersonSignal(Person *)),
            this, SLOT(addedNewPerson(Person *)) );
    window.setModal(true);
    window.exec();
}

void MainWindow::on_actionMedium_triggered()
{
    // show new window
    AddNewMedium window;
    // connect add functions
    connect(&window, SIGNAL(newMediumSignal(Medium *)),
            this, SLOT(addedNewMedium(Medium *)) );
    window.setModal(true);
    window.exec();
}

void MainWindow::giveMediumSlot(QString title, int mediumId, int personId, QString personName) {
    // give medium with mediumId to person with personId
    mainDataManager.connect(mediumList, personList, mediumId, personId);
    // refresh tables
    refreshTables();
    // show into statuis bar
    ui->statusBar->showMessage(title + " was taken by "
                               + personName);
}

void MainWindow::addedNewPerson(Person * newPerson) {
    // set id to person according to personCounter
    newPerson->setId(++personCounter);
    // append Person to the List
    personList.append(newPerson);
    // show the action to the status bar
    ui->statusBar->showMessage(newPerson->getName() + " added.");
    // refresh table
    mainDataManager.loadTablePerson(personList, ui->personTable);
}

void MainWindow::addedNewMedium(Medium * newMedium) {
    // set id to medium according to mediumCounter
    newMedium->setId(++mediumCounter);
    // append Medium to the List
    mediumList.append(newMedium);
    // show the action to the status bar
    ui->statusBar->showMessage(newMedium->getTitle() + " added.");
    // refresh table
    mainDataManager.loadTableMedium(mediumList, ui->mediumTable);
}

void MainWindow::on_deleteMediumButton_clicked()
{
    // get row to delete
    int row = ui->mediumTable->currentRow();

    //checks
    // check for empty table
    if(row == -1) return;
    // check if loaned by someone
    if(ui->mediumTable->item(row,7)->text().toInt() != 0) {
        QMessageBox::warning(this, "can not continue",
                             "this medium is already given to someone, please return book than delete it");
        return;
    }

    // get Id Cell and its value in String
    QTableWidgetItem * idCell = ui->mediumTable->item(row, 1);
    QString id = idCell->text();
    // find this element and delete it
    foreach (Medium * iter, mediumList) {
        if(iter->getId() == id) {
            mediumList.removeOne(iter);
            break;
        }
    }
    // show in statusbar
    ui->statusBar->showMessage("medium " + id + " deleted");
    // refresh table
    mainDataManager.loadTableMedium(mediumList, ui->mediumTable);
}

void MainWindow::on_deletePersonButton_clicked()
{
    // get row to delete
    int row = ui->personTable->currentRow();
    // check for empty table
    if(row == -1) return;
    // check if this person has loaned medium
    int numberLoanedMedium = ui->personTable->item(row, 3)->text().toInt();
    if(numberLoanedMedium > 0) {
        QMessageBox::warning(this, "can not continue",
                             "this person has loaned medium. Please give all book back, and than delete this person!");
        return;
    }
    // get Id Cell and its value in String
    QTableWidgetItem * idCell = ui->personTable->item(row, 0);
    QString id = idCell->text();
    // find this element and delete it
    foreach (Person * iter, personList) {
        if(iter->getIdStr() == id) {
            personList.removeOne(iter);
            break;
        }
    }
    // show in statusbar
    ui->statusBar->showMessage("person " + id + " deleted");
    // refresh table
    mainDataManager.loadTablePerson(personList, ui->personTable);

}

void MainWindow::sectionClickedMedium(int i)
{
    // sort by column that was clicked
    ui->mediumTable->sortByColumn(i);

    mainDataManager.saveTable(mediumList, ui->mediumTable);
}

void MainWindow::sectionClickedPerson(int i)
{
    // sort by column that was clicked
    // custom sort by birthday i=2
    if ( i == 2) {
        mainDataManager.sortListBDate(personList);
        mainDataManager.loadTablePerson(personList, ui->personTable);
    }
    // else std sort
    else {
        ui->personTable->sortByColumn(i);
        mainDataManager.saveTable(personList, ui->personTable);
    }
}


void MainWindow::on_savePersonButton_clicked()
{
    // get row to change
    int row = ui->personTable->currentRow();
    // check for empty table
    if(row == -1) return;

    // get Id Cell and its value in String
    QString id = ui->personTable->item(row, 0)->text();
    Person *personPtr;
    // get pointer on Medium with id
    foreach (Person * pPtrTmp, personList) {
        if(pPtrTmp->getIdStr() == id) {
            personPtr = pPtrTmp;
            break;
        }
    }

    // open new window
    ChangePerson window(personPtr);
    window.setModal(true);
    window.exec();
    // refresh
    refreshTables();
}

void MainWindow::on_saveMediumButton_clicked()
{
    // get row to change
    int row = ui->mediumTable->currentRow();
    // check for empty table
    if(row == -1) return;

    // get Id Cell and its value in String
    QString id = ui->mediumTable->item(row, 1)->text();
    Medium *mediumPtr;
    // get pointer on Medium with id
    foreach (Medium * mPtrTmp, mediumList) {
        if(mPtrTmp->getId() == id) {
            mediumPtr = mPtrTmp;
            break;
        }
    }

    // open new window
    ChangeMedium window(mediumPtr);
    window.setModal(true);
    window.exec();
    // refresh
    refreshTables();
}

void MainWindow::on_actionRead_from_triggered()
{
    mainDataManager.loadData(mediumList, personList, personCounter, mediumCounter);
    // refresh table
    refreshTables();
    // show in statusbar
    ui->statusBar->showMessage("readed from DB");
}

void MainWindow::on_actionWrite_to_triggered()
{
    // refresh Linked List from Table
    mainDataManager.saveTable(personList, ui->personTable);
    mainDataManager.saveTable(mediumList, ui->mediumTable);
    // save into files
    mainDataManager.saveData(mediumList, personList,
                             personCounter, mediumCounter);
    // refresh table
    refreshTables();
    // show in statusbar
    ui->statusBar->showMessage("written to DB");
}

void MainWindow::on_giveButton_clicked()
{
    // get row of medium
    int row = ui->mediumTable->currentRow();
    // check for empty table of medium
    if(row == -1) {
        QMessageBox::information(this, "can not continue",
                                 "please select an item");
        return;
    }
    // if no person in person list
    if(personList.empty()) {
        QMessageBox::information(this, "can not continue",
                                 "there is no person found, please add person to continue");
        return;
    }
    // check if book is already given to someone
    if(ui->mediumTable->item(row,7)->text().toInt() != 0) {
        QMessageBox::information(this, "can not continue",
                                 "this medium is already given to someone");
        return;
    }
    QString title = ui->mediumTable->item(row,2)->text();
    int id = ui->mediumTable->item(row,1)->text().toInt();
    // show window to choose person
    GiveMedium window(title, id, personList, this);
    connect(&window, SIGNAL(sig_giveMedium(QString,int,int,QString)),
            this, SLOT(giveMediumSlot(QString,int,int,QString)) );
    window.setModal(true);
    window.exec();
}

void MainWindow::on_returnButton_clicked()
{
    // get row of medium
    int row = ui->mediumTable->currentRow();
    // check for empty table
    if(row == -1) {
        QMessageBox::information(this, "can not continue",
                                 "please select an item");
        return;
    }
    // check if book is already given to someone
    // if not yet given return.
    int mediumId = ui->mediumTable->item(row,1)->text().toInt();
    int givenToId = ui->mediumTable->item(row,7)->text().toInt();
    if(givenToId == 0) {
        QMessageBox::information(this, "can not continue",
                                 "this medium is free, can't return");
        return;
    }
    mainDataManager.disconnect(mediumList, personList, mediumId, givenToId);
    // show in statusbar
    ui->statusBar->showMessage("medium " + QString::number(mediumId) + " was gived back");
    // refresh tables
    refreshTables();
}

void MainWindow::refreshTables() {
    // refresh tables
    mainDataManager.loadTablePerson(personList, ui->personTable);
    mainDataManager.loadTableMedium(mediumList, ui->mediumTable);
}

void MainWindow::on_searchButton_clicked()
{
    // get input to search
    QString tabName = ui->tabWidget->currentWidget()->objectName();
    QString key = ui->SearchLineEdit->text();
    bool isPersonTable = tabName == "personTab";
    QTableWidget * tmpTable;
    // choose a table according to opened tab
    if      ( isPersonTable)
        tmpTable = ui->personTable;
    else if (!isPersonTable)
        tmpTable = ui->mediumTable;
    // search with key
    mainDataManager.searchTable(tmpTable, key);
}

void MainWindow::on_refreshButton_clicked()
{
    refreshTables();
    // show in statusbar
    ui->statusBar->showMessage("refreshed");
}

void MainWindow::closeEvent (QCloseEvent *event)
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Quit?","Are you sure you saved all your data",
                                  QMessageBox::Yes|QMessageBox::No);
    if (reply != QMessageBox::Yes) {
        event->ignore();
    } else {
        event->accept();
    }
}
