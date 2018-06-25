/********************************************************************************
** Form generated from reading UI file 'addnewmedium.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDNEWMEDIUM_H
#define UI_ADDNEWMEDIUM_H

#include <QtCore/QDate>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDateEdit>
#include <QtGui/QDialog>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QSpinBox>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_AddNewMedium
{
public:
    QVBoxLayout *verticalLayout_4;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout_8;
    QVBoxLayout *typeMediumLayout;
    QRadioButton *radioButtonBook;
    QRadioButton *radioButtonCD;
    QRadioButton *radioButtonDVD;
    QVBoxLayout *verticalLayout;
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLineEdit *titleEdit;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_5;
    QLineEdit *authorEdit;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QDateEdit *yearEdit;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QSpinBox *pagesEdit;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_6;
    QDoubleSpinBox *durationEdit;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_4;
    QSpinBox *qualityEdit;
    QHBoxLayout *horizontalLayout_7;
    QPushButton *addButton;
    QPushButton *cancelButton;

    void setupUi(QDialog *AddNewMedium)
    {
        if (AddNewMedium->objectName().isEmpty())
            AddNewMedium->setObjectName(QString::fromUtf8("AddNewMedium"));
        AddNewMedium->resize(282, 374);
        verticalLayout_4 = new QVBoxLayout(AddNewMedium);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        groupBox = new QGroupBox(AddNewMedium);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        horizontalLayout_8 = new QHBoxLayout(groupBox);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        typeMediumLayout = new QVBoxLayout();
        typeMediumLayout->setObjectName(QString::fromUtf8("typeMediumLayout"));
        radioButtonBook = new QRadioButton(groupBox);
        radioButtonBook->setObjectName(QString::fromUtf8("radioButtonBook"));
        radioButtonBook->setChecked(true);

        typeMediumLayout->addWidget(radioButtonBook);

        radioButtonCD = new QRadioButton(groupBox);
        radioButtonCD->setObjectName(QString::fromUtf8("radioButtonCD"));

        typeMediumLayout->addWidget(radioButtonCD);

        radioButtonDVD = new QRadioButton(groupBox);
        radioButtonDVD->setObjectName(QString::fromUtf8("radioButtonDVD"));

        typeMediumLayout->addWidget(radioButtonDVD);


        horizontalLayout_8->addLayout(typeMediumLayout);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_2->addWidget(label);

        titleEdit = new QLineEdit(groupBox);
        titleEdit->setObjectName(QString::fromUtf8("titleEdit"));
        titleEdit->setMaxLength(50);

        horizontalLayout_2->addWidget(titleEdit);


        verticalLayout_2->addLayout(horizontalLayout_2);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout_5->addWidget(label_5);

        authorEdit = new QLineEdit(groupBox);
        authorEdit->setObjectName(QString::fromUtf8("authorEdit"));
        authorEdit->setMaxLength(50);

        horizontalLayout_5->addWidget(authorEdit);


        verticalLayout_2->addLayout(horizontalLayout_5);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout->addWidget(label_2);

        yearEdit = new QDateEdit(groupBox);
        yearEdit->setObjectName(QString::fromUtf8("yearEdit"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(yearEdit->sizePolicy().hasHeightForWidth());
        yearEdit->setSizePolicy(sizePolicy);
        yearEdit->setMinimumDateTime(QDateTime(QDate(1753, 9, 14), QTime(0, 0, 0)));
        yearEdit->setMaximumDate(QDate(2019, 12, 31));

        horizontalLayout->addWidget(yearEdit);


        verticalLayout_2->addLayout(horizontalLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_3->addWidget(label_3);

        pagesEdit = new QSpinBox(groupBox);
        pagesEdit->setObjectName(QString::fromUtf8("pagesEdit"));
        pagesEdit->setMinimum(10);
        pagesEdit->setMaximum(2000);

        horizontalLayout_3->addWidget(pagesEdit);


        verticalLayout_2->addLayout(horizontalLayout_3);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        horizontalLayout_6->addWidget(label_6);

        durationEdit = new QDoubleSpinBox(groupBox);
        durationEdit->setObjectName(QString::fromUtf8("durationEdit"));
        durationEdit->setEnabled(false);
        durationEdit->setMaximum(300);
        durationEdit->setSingleStep(0.1);
        durationEdit->setValue(3);

        horizontalLayout_6->addWidget(durationEdit);


        verticalLayout_2->addLayout(horizontalLayout_6);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_4->addWidget(label_4);

        qualityEdit = new QSpinBox(groupBox);
        qualityEdit->setObjectName(QString::fromUtf8("qualityEdit"));
        qualityEdit->setEnabled(false);
        qualityEdit->setMinimum(240);
        qualityEdit->setMaximum(1080);
        qualityEdit->setSingleStep(120);

        horizontalLayout_4->addWidget(qualityEdit);


        verticalLayout_2->addLayout(horizontalLayout_4);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        addButton = new QPushButton(groupBox);
        addButton->setObjectName(QString::fromUtf8("addButton"));

        horizontalLayout_7->addWidget(addButton);

        cancelButton = new QPushButton(groupBox);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));

        horizontalLayout_7->addWidget(cancelButton);


        verticalLayout_2->addLayout(horizontalLayout_7);


        verticalLayout_3->addLayout(verticalLayout_2);


        verticalLayout->addLayout(verticalLayout_3);


        horizontalLayout_8->addLayout(verticalLayout);


        verticalLayout_4->addWidget(groupBox);


        retranslateUi(AddNewMedium);

        QMetaObject::connectSlotsByName(AddNewMedium);
    } // setupUi

    void retranslateUi(QDialog *AddNewMedium)
    {
        AddNewMedium->setWindowTitle(QApplication::translate("AddNewMedium", "Dialog", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("AddNewMedium", "add new medium", 0, QApplication::UnicodeUTF8));
        radioButtonBook->setText(QApplication::translate("AddNewMedium", "Book", 0, QApplication::UnicodeUTF8));
        radioButtonCD->setText(QApplication::translate("AddNewMedium", "&CD", 0, QApplication::UnicodeUTF8));
        radioButtonDVD->setText(QApplication::translate("AddNewMedium", "DVD", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("AddNewMedium", "title", 0, QApplication::UnicodeUTF8));
        titleEdit->setPlaceholderText(QApplication::translate("AddNewMedium", "War and Peace", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("AddNewMedium", "author", 0, QApplication::UnicodeUTF8));
        authorEdit->setPlaceholderText(QApplication::translate("AddNewMedium", "Tolstoy", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("AddNewMedium", "year published", 0, QApplication::UnicodeUTF8));
        yearEdit->setDisplayFormat(QApplication::translate("AddNewMedium", "yyyy", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("AddNewMedium", "number of pages", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("AddNewMedium", "duration", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("AddNewMedium", "video quality", 0, QApplication::UnicodeUTF8));
        addButton->setText(QApplication::translate("AddNewMedium", "add", 0, QApplication::UnicodeUTF8));
        cancelButton->setText(QApplication::translate("AddNewMedium", "cancel", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class AddNewMedium: public Ui_AddNewMedium {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDNEWMEDIUM_H
