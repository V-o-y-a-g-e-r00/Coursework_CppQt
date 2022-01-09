#include "editdialog.h"
#include "ui_editdialog.h"

EditDialog::EditDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditDialog)
{
    ui->setupUi(this);

}
EditDialog::EditDialog(QString txt0,QString txt1, QString txt2, QString txt3, QString txt4, QWidget *parent):QDialog(parent), ui(new Ui::EditDialog)
{
    ui->setupUi(this);
    ui->lineEdit->setText(txt0);
    ui->lineEdit_2->setText(txt1);
    ui->lineEdit_3->setText(txt2);
    ui->lineEdit_4->setText(txt3);
    ui->lineEdit_5->setText(txt4);
}
EditDialog::~EditDialog()
{
    delete ui;
}
QString EditDialog::getName(){return ui->lineEdit->text();}
QString EditDialog::getManufacturer(){return ui->lineEdit_2->text();}
QString EditDialog::getSize(){return ui->lineEdit_3->text();}
QString EditDialog::getYear(){return ui->lineEdit_4->text();}
QString EditDialog::getOS(){return ui->lineEdit_5->text();}
