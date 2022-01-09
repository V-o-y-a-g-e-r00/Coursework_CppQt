#ifndef EDITDIALOG_H
#define EDITDIALOG_H

#include <QDialog>
#include <QString>

namespace Ui {
class EditDialog;
}

class EditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditDialog(QWidget *parent = nullptr);
    EditDialog(QString txt0,QString txt1, QString txt2, QString txt3, QString txt4, QWidget *parent = nullptr);
    ~EditDialog();
    QString getName();
    QString getManufacturer();
    QString getSize();
    QString getYear();
    QString getOS();

private:
    Ui::EditDialog *ui;
};

#endif // EDITDIALOG_H
