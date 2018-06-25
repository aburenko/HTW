/********************************************************************************
** Form generated from reading UI file 'changeperson.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHANGEPERSON_H
#define UI_CHANGEPERSON_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDateEdit>
#include <QtGui/QDialog>
#include <QtGui/QFormLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_ChangePerson
{
public:
    QFormLayout *formLayout;
    QLabel *label;
    QLineEdit *idEdit;
    QLabel *label_2;
    QLineEdit *nameEdit;
    QLabel *label_3;
    QDateEdit *dateEdit;
    QLabel *label_4;
    QLineEdit *numberEdit;
    QPushButton *cancelButton;
    QPushButton *saveButton;

    void setupUi(QDialog *ChangePerson)
    {
        if (ChangePerson->objectName().isEmpty())
            ChangePerson->setObjectName(QString::fromUtf8("ChangePerson"));
        ChangePerson->resize(311, 196);
        ChangePerson->setMinimumSize(QSize(200, 150));
        formLayout = new QFormLayout(ChangePerson);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        label = new QLabel(ChangePerson);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        idEdit = new QLineEdit(ChangePerson);
        idEdit->setObjectName(QString::fromUtf8("idEdit"));
        idEdit->setEnabled(false);

        formLayout->setWidget(0, QFormLayout::FieldRole, idEdit);

        label_2 = new QLabel(ChangePerson);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        nameEdit = new QLineEdit(ChangePerson);
        nameEdit->setObjectName(QString::fromUtf8("nameEdit"));
        nameEdit->setMaxLength(50);

        formLayout->setWidget(1, QFormLayout::FieldRole, nameEdit);

        label_3 = new QLabel(ChangePerson);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_3);

        dateEdit = new QDateEdit(ChangePerson);
        dateEdit->setObjectName(QString::fromUtf8("dateEdit"));
        dateEdit->setCalendarPopup(true);

        formLayout->setWidget(2, QFormLayout::FieldRole, dateEdit);

        label_4 = new QLabel(ChangePerson);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        formLayout->setWidget(3, QFormLayout::LabelRole, label_4);

        numberEdit = new QLineEdit(ChangePerson);
        numberEdit->setObjectName(QString::fromUtf8("numberEdit"));
        numberEdit->setEnabled(false);

        formLayout->setWidget(3, QFormLayout::FieldRole, numberEdit);

        cancelButton = new QPushButton(ChangePerson);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));

        formLayout->setWidget(4, QFormLayout::LabelRole, cancelButton);

        saveButton = new QPushButton(ChangePerson);
        saveButton->setObjectName(QString::fromUtf8("saveButton"));

        formLayout->setWidget(4, QFormLayout::FieldRole, saveButton);


        retranslateUi(ChangePerson);

        QMetaObject::connectSlotsByName(ChangePerson);
    } // setupUi

    void retranslateUi(QDialog *ChangePerson)
    {
        ChangePerson->setWindowTitle(QApplication::translate("ChangePerson", "Dialog", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("ChangePerson", "id", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("ChangePerson", "name", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("ChangePerson", "birthday", 0, QApplication::UnicodeUTF8));
        dateEdit->setDisplayFormat(QApplication::translate("ChangePerson", "dd.MM.yyyy", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("ChangePerson", "number of medium", 0, QApplication::UnicodeUTF8));
        cancelButton->setText(QApplication::translate("ChangePerson", "cancel", 0, QApplication::UnicodeUTF8));
        saveButton->setText(QApplication::translate("ChangePerson", "save", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ChangePerson: public Ui_ChangePerson {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHANGEPERSON_H
