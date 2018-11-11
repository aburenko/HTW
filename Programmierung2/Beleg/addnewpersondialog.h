#ifndef ADDNEWPERSONDIALOG_H
#define ADDNEWPERSONDIALOG_H

#include <QDialog>

namespace Ui {
class AddNewPersonDialog;
}

class AddNewPersonDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddNewPersonDialog(QWidget *parent = 0);
    ~AddNewPersonDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::AddNewPersonDialog *ui;
};

#endif // ADDNEWPERSONDIALOG_H
