#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QFileInfo> //для проверки файлов на то, что они существуют
#include <QMessageBox>
#include <QMouseEvent> //для крестика
//#include <iostream>

#include "Vector.h"
#include "ProgramCharact.h"
#include "showtxtdialog.h"
#include "editdialog.h"


#define FIELDCOUNT 5 //Задаем число полей

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_Create_triggered();

    void on_Open_triggered();

    void on_Save_triggered();

    void on_SaveAs_triggered();

    void on_AddDB_triggered();

    void on_Quit_triggered();

    void on_AddRecord_triggered();

    void on_DeleteRecord_triggered();

    void on_Edit_triggered();

    void on_ShowTxt_triggered();

    void on_About_triggered();
    //для меню
    void ShowContextMenu(const QPoint&);
/*  Для определения текущей выбранной строки*/
//    void TlSlot(QModelIndex, QModelIndex);

//    void on_tableWidget_cellEntered(int row, int column);

    void on_tableWidget_cellChanged(int row, int column);

    void on_LineEditSearch_textEdited(const QString &arg1);

    void on_tableWidget_cellClicked(int row, int column);

private:
    Ui::MainWindow *ui;

    Vector<ProgramCharact> VectorDB;
    Vector<size_t> SearchRelationVector; //вектор показывающий отношение между VectorDB и тем, что нашлось в поиске
    QString FileName="Untitled"; //путь с именем к текущему файлу таблицы
    bool IsFilePathOpen=false; //флаг того, что открыт какойто файл. диалог getSaveFileName при нажатии cansel возвращает пустую строку, поэтому мы не знаем что произошло нажад ли пользователь отмена или мы разорвали связь с именем файла
    bool IsEditedFlag=false;    //флаг того, что документ редактировали.
    //    void TableSelectionConnect();

// Методы для работы с таблицей и вектором=================================
//    void TableToVector(); //рабочие методы без учета поиска
//    void VectorToTable(); //рабочие методы без учета поиска

    void TableToVectorSearch(); //то же самое, только с учетом поиска
    void VectorToTableSearch(); //то же самое, только с учетом поиска

    void UpdateRelation(); //вспомогательная функция, обновляет SearchRelationVector
 //   void OnDocumentEdit(); //функция, вызываемая после того, как документ был отредактирован
    void closeEvent(QCloseEvent *event); /* Перехват сообщения закрытия программы */

};
#endif // MAINWINDOW_H
