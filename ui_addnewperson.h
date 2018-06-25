/********************************************************************************
** Form generated from reading UI file 'addnewperson.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDNEWPERSON_H
#define UI_ADDNEWPERSON_H

#include <QtCore/QDate>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDateEdit>
#include <QtGui/QDialog>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_AddNewPerson
{
public:
    QVBoxLayout *verticalLayout_3;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_4;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *nameLineEdit;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QDateEdit *birthdayEdit;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *completeButton;
    QPushButton *cancelButton;

    void setupUi(QDialog *AddNewPerson)
    {
        if (AddNewPerson->objectName().isEmpty())
            AddNewPerson->setObjectName(QString::fromUtf8("AddNewPerson"));
        AddNewPerson->resize(289, 178);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(AddNewPerson->sizePolicy().hasHeightForWidth());
        AddNewPerson->setSizePolicy(sizePolicy);
        verticalLayout_3 = new QVBoxLayout(AddNewPerson);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        groupBox = new QGroupBox(AddNewPerson);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        verticalLayout_4 = new QVBoxLayout(groupBox);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        nameLineEdit = new QLineEdit(groupBox);
        nameLineEdit->setObjectName(QString::fromUtf8("nameLineEdit"));

        horizontalLayout->addWidget(nameLineEdit);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_2->addWidget(label_2);

        birthdayEdit = new QDateEdit(groupBox);
        birthdayEdit->setObjectName(QString::fromUtf8("birthdayEdit"));
        birthdayEdit->setMinimumTime(QTime(0, 0, 0));
        birthdayEdit->setCalendarPopup(true);
        birthdayEdit->setDate(QDate(2000, 1, 1));

        horizontalLayout_2->addWidget(birthdayEdit);


        verticalLayout->addLayout(horizontalLayout_2);


        verticalLayout_2->addLayout(verticalLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        completeButton = new QPushButton(groupBox);
        completeButton->setObjectName(QString::fromUtf8("completeButton"));

        horizontalLayout_3->addWidget(completeButton);

        cancelButton = new QPushButton(groupBox);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));

        horizontalLayout_3->addWidget(cancelButton);


        verticalLayout_2->addLayout(horizontalLayout_3);


        verticalLayout_4->addLayout(verticalLayout_2);


        verticalLayout_3->addWidget(groupBox);


        retranslateUi(AddNewPerson);

        QMetaObject::connectSlotsByName(AddNewPerson);
    } // setupUi

    void retranslateUi(QDialog *AddNewPerson)
    {
        AddNewPerson->setWindowTitle(QApplication::translate("AddNewPerson", "Dialog", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("AddNewPerson", "add new Person", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("AddNewPerson", "name", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("AddNewPerson", "birthday", 0, QApplication::UnicodeUTF8));
        birthdayEdit->setDisplayFormat(QApplication::translate("AddNewPerson", "dd.MM.yyyy", 0, QApplication::UnicodeUTF8));
        completeButton->setText(QApplication::translate("AddNewPerson", "comlete", 0, QApplication::UnicodeUTF8));
        cancelButton->setText(QApplication::translate("AddNewPerson", "cancel", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class AddNewPerson: public Ui_AddNewPerson {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDNEWPERSON_H
