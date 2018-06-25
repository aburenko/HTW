/********************************************************************************
** Form generated from reading UI file 'givemedium.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GIVEMEDIUM_H
#define UI_GIVEMEDIUM_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QListWidget>
#include <QtGui/QPushButton>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_GiveMedium
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QListWidget *personList;
    QPushButton *cancel;

    void setupUi(QDialog *GiveMedium)
    {
        if (GiveMedium->objectName().isEmpty())
            GiveMedium->setObjectName(QString::fromUtf8("GiveMedium"));
        GiveMedium->resize(382, 310);
        verticalLayout_2 = new QVBoxLayout(GiveMedium);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(GiveMedium);
        label->setObjectName(QString::fromUtf8("label"));
        label->setLineWidth(1);

        verticalLayout->addWidget(label);

        personList = new QListWidget(GiveMedium);
        personList->setObjectName(QString::fromUtf8("personList"));
        personList->setResizeMode(QListView::Adjust);

        verticalLayout->addWidget(personList);

        cancel = new QPushButton(GiveMedium);
        cancel->setObjectName(QString::fromUtf8("cancel"));

        verticalLayout->addWidget(cancel);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(GiveMedium);

        QMetaObject::connectSlotsByName(GiveMedium);
    } // setupUi

    void retranslateUi(QDialog *GiveMedium)
    {
        GiveMedium->setWindowTitle(QApplication::translate("GiveMedium", "Dialog", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("GiveMedium", "<html><head/><body><p><span style=\" font-size:10pt; font-weight:600;\">give to ... </span><span style=\" font-size:10pt;\">(double tap to select)</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        cancel->setText(QApplication::translate("GiveMedium", "cancel", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class GiveMedium: public Ui_GiveMedium {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GIVEMEDIUM_H
