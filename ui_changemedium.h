/********************************************************************************
** Form generated from reading UI file 'changemedium.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHANGEMEDIUM_H
#define UI_CHANGEMEDIUM_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QFormLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpinBox>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_ChangeMedium
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QFormLayout *formLayout;
    QLabel *label;
    QLineEdit *typeEdit;
    QLabel *label_2;
    QLineEdit *idEdit;
    QLabel *label_3;
    QLineEdit *titleEdit;
    QLabel *label_4;
    QLineEdit *AuthorEdit;
    QLabel *label_5;
    QDoubleSpinBox *durOrPagEdit;
    QLabel *label_6;
    QSpinBox *qualityEdit;
    QLabel *label_7;
    QSpinBox *yearEdit;
    QLabel *label_8;
    QLineEdit *givenToEdit;
    QPushButton *pushButton_2;
    QPushButton *pushButton;

    void setupUi(QDialog *ChangeMedium)
    {
        if (ChangeMedium->objectName().isEmpty())
            ChangeMedium->setObjectName(QString::fromUtf8("ChangeMedium"));
        ChangeMedium->resize(435, 397);
        verticalLayout = new QVBoxLayout(ChangeMedium);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        groupBox = new QGroupBox(ChangeMedium);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setMinimumSize(QSize(200, 200));
        groupBox->setFlat(true);
        formLayout = new QFormLayout(groupBox);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        typeEdit = new QLineEdit(groupBox);
        typeEdit->setObjectName(QString::fromUtf8("typeEdit"));
        typeEdit->setEnabled(false);
        typeEdit->setMaxLength(50);
        typeEdit->setReadOnly(false);

        formLayout->setWidget(0, QFormLayout::FieldRole, typeEdit);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        idEdit = new QLineEdit(groupBox);
        idEdit->setObjectName(QString::fromUtf8("idEdit"));
        idEdit->setEnabled(false);
        idEdit->setMaxLength(50);
        idEdit->setReadOnly(false);

        formLayout->setWidget(1, QFormLayout::FieldRole, idEdit);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_3);

        titleEdit = new QLineEdit(groupBox);
        titleEdit->setObjectName(QString::fromUtf8("titleEdit"));
        titleEdit->setMaxLength(50);

        formLayout->setWidget(2, QFormLayout::FieldRole, titleEdit);

        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        formLayout->setWidget(3, QFormLayout::LabelRole, label_4);

        AuthorEdit = new QLineEdit(groupBox);
        AuthorEdit->setObjectName(QString::fromUtf8("AuthorEdit"));
        AuthorEdit->setMaxLength(50);

        formLayout->setWidget(3, QFormLayout::FieldRole, AuthorEdit);

        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        formLayout->setWidget(4, QFormLayout::LabelRole, label_5);

        durOrPagEdit = new QDoubleSpinBox(groupBox);
        durOrPagEdit->setObjectName(QString::fromUtf8("durOrPagEdit"));
        durOrPagEdit->setMaximum(10000);

        formLayout->setWidget(4, QFormLayout::FieldRole, durOrPagEdit);

        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        formLayout->setWidget(5, QFormLayout::LabelRole, label_6);

        qualityEdit = new QSpinBox(groupBox);
        qualityEdit->setObjectName(QString::fromUtf8("qualityEdit"));
        qualityEdit->setEnabled(false);
        qualityEdit->setMinimum(140);
        qualityEdit->setMaximum(1080);
        qualityEdit->setSingleStep(120);
        qualityEdit->setValue(140);

        formLayout->setWidget(5, QFormLayout::FieldRole, qualityEdit);

        label_7 = new QLabel(groupBox);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        formLayout->setWidget(6, QFormLayout::LabelRole, label_7);

        yearEdit = new QSpinBox(groupBox);
        yearEdit->setObjectName(QString::fromUtf8("yearEdit"));
        yearEdit->setMinimum(999);
        yearEdit->setMaximum(2020);
        yearEdit->setValue(1999);

        formLayout->setWidget(6, QFormLayout::FieldRole, yearEdit);

        label_8 = new QLabel(groupBox);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        formLayout->setWidget(7, QFormLayout::LabelRole, label_8);

        givenToEdit = new QLineEdit(groupBox);
        givenToEdit->setObjectName(QString::fromUtf8("givenToEdit"));
        givenToEdit->setEnabled(false);
        givenToEdit->setMaxLength(50);
        givenToEdit->setReadOnly(false);

        formLayout->setWidget(7, QFormLayout::FieldRole, givenToEdit);

        pushButton_2 = new QPushButton(groupBox);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        formLayout->setWidget(8, QFormLayout::LabelRole, pushButton_2);

        pushButton = new QPushButton(groupBox);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        formLayout->setWidget(8, QFormLayout::FieldRole, pushButton);


        verticalLayout->addWidget(groupBox);


        retranslateUi(ChangeMedium);

        QMetaObject::connectSlotsByName(ChangeMedium);
    } // setupUi

    void retranslateUi(QDialog *ChangeMedium)
    {
        ChangeMedium->setWindowTitle(QApplication::translate("ChangeMedium", "Dialog", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("ChangeMedium", "change person data", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("ChangeMedium", "type", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("ChangeMedium", "id", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("ChangeMedium", "title", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("ChangeMedium", "author", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("ChangeMedium", "duration / pages", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("ChangeMedium", "quality", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("ChangeMedium", "year", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("ChangeMedium", "given to...", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("ChangeMedium", "cancel", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("ChangeMedium", "save", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ChangeMedium: public Ui_ChangeMedium {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHANGEMEDIUM_H
