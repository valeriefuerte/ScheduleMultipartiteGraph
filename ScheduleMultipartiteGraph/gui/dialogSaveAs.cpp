#include "dialogSaveAs.h"
#include "ui_dialogSaveAs.h"
#include<QTableView>
#include <QListView>
#include <QDebug>

QFileInfo fileInfo;
DialogSaveAs::DialogSaveAs(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogSaveAs)
{
    ui->setupUi(this);
    ui->table_file_dir->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    model = new QFileSystemModel(this);
    model->setFilter(QDir::QDir::AllEntries);
    model->setNameFilters(QStringList()<<"*.json");

    model->setRootPath(QDir::currentPath());
    ui->table_file_dir->setModel(model);
    ui->table_file_dir->setRootIndex(model->index(QDir::currentPath()+"/storage"));

    curpath=QDir::currentPath()+"/storage";
    ui->table_file_dir->show();

    ui->fileName_Line_Edit->setValidator(new QRegExpValidator(QRegExp("[a-z-A-Z-0-9_]+")));
}


DialogSaveAs::~DialogSaveAs()
{
    delete ui;
}

void DialogSaveAs::on_table_file_dir_doubleClicked(const QModelIndex &index)
{
    QListView *listView = (QListView*) sender();

     fileInfo = model->fileInfo(index);

    curpath=fileInfo.canonicalFilePath();
    if (fileInfo.fileName()==".."){
        QDir dir = fileInfo.dir();
        dir.cdUp();
        listView->setRootIndex(model->index(dir.absolutePath()));
    }
    else if (fileInfo.fileName()=="."){
        listView->setRootIndex(model->index(""));
    }
    else if (fileInfo.isDir()){
        listView->setRootIndex(index);
    }
}

void DialogSaveAs::on_table_file_dir_clicked(const QModelIndex &index)
{
    if (openFile){
        QString name;
        if (!(index.data().toString()=="."||index.data().toString()=="..")&&index.column()==0){
            name =index.data().toString();
            name.remove(".json");

            ui->fileName_Line_Edit->setText(name);
        }
    pathFile=curpath+"/"+name+".json";
   }
}

//событие кнопки сохранить
void DialogSaveAs::on_saveButton_clicked()
{
    //имя файла
    QString name =ui->fileName_Line_Edit->text();
    if (name=="")
    {
        fileName=name;
    }
    else{
        fileName=name;
    }
    emit sendFileName(curpath+"/"+name+".json",fileName,false);

}

void DialogSaveAs::changeDialogOpenFile(){
    this->setWindowTitle("Открыть");

    ui->saveButton->hide();
    ui->createButton->hide();
    ui->deleteButton->hide();

}

void DialogSaveAs::changeDialogSaveFile(){
    this->setWindowTitle("Сохранить");
    ui->openButton->hide();
    ui->createButton->hide();
    ui->deleteButton->hide();

    openFile=false;
}

void DialogSaveAs::changeDialogNewFile(){
    this->setWindowTitle("Создать");
    ui->openButton->hide();
    ui->saveButton->hide();
    ui->deleteButton->hide();

    openFile = false;
}

void DialogSaveAs::changeDialogDeleteFile(){
    this->setWindowTitle("Удалить");

    ui->openButton->hide();
    ui->saveButton->hide();
    ui->createButton->hide();

}

//событие кнопки открыть
void DialogSaveAs::on_openButton_clicked()
{
    //имя файла
    QString name =ui->fileName_Line_Edit->text();
    if (name=="")
    {
        fileName=name;
    }
    else {
        fileName=name;
    }
    emit sendSelectedFileName(pathFile, fileName);

}

//событие кнопки создать
void DialogSaveAs::on_createButton_clicked()
{
     //имя файла
    QString name =ui->fileName_Line_Edit->text();
    if (name=="")
    {
        fileName=name;
    }
    else{

        fileName = name;
    }
    emit sendFileName(curpath+"/"+name+".json",fileName,true);

}
//событие кнопки удалить
void DialogSaveAs::on_deleteButton_clicked()
{
    //имя файла
   QString name =ui->fileName_Line_Edit->text();
   if (name=="")
   {
       fileName=name;
   }
   else{

       fileName = name;
   }

    emit sendDeleteFileName(curpath+"/"+name+".json",fileName);
}
void DialogSaveAs::closeEvent(QCloseEvent *){
    ui->fileName_Line_Edit->clear();
    ui->table_file_dir->selectionModel()->clear();

    fileName.clear();

    ui->saveButton->show();
    ui->openButton->show();
    ui->createButton->show();
    ui->deleteButton->show();

    openFile=true;


}


