#include "mainwindow.h"
#include "ui_mainwindow.h"




MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
/*  Подготавливаем таблицу*/
//    ui->tableWidget->setRowCount(10);
    this->setWindowTitle(QString(FileName).append(" -CourseWork"));
    ui->tableWidget->setColumnCount(5);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "Название" << "Фирма-изготовитель" << "Размер" << "Год выпуска" << "ОС");
    ui->tableWidget->setColumnWidth(1, 150); //подгоняем ширину столбца "Фирма-изготовитель"
 //   TableSelectionConnect();
    ui->tableWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->tableWidget, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(ShowContextMenu(const QPoint&)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*  Слоты для сигналов от кнопок меню*/
void MainWindow::on_Create_triggered()
{
    ui->statusbar->showMessage("Create");
    if(IsEditedFlag)
    {
        QMessageBox msgBox1;
        msgBox1.setIcon(QMessageBox::Question);
        msgBox1.setWindowTitle(QString(FileName).append(" -CourseWork"));
        msgBox1.setText("Внимание!");
        msgBox1.setInformativeText("Файл был изменен! Сохранить изменения перед открытием нового файла?");
        msgBox1.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        msgBox1.setDefaultButton(QMessageBox::Save);

      //  QMessageBox::StandardButton reply;
      //  reply=QMessageBox::question(this, "Открыть", "Файл был изменен. Все изменения будут утеряны. Продолжить?", QMessageBox::StandardButtons(Yes|No|Cancel));
        int reply=msgBox1.exec();
        switch(reply)
        {
        case QMessageBox::Save:
            on_Save_triggered();
            if(!IsEditedFlag) //проверяем, что мы действительно сохранили, а не нажали отмену в диалоге сохранения
            {
                FileName="Untitled";
                this->setWindowTitle(QString(FileName).append(" -CourseWork"));
                IsFilePathOpen=false; //устанавливаем флаг
                VectorDB.clear();
                UpdateRelation();
                //VectorToTable();
                VectorToTableSearch();
                IsEditedFlag=false;
                this->setWindowTitle(QString("").append(FileName).append(" -CourseWork"));
            }
            break;
        case QMessageBox::Discard:
                FileName="Untitled";
                this->setWindowTitle(QString(FileName).append(" -CourseWork"));
                IsFilePathOpen=false; //устанавливаем флаг
                VectorDB.clear();
                UpdateRelation();
                //VectorToTable();
                VectorToTableSearch();
                IsEditedFlag=false;
                this->setWindowTitle(QString("").append(FileName).append(" -CourseWork"));

                break;
        case QMessageBox::Cancel:
                break;
        }

    /*    if(reply==QMessageBox::Yes)
        {
            FileName="Untitled";
            this->setWindowTitle(QString(FileName).append(" -CourseWork"));
            IsFilePathOpen=false; //устанавливаем флаг
            VectorDB.clear();
            UpdateRelation();
            //VectorToTable();
            VectorToTableSearch();
            IsEditedFlag=false;
            this->setWindowTitle(QString("").append(FileName).append(" -CourseWork"));
        }*/





    }
    else
    {
        FileName="Untitled";
        this->setWindowTitle(QString(FileName).append(" -CourseWork"));
        IsFilePathOpen=false; //устанавливаем флаг
        VectorDB.clear();
        UpdateRelation();
        //VectorToTable();
        VectorToTableSearch();
        IsEditedFlag=false;
        this->setWindowTitle(QString("").append(FileName).append(" -CourseWork"));
    }
}

void MainWindow::on_Open_triggered()
{
    ui->statusbar->showMessage("Open");
    if(IsEditedFlag)
    {
        QMessageBox msgBox1;
        msgBox1.setIcon(QMessageBox::Question);
        msgBox1.setWindowTitle(QString(FileName).append(" -CourseWork"));
        msgBox1.setText("Внимание!");
        msgBox1.setInformativeText("Файл был изменен! Сохранить изменения перед открытием нового файла?");
        msgBox1.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        msgBox1.setDefaultButton(QMessageBox::Save);
  //  QMessageBox::StandardButton reply;
  //  reply=QMessageBox::question(this, "Открыть", "Файл был изменен. Все изменения будут утеряны. Продолжить?");
   // if(reply==QMessageBox::Yes)
        int reply=msgBox1.exec();
        switch(reply)
        {
        case QMessageBox::Save:
            on_Save_triggered();
            if(!IsEditedFlag) //проверяем, что мы действительно сохранили, а не нажали отмену в диалоге сохранения
            {
            QString TempFileName=QFileDialog::getOpenFileName(this, "Открыть файл...", ".", "csv files (*.csv);;All files (*.*)"); //в случае неудачи не обновляем Filename
            QFileInfo CheckFile(TempFileName);
            if (CheckFile.exists() && CheckFile.isFile()) //проверяем, что файл существует и не является директорией
            {
                QFile File(TempFileName);
                if (File.open(QIODevice::ReadOnly)) //открываем файл для чтения
                {
                    /* очищаем вектор обновляем таблицу */
                    VectorDB.clear();
                    UpdateRelation();
                    VectorToTableSearch();
                    /*      */

                    QTextStream fin(&File); //создаем поток
                    while (!fin.atEnd())
                    {
                    QString line = fin.readLine();
                    QStringList fields = line.split(";"); //line.split(";") возвращает список, состоящий из строк, разделенных ;
                    VectorDB.pushBack(ProgramCharact(fields[0], fields[1], fields[2].toLongLong(), fields[3].toInt(), fields[4]));
                    //      ui->statusbar->showMessage("123");
                    }
                    FileName=TempFileName;
                    this->setWindowTitle(QString(FileName).append(" -CourseWork"));
                    File.close();
                    IsFilePathOpen=true; //устанавливаем флаг
                    UpdateRelation();
                    VectorToTableSearch();
                    IsEditedFlag=false;
                    this->setWindowTitle(QString("").append(FileName).append(" -CourseWork"));
                }
            }
            else
            {

                QMessageBox msgBox;
                msgBox.setText("Файл не существует или выбрана директория!");
            }
            }
            break;
        case QMessageBox::Discard:
            QString TempFileName=QFileDialog::getOpenFileName(this, "Открыть файл...", ".", "csv files (*.csv);;All files (*.*)"); //в случае неудачи не обновляем Filename
            QFileInfo CheckFile(TempFileName);
            if (CheckFile.exists() && CheckFile.isFile()) //проверяем, что файл существует и не является директорией
            {
                QFile File(TempFileName);
                if (File.open(QIODevice::ReadOnly)) //открываем файл для чтения
                {
                    /* очищаем вектор обновляем таблицу */
                    VectorDB.clear();
                    UpdateRelation();
                    VectorToTableSearch();
                    /*      */

                    QTextStream fin(&File); //создаем поток
                    while (!fin.atEnd())
                    {
                    QString line = fin.readLine();
                    QStringList fields = line.split(";"); //line.split(";") возвращает список, состоящий из строк, разделенных ;
                    VectorDB.pushBack(ProgramCharact(fields[0], fields[1], fields[2].toLongLong(), fields[3].toInt(), fields[4]));
                    //      ui->statusbar->showMessage("123");
                    }
                    FileName=TempFileName;
                    this->setWindowTitle(QString(FileName).append(" -CourseWork"));
                    File.close();
                    IsFilePathOpen=true; //устанавливаем флаг
                    UpdateRelation();
                    VectorToTableSearch();
                    IsEditedFlag=false;
                    this->setWindowTitle(QString("").append(FileName).append(" -CourseWork"));
                }
            }
            else
            {

                QMessageBox msgBox;
                msgBox.setText("Файл не существует или выбрана директория!");
            }
            break;
        }
    }
    else
    {
        QString TempFileName=QFileDialog::getOpenFileName(this, "Открыть файл...", ".", "csv files (*.csv);;All files (*.*)"); //в случае неудачи не обновляем Filename
        QFileInfo CheckFile(TempFileName);
        if (CheckFile.exists() && CheckFile.isFile()) //проверяем, что файл существует и не является директорией
        {
            QFile File(TempFileName);
            if (File.open(QIODevice::ReadOnly)) //открываем файл для чтения
            {
                /* очищаем вектор обновляем таблицу */
                VectorDB.clear();
                UpdateRelation();
                VectorToTableSearch();
                /*      */

                QTextStream fin(&File); //создаем поток
                while (!fin.atEnd())
                {
                    QString line = fin.readLine();
                    QStringList fields = line.split(";"); //line.split(";") возвращает список, состоящий из строк, разделенных ;
                    VectorDB.pushBack(ProgramCharact(fields[0], fields[1], fields[2].toLongLong(), fields[3].toInt(), fields[4]));
              //      ui->statusbar->showMessage("123");
                }
                FileName=TempFileName;
                this->setWindowTitle(QString(FileName).append(" -CourseWork"));
                File.close();
                IsFilePathOpen=true; //устанавливаем флаг
                UpdateRelation();
                VectorToTableSearch();
                IsEditedFlag=false;
                this->setWindowTitle(QString("").append(FileName).append(" -CourseWork"));
            }
        }
        else
        {

            QMessageBox msgBox;
            msgBox.setText("Файл не существует или выбрана директория!");
        }
    }
}

void MainWindow::on_Save_triggered()
{
    ui->statusbar->showMessage(QString("Save: ").append(FileName));
    TableToVectorSearch();
    UpdateRelation();
    int TempCurrentRow=ui->tableWidget->currentRow();
    VectorToTableSearch();
    ui->tableWidget->setCurrentIndex(ui->tableWidget->model()->index(TempCurrentRow, 0));
    if(IsFilePathOpen) //Если мы уже имеем связь с файлом
    {
        QFile File(FileName);
        if (File.open(QIODevice::WriteOnly|QIODevice::Text)) //открываем файл для записи. QIODevice::Text для локального окончания строк. Т.е. вместо "\n" в потоке в windows будет "\r\n"
        {
            QTextStream fout(&File);
            for(auto &iterator1: VectorDB) //Пример использования итератора. auto определяет тип iterator1 по значению, которым iterator1 инициализируется. использование ссылки позволяет избежать копирования в переменную iterator1. Поскольку Vector<T> имеет функции begin() end(), то их вызовы и определят границы диапазона для цикла for range-based.
            {
                fout << iterator1.GetName() << ";" << iterator1.GetManufacturer() <<";"<< iterator1.GetSize()<< ";" << iterator1.GetYear()<< ";" << iterator1.GetOS()<< "\n";
            }
            IsEditedFlag=false;
            this->setWindowTitle(QString("").append(FileName).append(" -CourseWork"));
        }
    }
    else
    {
    on_SaveAs_triggered(); //если никакой файл не открыт, то сохраняем как.
    }
}

void MainWindow::on_SaveAs_triggered()
{
    ui->statusbar->showMessage("Save As");
    QString TempFileName=QFileDialog::getSaveFileName(this, "Сохранить файл как", ".", "csv files (*.csv);; All files (*.*)");
    TableToVectorSearch();
    UpdateRelation();
    int TempCurrentRow=ui->tableWidget->currentRow();
    VectorToTableSearch();
    ui->tableWidget->setCurrentIndex(ui->tableWidget->model()->index(TempCurrentRow, 0));
    if(TempFileName!="") //если не нажали на cansel
    {
    //    QFileInfo CheckFile(FileName);
       // if (CheckFile.exists() && CheckFile.isFile())
       // {
            QFile File(TempFileName);
            if (File.open(QIODevice::WriteOnly|QIODevice::Text)) //открываем файл для записи. QIODevice::Text для локального окончания строк. Т.е. вместо "\n" в потоке в windows будет "\r\n"
            {
                QTextStream fout(&File);
                size_t i;
                for(i=0;i<VectorDB.getSize(); i++)
                {
                    fout << VectorDB[i].GetName() << ";" << VectorDB[i].GetManufacturer() <<";"<< VectorDB[i].GetSize()<< ";" <<VectorDB[i].GetYear()<< ";" <<VectorDB[i].GetOS()<< "\n";
                }
                FileName=TempFileName;
                this->setWindowTitle(QString(FileName).append(" -CourseWork"));
                IsFilePathOpen=true; //устанавливаем флаг
                IsEditedFlag=false;
                this->setWindowTitle(QString("").append(FileName).append(" -CourseWork"));
            }
      //  }
    }
}

void MainWindow::on_AddDB_triggered()
{
    ui->statusbar->showMessage("AddDB");
    TableToVectorSearch();
    QString TempFileName=QFileDialog::getOpenFileName(this, "Открыть для добавления...", ".", "csv files (*.csv);;All files (*.*)"); //Оставляем Filename прежним
    QFileInfo CheckFile(TempFileName);
    if (CheckFile.exists() && CheckFile.isFile()) //проверяем, что файл существует и не является директорией
    {
        QFile File(TempFileName);
        if (File.open(QIODevice::ReadOnly)) //открываем файл для чтения
        {
            QTextStream fin(&File); //создаем поток
            while (!fin.atEnd())
            {
                QString line = fin.readLine();
                QStringList fields = line.split(";"); //line.split(";") возвращает список, состоящий из строк, разделенных ;
                VectorDB.pushBack(ProgramCharact(fields[0], fields[1], fields[2].toLongLong(), fields[3].toInt(), fields[4]));
          //      ui->statusbar->showMessage("123");
            }
         //   FileName=TempFileName;
         //   this->setWindowTitle(QString(FileName).append(" -CourseWork"));
            File.close();
        //    IsFilePathOpen=true; //устанавливаем флаг
        }
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText("Файл не существует или выбрана директория!");
    }
    UpdateRelation();
    VectorToTableSearch();
}

void MainWindow::on_Quit_triggered()
{
    ui->statusbar->showMessage("Quit");
 //   QCloseEvent event;
 //   closeEvent(&event);
    close(); //строчка closeEvent(&event); не работает. вместо этого вызываем метод close();
 //   QApplication::quit(); тоже можно использовать. вызовет также closeEvent(&event);
 /*   if(IsEditedFlag)
    {
        QMessageBox msgBox1;
        msgBox1.setIcon(QMessageBox::Question);
        msgBox1.setWindowTitle(QString(FileName).append(" -CourseWork"));
        msgBox1.setText("Внимание!");
        msgBox1.setInformativeText("Файл был изменен! Сохранить изменения перед выходом?");
        msgBox1.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        msgBox1.setDefaultButton(QMessageBox::Save);
        //QMessageBox::StandardButton reply;
        int reply=msgBox1.exec();
        switch(reply)
        {
        case QMessageBox::Save:
            on_Save_triggered();
            if(!IsEditedFlag) //проверяем, что мы действительно сохранили, а не нажали отмену в диалоге сохранения
            {
                QApplication::quit();
             //   QMainWindow::closeEvent();
            }
            break;
        case QMessageBox::Discard:
            QApplication::quit();
            break;
        }

   // reply=QMessageBox::question(this, "Открыть", "Файл был изменен. Все изменения будут утеряны. Продолжить?");
   // if(reply==QMessageBox::Yes) QApplication::quit();
    }
    else
    {
        QApplication::quit();
    }*/
}
void MainWindow::closeEvent(QCloseEvent *event) /* Перехват сообщения закрытия программы */
{
/*    QMessageBox::StandardButton reply;
    if(IsEditedFlag)
    {
    reply=QMessageBox::question(this, "Открыть", "Файл был изменен. Все изменения будут утеряны. Продолжить?");
    if(reply==QMessageBox::No) event->ignore();
    }
 //   on_Quit_triggered(); */
    if(IsEditedFlag)
    {
        QMessageBox msgBox1;
        msgBox1.setIcon(QMessageBox::Question);
        msgBox1.setWindowTitle(QString(FileName).append(" -CourseWork"));
        msgBox1.setText("Внимание!");
        msgBox1.setInformativeText("Файл был изменен! Сохранить изменения перед выходом?");
        msgBox1.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        msgBox1.setDefaultButton(QMessageBox::Save);
        //QMessageBox::StandardButton reply;
        int reply=msgBox1.exec();
        switch(reply)
        {
        case QMessageBox::Save:
            on_Save_triggered();
            if(!IsEditedFlag) //проверяем, что мы действительно сохранили, а не нажали отмену в диалоге сохранения
            {
               // QApplication::quit();
                event->accept();
            }
            else
            {
                event->ignore();
            }
            break;
        case QMessageBox::Discard:
            event->accept();
            QMainWindow::closeEvent(event);
          //  QApplication::quit();
           // event->accept();
           // QApplication::quit();
            break;
        case QMessageBox::Cancel:
            event->ignore();
            break;
        }

   // reply=QMessageBox::question(this, "Открыть", "Файл был изменен. Все изменения будут утеряны. Продолжить?");
   // if(reply==QMessageBox::Yes) QApplication::quit();
    }
    else
    {
        QApplication::quit();
    }
}

void MainWindow::on_AddRecord_triggered()
{
    ui->statusbar->showMessage("AddRecord");
    //TableToVector();
    TableToVectorSearch();
    VectorDB.pushBack(ProgramCharact());
    UpdateRelation();
    //VectorToTable();
    VectorToTableSearch();
    ui->tableWidget->scrollToBottom();
    if(SearchRelationVector[SearchRelationVector.getSize()-1]==VectorDB.getSize()-1)    ui->tableWidget->setCurrentIndex(ui->tableWidget->model()->index(SearchRelationVector.getSize()-1, 0)); //т.е. если добавленный элемент,  который последний в векторе, прошел фильтр, то его выделяем.
    // ui->statusbar->showMessage(QString::number(VectorDB[0].GetSize()));
    //   ui->statusbar->showMessage(VectorDB[0].GetName());
}

void MainWindow::on_DeleteRecord_triggered()
{
    int TempCurrentRow=ui->tableWidget->currentRow();
    if(ui->tableWidget->currentRow()!=-1) //после вызова VectorToTable пропадает выделение. Если ничего не выделено, то устанавливается -1
    {
    ui->statusbar->showMessage("DeleteRecord");
    //TableToVector();
    TableToVectorSearch();
    VectorDB.erase(SearchRelationVector[ui->tableWidget->currentRow()], SearchRelationVector[ui->tableWidget->currentRow()]+1);
    //VectorToTable();
    UpdateRelation();
    VectorToTableSearch();
 //   ui->statusbar->showMessage(QString("currentRow=").append(QString::number(ui->tableWidget->currentRow())));

    //Выделяем следующую строку в таблице
    if(TempCurrentRow==SearchRelationVector.getSize()) ui->tableWidget->setCurrentIndex(ui->tableWidget->model()->index(SearchRelationVector.getSize()-1, 0));
        else ui->tableWidget->setCurrentIndex(ui->tableWidget->model()->index(TempCurrentRow, 0));
    }
}

void MainWindow::on_Edit_triggered()
{

    ui->statusbar->showMessage("Edit");
    if(ui->tableWidget->currentRow()!=-1) //если есть выделение
    {
        EditDialog EditDialog1(ui->tableWidget->item(ui->tableWidget->currentRow(), 0)->text(), ui->tableWidget->item(ui->tableWidget->currentRow(), 1)->text(),ui->tableWidget->item(ui->tableWidget->currentRow(), 2)->text(),ui->tableWidget->item(ui->tableWidget->currentRow(), 3)->text(),ui->tableWidget->item(ui->tableWidget->currentRow(), 4)->text());
        EditDialog1.adjustSize(); //вначале подгоняем размер, а потом фиксируем его
        EditDialog1.setFixedHeight(EditDialog1.geometry().height());
        EditDialog1.setWindowTitle(QString("Редактировать: строка:").append(QString::number(ui->tableWidget->currentRow()+1)));
        if(EditDialog1.exec()==QDialog::Accepted)
        {
            ui->tableWidget->item(ui->tableWidget->currentRow(), 0)->setText(EditDialog1.getName());
            ui->tableWidget->item(ui->tableWidget->currentRow(), 1)->setText(EditDialog1.getManufacturer());
            ui->tableWidget->item(ui->tableWidget->currentRow(), 2)->setText(EditDialog1.getSize());
            ui->tableWidget->item(ui->tableWidget->currentRow(), 3)->setText(EditDialog1.getYear());
            ui->tableWidget->item(ui->tableWidget->currentRow(), 4)->setText(EditDialog1.getOS());
            QModelIndex TempIndex=ui->tableWidget->currentIndex();
            int TempRow=SearchRelationVector[TempIndex.row()];
            TableToVectorSearch();
            UpdateRelation();
            VectorToTableSearch();
            int i;
            for(i=0; i<SearchRelationVector.getSize();i++)
            {
                if(SearchRelationVector[i]==TempRow)
                {

                    TempIndex=ui->tableWidget->model()->index(i, TempIndex.column());
                    ui->tableWidget->setCurrentIndex(TempIndex);
                    break;
                }
            }
         //   ui->tableWidget->setCurrentIndex(TempIndex);
        }
    }
}

void MainWindow::on_ShowTxt_triggered() //окошко, где содержимое представленно в текстовом виде, соответствующем формату csv
{
    ui->statusbar->showMessage("ShowTxt");
    disconnect(ui->tableWidget, SIGNAL(cellChanged(int, int)), this, SLOT(on_tableWidget_cellChanged(int, int)));
    QModelIndex TempIndex=ui->tableWidget->currentIndex();
    TableToVectorSearch();
    UpdateRelation();
    VectorToTableSearch();
    ui->tableWidget->setCurrentIndex(TempIndex);

    ShowTxtDialog ShowTxtDialog1;
    size_t i;
    QString StrCSV;
    for(i=0; i<VectorDB.getSize(); i++)
    {
        StrCSV+=VectorDB[i].GetName()+";"+VectorDB[i].GetManufacturer()+";"+QString::number(VectorDB[i].GetSize())+";"+QString::number(VectorDB[i].GetYear())+";"+VectorDB[i].GetOS() + "\n";
    }
    ShowTxtDialog1.TextEditSetText(StrCSV);
    ShowTxtDialog1.setWindowTitle(" -.csv format");
    ShowTxtDialog1.exec();
    connect(ui->tableWidget, SIGNAL(cellChanged(int, int)), this, SLOT(on_tableWidget_cellChanged(int, int)));
}

void MainWindow::on_About_triggered()
{
    ui->statusbar->showMessage("About");
    QMessageBox msgAbout;
//    msgAbout.setIconPixmap(QPixmap(":/IconPrefix1/Icons/help_121828.ico"));
    msgAbout.setWindowTitle("О программе -CourseWork");
    msgAbout.setText("Курсовая работа по дисциплине ООП.\n"
                             "Тема: Класс, характеризующий пакет программ (название, фирма - изготовитель, размер и т.д.)\n"
                             "Вариант: 14\n"
                             "Выполнил студент группы ИКПИ-05\n"
                             "Молошников Федор\n"
                             "Санкт-Петербург\n"
                             "2021 год");
    msgAbout.exec();
}
/*  Слоты для сигналов от кнопок для поиска*/


/*  Слоты для работы с выделением ячеек*/
/* void MainWindow::TlSlot(QModelIndex r, QModelIndex)
{

    QString tempStr;
    tempStr.append("row=");
    tempStr.append(QString::number(r.row()));
    tempStr.append(" column=");
 //   tempStr.append(QString::number(column));
    ui->statusbar->showMessage(tempStr);
}
void MainWindow::TableSelectionConnect()
{

    connect(ui->tableWidget->selectionModel(), SIGNAL(currentChanged(QModelIndex, QModelIndex)), this, SLOT(TlSlot(QModelIndex, QModelIndex)));
    ui->statusbar->showMessage("Trying to connect");
} */
/* void MainWindow::on_tableWidget_cellEntered(int row, int column)
{
    TableSelectionConnect();
    QString tempStr;
    tempStr.append("row=");
    tempStr.append(QString::number(row));
    tempStr.append(" column=");
    tempStr.append(QString::number(column));
    ui->statusbar->showMessage(tempStr);
} */

/* void MainWindow::TableToVector() //версия простая, без поиска
{
//    VectorDB.pushBack(ProgramCharact()); //для отладки
    size_t CurrentSize=VectorDB.getSize();
    ui->statusbar->showMessage(QString::number(CurrentSize).append("=CurrentSize"));
    VectorDB.clear();
    size_t i;
    for(i=0; i<CurrentSize; i++) //заполняем каждый объект вектора. с помощью конструктора с параметрами
    {
        VectorDB.pushBack(ProgramCharact(ui->tableWidget->item(i, 0)->text(), ui->tableWidget->item(i, 1)->text(), ui->tableWidget->item(i, 2)->text().toLongLong(), ui->tableWidget->item(i, 3)->text().toInt(), ui->tableWidget->item(i, 4)->text()));
    }
} */
/* void MainWindow::VectorToTable() //версия простая, без поиска
{
    ui->tableWidget->clearContents(); //удаляет item ы из динамической памяти,а не просто скрывает их
    ui->tableWidget->setRowCount(VectorDB.getSize());
    ui->statusbar->showMessage(QString::number(VectorDB.getSize()).append("=VectorDB.getSize()"));
    size_t i;
    for(i=0; i<VectorDB.getSize(); i++)
    {
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(VectorDB[i].GetName()));
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(VectorDB[i].GetManufacturer()));
        ui->tableWidget->setItem(i, 2, new QTableWidgetItem(QString::number(VectorDB[i].GetSize())));
        ui->tableWidget->setItem(i, 3, new QTableWidgetItem(QString::number(VectorDB[i].GetYear())));
        ui->tableWidget->setItem(i, 4, new QTableWidgetItem(VectorDB[i].GetOS()));
    }
} */

void MainWindow::TableToVectorSearch()
{

  //  ui->statusbar->showMessage(QString::number(SearchRelationVector.getSize()).append("=CurrentSize"));
    size_t i;
    for(i=0; i<SearchRelationVector.getSize(); i++) //заполняем каждый объект вектора. с помощью конструктора с параметрами
    {
        VectorDB[SearchRelationVector[i]].SetName(ui->tableWidget->item(i, 0)->text());
        VectorDB[SearchRelationVector[i]].SetManufacturer(ui->tableWidget->item(i, 1)->text());
        VectorDB[SearchRelationVector[i]].SetSize(ui->tableWidget->item(i, 2)->text().toLongLong());
        VectorDB[SearchRelationVector[i]].SetYear(ui->tableWidget->item(i, 3)->text().toInt());
        VectorDB[SearchRelationVector[i]].SetOS(ui->tableWidget->item(i, 4)->text());
    }
}
void MainWindow::VectorToTableSearch() //версия для поиска
{
    ui->tableWidget->clearContents(); //удаляет item ы из динамической памяти,а не просто скрывает их
    ui->tableWidget->setRowCount(SearchRelationVector.getSize());
 //   ui->statusbar->showMessage(QString::number(SearchRelationVector.getSize()).append("=SearchRelationVector.getSize()"));
    size_t i;
    for(i=0; i<SearchRelationVector.getSize(); i++)
    {
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(VectorDB[SearchRelationVector[i]].GetName()));
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(VectorDB[SearchRelationVector[i]].GetManufacturer()));
        ui->tableWidget->setItem(i, 2, new QTableWidgetItem(QString::number(VectorDB[SearchRelationVector[i]].GetSize())));
        ui->tableWidget->setItem(i, 3, new QTableWidgetItem(QString::number(VectorDB[SearchRelationVector[i]].GetYear())));
        ui->tableWidget->setItem(i, 4, new QTableWidgetItem(VectorDB[SearchRelationVector[i]].GetOS()));
    }
    ui->tableWidget->resizeRowsToContents();
}
void MainWindow::UpdateRelation()
{
    SearchRelationVector.clear();
    size_t i;
    for(i=0;i<VectorDB.getSize();i++) //заполняем вектор отношения
    {
        if(VectorDB[i].GetName().indexOf(ui->LineEditSearch->text())!=-1 || VectorDB[i].GetManufacturer().indexOf(ui->LineEditSearch->text())!=-1 || QString::number(VectorDB[i].GetSize()).indexOf(ui->LineEditSearch->text())!=-1 || QString::number(VectorDB[i].GetYear()).indexOf(ui->LineEditSearch->text())!=-1 || VectorDB[i].GetOS().indexOf(ui->LineEditSearch->text())!=-1)
        {
       //     ui->statusbar->showMessage((ui->LineEditSearch->text()).append(" find!"));
            SearchRelationVector.pushBack(i);
        }
    }
}

void MainWindow::on_tableWidget_cellChanged(int row, int column)
{
    //Тут будем добавлять зведочку в заголовке
    //this->setWindowTitle("*Untitled"); //что-то подобное
    IsEditedFlag=true;
    this->setWindowTitle(QString("*").append(FileName).append(" -CourseWork"));
}

void MainWindow::on_LineEditSearch_textEdited(const QString &arg1)
{
    disconnect(ui->tableWidget, SIGNAL(cellChanged(int, int)), this, SLOT(on_tableWidget_cellChanged(int, int))); //отключаем и подключаем сигнал, чтобы при поиске не было такого, как будто таблица отредактирована
    TableToVectorSearch(); //Тут можно по флагу изменения таблицы, когда он у нас будет.
    UpdateRelation();
    VectorToTableSearch();
    connect(ui->tableWidget, SIGNAL(cellChanged(int, int)), this, SLOT(on_tableWidget_cellChanged(int, int)));
    ui->statusbar->showMessage(QString("Search: DB:").append(QString::number(VectorDB.getSize())).append(" records. Found: ").append(QString::number(SearchRelationVector.getSize())).append(" records"));
}
void MainWindow::ShowContextMenu(const QPoint& pos)
{
// for most widgets
//QPoint globalPos = ui->tableWidget->mapToGlobal(pos);
// for QAbstractScrollArea and derived classes you would use:
QPoint globalPos = ui->tableWidget->viewport()->mapToGlobal(pos);
QMenu myMenu;
myMenu.addAction("Редактировать", this, SLOT(on_Edit_triggered()));
myMenu.addAction("Удалить", this, SLOT(on_DeleteRecord_triggered()));
myMenu.addAction("Добавить", this, SLOT(on_AddRecord_triggered()));
myMenu.exec(globalPos);
}

void MainWindow::on_tableWidget_cellClicked(int row, int column)
{
    ui->statusbar->showMessage(QString("Current row:").append(QString::number(row+1)).append(" column:").append(QString::number(column+1)));
}
