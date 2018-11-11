#include <QMessageBox>
#include "addnewpersondialog.h"
#include "ui_addnewpersondialog.h"

AddNewPersonDialog::AddNewPersonDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddNewPersonDialog)
{
    ui->setupUi(this);
}

AddNewPersonDialog::~AddNewPersonDialog()
{
    delete ui;
}

void AddNewPersonDialog::on_buttonBox_accepted()
{
    if(ui->plainTextName->toPlainText().isEmpty()) {
        QMessageBox::information(this, "can not complete", "fill name in");
    }
}
