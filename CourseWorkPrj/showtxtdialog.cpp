#include "showtxtdialog.h"
#include "ui_showtxtdialog.h"

ShowTxtDialog::ShowTxtDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ShowTxtDialog)
{
    ui->setupUi(this);
}

ShowTxtDialog::~ShowTxtDialog()
{
    delete ui;
}

void ShowTxtDialog::TextEditSetText(QString StrCSV)
{
    ui->textEdit->setText(StrCSV);
}
