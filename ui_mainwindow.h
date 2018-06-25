/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QTabWidget>
#include <QtGui/QTableWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionRead_from;
    QAction *actionWrite_to;
    QAction *actionPerson;
    QAction *actionMedium;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *horizontalLayout;
    QPushButton *refreshButton;
    QLineEdit *SearchLineEdit;
    QPushButton *searchButton;
    QTabWidget *tabWidget;
    QWidget *mediumTab;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QTableWidget *mediumTable;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *deleteMediumButton;
    QPushButton *saveMediumButton;
    QPushButton *giveButton;
    QPushButton *returnButton;
    QWidget *personTab;
    QVBoxLayout *verticalLayout_4;
    QVBoxLayout *verticalLayout_3;
    QTableWidget *personTable;
    QHBoxLayout *personButtonsLayout;
    QPushButton *deletePersonButton;
    QPushButton *savePersonButton;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menunew;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(712, 434);
        actionRead_from = new QAction(MainWindow);
        actionRead_from->setObjectName(QString::fromUtf8("actionRead_from"));
        actionWrite_to = new QAction(MainWindow);
        actionWrite_to->setObjectName(QString::fromUtf8("actionWrite_to"));
        actionPerson = new QAction(MainWindow);
        actionPerson->setObjectName(QString::fromUtf8("actionPerson"));
        actionMedium = new QAction(MainWindow);
        actionMedium->setObjectName(QString::fromUtf8("actionMedium"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout_6 = new QVBoxLayout(centralWidget);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        refreshButton = new QPushButton(centralWidget);
        refreshButton->setObjectName(QString::fromUtf8("refreshButton"));

        horizontalLayout->addWidget(refreshButton);

        SearchLineEdit = new QLineEdit(centralWidget);
        SearchLineEdit->setObjectName(QString::fromUtf8("SearchLineEdit"));
        SearchLineEdit->setMaxLength(50);

        horizontalLayout->addWidget(SearchLineEdit);

        searchButton = new QPushButton(centralWidget);
        searchButton->setObjectName(QString::fromUtf8("searchButton"));

        horizontalLayout->addWidget(searchButton);


        verticalLayout_6->addLayout(horizontalLayout);

        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        mediumTab = new QWidget();
        mediumTab->setObjectName(QString::fromUtf8("mediumTab"));
        verticalLayout_2 = new QVBoxLayout(mediumTab);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        mediumTable = new QTableWidget(mediumTab);
        if (mediumTable->columnCount() < 8)
            mediumTable->setColumnCount(8);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        mediumTable->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        mediumTable->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        mediumTable->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        mediumTable->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        mediumTable->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        mediumTable->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        mediumTable->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        mediumTable->setHorizontalHeaderItem(7, __qtablewidgetitem7);
        mediumTable->setObjectName(QString::fromUtf8("mediumTable"));
        mediumTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
        mediumTable->horizontalHeader()->setDefaultSectionSize(83);

        verticalLayout->addWidget(mediumTable);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        deleteMediumButton = new QPushButton(mediumTab);
        deleteMediumButton->setObjectName(QString::fromUtf8("deleteMediumButton"));

        horizontalLayout_2->addWidget(deleteMediumButton);

        saveMediumButton = new QPushButton(mediumTab);
        saveMediumButton->setObjectName(QString::fromUtf8("saveMediumButton"));

        horizontalLayout_2->addWidget(saveMediumButton);

        giveButton = new QPushButton(mediumTab);
        giveButton->setObjectName(QString::fromUtf8("giveButton"));

        horizontalLayout_2->addWidget(giveButton);

        returnButton = new QPushButton(mediumTab);
        returnButton->setObjectName(QString::fromUtf8("returnButton"));

        horizontalLayout_2->addWidget(returnButton);


        verticalLayout->addLayout(horizontalLayout_2);


        verticalLayout_2->addLayout(verticalLayout);

        tabWidget->addTab(mediumTab, QString());
        personTab = new QWidget();
        personTab->setObjectName(QString::fromUtf8("personTab"));
        verticalLayout_4 = new QVBoxLayout(personTab);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        personTable = new QTableWidget(personTab);
        if (personTable->columnCount() < 4)
            personTable->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        personTable->setHorizontalHeaderItem(0, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        personTable->setHorizontalHeaderItem(1, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        personTable->setHorizontalHeaderItem(2, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        personTable->setHorizontalHeaderItem(3, __qtablewidgetitem11);
        personTable->setObjectName(QString::fromUtf8("personTable"));
        personTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
        personTable->setRowCount(0);
        personTable->horizontalHeader()->setDefaultSectionSize(100);

        verticalLayout_3->addWidget(personTable);

        personButtonsLayout = new QHBoxLayout();
        personButtonsLayout->setSpacing(6);
        personButtonsLayout->setObjectName(QString::fromUtf8("personButtonsLayout"));
        deletePersonButton = new QPushButton(personTab);
        deletePersonButton->setObjectName(QString::fromUtf8("deletePersonButton"));

        personButtonsLayout->addWidget(deletePersonButton);

        savePersonButton = new QPushButton(personTab);
        savePersonButton->setObjectName(QString::fromUtf8("savePersonButton"));

        personButtonsLayout->addWidget(savePersonButton);


        verticalLayout_3->addLayout(personButtonsLayout);


        verticalLayout_4->addLayout(verticalLayout_3);

        tabWidget->addTab(personTab, QString());

        verticalLayout_6->addWidget(tabWidget);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 712, 30));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menunew = new QMenu(menuBar);
        menunew->setObjectName(QString::fromUtf8("menunew"));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menunew->menuAction());
        menuFile->addAction(actionRead_from);
        menuFile->addAction(actionWrite_to);
        menunew->addAction(actionPerson);
        menunew->addSeparator();
        menunew->addAction(actionMedium);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        actionRead_from->setText(QApplication::translate("MainWindow", "&Read from", 0, QApplication::UnicodeUTF8));
        actionWrite_to->setText(QApplication::translate("MainWindow", "&Write to", 0, QApplication::UnicodeUTF8));
        actionPerson->setText(QApplication::translate("MainWindow", "&Person", 0, QApplication::UnicodeUTF8));
        actionMedium->setText(QApplication::translate("MainWindow", "&Medium", 0, QApplication::UnicodeUTF8));
        refreshButton->setText(QApplication::translate("MainWindow", "refresh", 0, QApplication::UnicodeUTF8));
        searchButton->setText(QApplication::translate("MainWindow", "search", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem = mediumTable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("MainWindow", "type", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem1 = mediumTable->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("MainWindow", "id", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem2 = mediumTable->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("MainWindow", "title", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem3 = mediumTable->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("MainWindow", "author", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem4 = mediumTable->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QApplication::translate("MainWindow", "duration / pages", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem5 = mediumTable->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QApplication::translate("MainWindow", "quality", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem6 = mediumTable->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QApplication::translate("MainWindow", "year", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem7 = mediumTable->horizontalHeaderItem(7);
        ___qtablewidgetitem7->setText(QApplication::translate("MainWindow", "given to", 0, QApplication::UnicodeUTF8));
        deleteMediumButton->setText(QApplication::translate("MainWindow", "delete selected", 0, QApplication::UnicodeUTF8));
        saveMediumButton->setText(QApplication::translate("MainWindow", "change selected", 0, QApplication::UnicodeUTF8));
        giveButton->setText(QApplication::translate("MainWindow", "give selected to ...", 0, QApplication::UnicodeUTF8));
        returnButton->setText(QApplication::translate("MainWindow", "return selected", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(mediumTab), QApplication::translate("MainWindow", "medium", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem8 = personTable->horizontalHeaderItem(0);
        ___qtablewidgetitem8->setText(QApplication::translate("MainWindow", "id", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem9 = personTable->horizontalHeaderItem(1);
        ___qtablewidgetitem9->setText(QApplication::translate("MainWindow", "name", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem10 = personTable->horizontalHeaderItem(2);
        ___qtablewidgetitem10->setText(QApplication::translate("MainWindow", "birthday", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem11 = personTable->horizontalHeaderItem(3);
        ___qtablewidgetitem11->setText(QApplication::translate("MainWindow", "medium", 0, QApplication::UnicodeUTF8));
        deletePersonButton->setText(QApplication::translate("MainWindow", "delete selected", 0, QApplication::UnicodeUTF8));
        savePersonButton->setText(QApplication::translate("MainWindow", "change selected", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(personTab), QApplication::translate("MainWindow", "person", 0, QApplication::UnicodeUTF8));
        menuFile->setTitle(QApplication::translate("MainWindow", "fi&le", 0, QApplication::UnicodeUTF8));
        menunew->setTitle(QApplication::translate("MainWindow", "add &new...", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
