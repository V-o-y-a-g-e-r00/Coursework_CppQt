#ifndef SHOWTXTDIALOG_H
#define SHOWTXTDIALOG_H

#include <QDialog>

namespace Ui {
class ShowTxtDialog;
}

class ShowTxtDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ShowTxtDialog(QWidget *parent = nullptr);
    ~ShowTxtDialog();
    void TextEditSetText(QString StrCSV);

private:
    Ui::ShowTxtDialog *ui;
};

#endif // SHOWTXTDIALOG_H
