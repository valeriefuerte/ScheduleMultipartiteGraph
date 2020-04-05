#include <QtGui>
#include <QApplication>
#include <QTableView>
#include <QTreeView>
#include <QListView>
#include <QSplitter>
#include <QHeaderView>
#include <QDebug>
#include <QAbstractTableModel>
#include <QTime>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "models/table_model.h"
#include "dialogWindowEmptyRow.h"
#include "dialogCabinetWindow.h"
#include "models/repository/repositorytemplate.h"
#include "gui/dialogLessonTimeWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
      ui->setupUi(this);
      //Инициализация моделей QTableView
      list_s = new QStringList();
      list_gr = new QStringList();
      list_cb=new QStringList();
      list_tm = new QStringList();

      //Начальная визуализация QTableView
      //Таблица "Предметы"
      subjectModel = new StringListModel(*list_s);

      //Таблица "Группы"
      groupModel=new StringListModel(*list_gr);

       //Таблица Кабинеты
      cabinetModel=new StringListModel(*list_cb);

      //Инициализация диалоговых окон
      dialogEmptyRow = new DialogWindowEmptyRow();
      dialogEmptyRow->resize(300,100);

      dialogConfrimEdit = new DialogWindowConfirmEditRow();
      dialogConfrimEdit->resize(300,100);

      dialogConfirmCabinet = new DialogCabinetWindow();
      dialogLessonTime = new DialogLessonTimeWindow();

      connect(dialogConfirmCabinet, SIGNAL(sendDataCabinet(Cabinet)), this, SLOT(receiveDataCabinet(Cabinet)));

      connect(dialogConfirmCabinet, SIGNAL(sendEditDataCabinet(RepositoryTemplate<Cabinet>*)), this,SLOT(receiveEditDataCabinet(RepositoryTemplate<Cabinet>*)));

      connect(this,SIGNAL(sendSelectionCabinet(Cabinet)),dialogConfirmCabinet,SLOT(receiveSelectionCabinet(Cabinet)));

      //    qDebug() << "Кабинеты: " << endl;
      //    for (auto it = this->repoCabinets.begin(), end = this->repoCabinets.end(); it < end; ++it) {
      //        auto element = *it;
      //        qDebug() << element.toString() << endl;
      //    }

      //    qDebug() << endl << "Время: " << endl;
      //    for (auto it = this->repoLessonsTimes.begin(), end = this->repoLessonsTimes.end(); it < end; ++it) {
      //        auto element = *it;
      //        qDebug() << element.toString() << endl;
      //    }

      //    qDebug() << endl << "Группы: " << endl;
      //    for (auto it = this->repoGroupStudents.begin(), end = this->repoGroupStudents.end(); it < end; ++it) {
      //        auto element = *it;
      //        qDebug() << element.toString() << endl;
      //    }

      //    qDebug() << endl << "Дисциплины: " << endl;
      //    for (auto it = this->repoSubjects.begin(), end = this->repoSubjects.end(); it < end; ++it) {
      //        auto element = *it;
      //        qDebug() << element.toString() << endl;
      //    }

      //    auto s = this->repoSubjects.getById(2);
      //    qDebug() << "Получение по id" << endl;
      //    qDebug() << s.toString() << endl;

      //    qDebug() << "Получение по параметрам" << endl;
      //    for (auto e : this->repoSubjects.getByParameters(Subject("йцуйцу"))) {
      //        qDebug() << e.toString() << endl;
      //    }

      //    qDebug() << "Добавление элемента 'Новый элемент'" << endl;
      //    this->repoSubjects.add(Subject("Новый элемент"));
      //    qDebug() << endl << "Дисциплины: " << endl;
      //    for (auto e : this->repoSubjects.getAll()) {
      //        qDebug() << e.toString() << endl;
      //    }

      //    qDebug() << "Изменение элемента 'Новый элемент' на 'Измененный элемент'" << endl;
      //    this->repoSubjects.update(4, Subject("Измененный элемент"));
      //    qDebug() << endl << "Дисциплины: " << endl;
      //    for (auto e : this->repoSubjects.getAll()) {
      //        qDebug() << e.toString() << endl;
      //    }

      //    qDebug() << "Удаление элемента 'Измененный элемент'" << endl;
      //    this->repoSubjects.remove(4);
      //    qDebug() << endl << "Дисциплины: " << endl;
      //    for (auto e : this->repoSubjects.getAll()) {
      //        qDebug() << e.toString() << endl;
      //    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::visualRows(QTableView *table, StringListModel *model){
    table->setModel(model);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void MainWindow::on_addSubjectButton_clicked()
{
    qDebug()<<"Индекс"<<ui->subject_table->currentIndex().row();
    if (!(list_s->isEmpty())){
            if ((list_s->last()=="")&&(ui->subject_table->currentIndex().row()==-1)){
                dialogEmptyRow->show();
                qDebug()<<"addConfirm1";
                return;
           }
    }
    if (!(list_s->isEmpty())){
            if ((list_s->last()!=ui->subject_table->currentIndex().data())){
                qDebug()<<"addConfirm2";
                dialogConfrimEdit->show();
                return;
            }
    }
    if (!(list_s->isEmpty())){
            if ((list_s->last()=="")&&(ui->subject_table->currentIndex().data()=="")){
                qDebug()<<"addConfirm3";
                dialogEmptyRow->show();
                return;
            }
    }
    list_s->append("");
    int index =ui->subject_table->currentIndex().row()+1;
    subjectModel->insertRow(index);

    const QModelIndex indexNext=subjectModel->index(index,0);

    ui->subject_table->setCurrentIndex(indexNext);
    visualRows(ui->subject_table,subjectModel);
}

void MainWindow::on_removeSubjectButton_clicked()
{

    int index =ui->subject_table->selectionModel()->currentIndex().row();
    qDebug()<<repoSubjects.getById(index).name;
    repoSubjects.remove(index);
    list_s->removeAt(index);
    ui->subject_table->model()->removeRow(index);

}

void MainWindow::on_confirmSubjectButton_clicked()
{
    int index = ui->subject_table->selectionModel()->currentIndex().row();
    QVariant value = ui->subject_table->selectionModel()->currentIndex().data();
    QString str = value.toString();
    if (str==""){
        qDebug()<<"Confirm";
        dialogEmptyRow->show();
    }
    else{
        repoSubjects.add(str);
        list_s->replace(index,str);
     }


}

void MainWindow::on_addGroupButton_clicked()
{
    if (!(list_gr->isEmpty())){
            if ((list_gr->last()=="")&&(ui->group_table->currentIndex().row()==-1)){
                dialogEmptyRow->show();
                return;
           }
    }
    if (!(list_gr->isEmpty())){
            if ((list_gr->last()!=ui->group_table->currentIndex().data())){
                dialogConfrimEdit->show();
                return;
            }
    }
    if (!(list_gr->isEmpty())){
            if ((list_gr->last()=="")&&(ui->group_table->currentIndex().data()=="")){
                dialogEmptyRow->show();
                return;
            }
    }
       list_gr->append("");
       int index =ui->group_table->currentIndex().row()+1;
       groupModel->insertRow(index);

       const QModelIndex indexNext=groupModel->index(index,0);

       ui->group_table->setCurrentIndex(indexNext);
       visualRows(ui->group_table,groupModel);


}

void MainWindow::on_removeGroupButton_clicked()
{
    int index =ui->group_table->selectionModel()->currentIndex().row();
    this->repoGroupStudents.remove(index);
    list_gr->removeAt(index);
    ui->group_table->model()->removeRow(index);
}

void MainWindow::on_confirmGroupButton_clicked()
{
    int index = ui->group_table->selectionModel()->currentIndex().row();
    QVariant value = ui->group_table->selectionModel()->currentIndex().data();
    QString str = value.toString();

    if (str==""){
        dialogEmptyRow->show();
    }
    else{
        this->repoGroupStudents.add(str);
        list_gr->replace(index,str);
     }
}

void MainWindow::on_addCabinetsButton_clicked()
{
    dialogConfirmCabinet->show();
    dialogConfirmCabinet->clearLineEdit();
 }

void MainWindow::receiveDataCabinet(Cabinet cabinet){

     QString s = QString("%1%2%3").arg(cabinet.building).arg(cabinet.floor).arg(cabinet.number);
     repoCabinets.add(cabinet);
     list_cb->append(s);

     int index =ui->cabinets_table->currentIndex().row()+1;
     qDebug()<<"Индекс"<<index;
     cabinetModel->insertRow(index);
     const QModelIndex indexNext=cabinetModel->index(index,0);
     cabinetModel->setData(indexNext,QVariant(s));
     visualRows(ui->cabinets_table,cabinetModel);
     ui->cabinets_table->setCurrentIndex(indexNext);
     qDebug()<<"Индекс после добавления"<<ui->cabinets_table->currentIndex().row();
}
void MainWindow::on_editCabinetsButton_clicked()
{
    int index=ui->cabinets_table->selectionModel()->currentIndex().row();
    selectIndex=index;
    emit sendSelectionCabinet(repoCabinets.getById(index));
    qDebug()<<"edit called";
    qDebug()<<"Индекс"<<ui->cabinets_table->currentIndex().row();
    qDebug()<<repoCabinets.getById(index).building<<repoCabinets.getById(index).floor<<repoCabinets.getById(index).number;
    dialogConfirmCabinet->show();
}
void MainWindow::receiveEditDataCabinet(RepositoryTemplate<Cabinet> *repCabinet){
    //qDebug()<<"Работает";
    QList<Cabinet> cab_l;
    cab_l=repCabinet->getAll();

    QString s = QString::number(cab_l.back().building)+QString::number(cab_l.back().floor)+QString::number(cab_l.back().number);
    qDebug()<<"Вывод принятого репозитория";
    QList<Cabinet> cabinets_l;
        cabinets_l=repCabinet->getAll();
         foreach (Cabinet cabinet, cabinets_l) {
            qDebug()<<cabinet.floor<<"\t"<<cabinet.number<<"\t"<<cabinet.building<<"\n";
        }
     repoCabinets.update(selectIndex,repCabinet->getById(0));
     list_cb->replace(selectIndex,s);
     const QModelIndex indexNext=cabinetModel->index(selectIndex,0);
     cabinetModel->setData(indexNext,QVariant(s));
    //qDebug()<<repCabinet->getById(0).building<<repCabinet->getById(0).floor<<repCabinet->getById(0).number;
    //repoCabinets.update(selectIndex,repCabinet->getById(0));

}

void MainWindow::on_removeCabinetsButton_clicked()
{
    int r =ui->cabinets_table->selectionModel()->currentIndex().row();
    list_cb->removeAt(r);
    repoCabinets.remove(r);
    ui->cabinets_table->model()->removeRow(r);
}



void MainWindow::on_cabinets_table_doubleClicked(const QModelIndex &index)
{
     qDebug()<<index.data();
}


void MainWindow::on_addTimeButton_clicked()
{
   dialogLessonTime->show();
}

void MainWindow::on_removeTimeButton_clicked()
{
    int r =ui->time_table->selectionModel()->currentIndex().row();
    list_tm->removeAt(r);
    ui->time_table->model()->removeRow(r);
}

void MainWindow::on_confirmTimeButton_clicked()
{
    int index = ui->time_table->selectionModel()->currentIndex().row();
    QVariant value = ui->time_table->selectionModel()->currentIndex().data();
    QString str = value.toString();
    list_tm->replace(index,str);
}

void MainWindow::on_subject_table_clicked(const QModelIndex &index)
{
    QList<Subject> repSubjects;

    Subject reSubject = Subject();
    Subject moSubject=Subject();
    repSubjects = repoSubjects.getAll();

    qDebug()<<"Вывод репозитория";
    for (auto it = repSubjects.begin(); it != repSubjects.end(); ++it) {
        reSubject = *it;
        qDebug() << reSubject.name;
    }
    qDebug()<<"Вывод модели";
    for (auto it = list_s->begin(); it != list_s->end(); ++it) {
        moSubject = *it;
        qDebug() << moSubject.name;
    }
}


void MainWindow::on_group_table_clicked(const QModelIndex &index)
{

    QList<GroupStudents> list_groups;
    GroupStudents  stGrp= GroupStudents();
     GroupStudents  repoGrp= GroupStudents();

    list_groups = this->repoGroupStudents.getAll();

    //QStringList list_s;
    qDebug()<<"Вывод репозитория";
    for (auto it = list_groups.begin(); it != list_groups.end(); ++it) {
        stGrp = *it;
        qDebug() << stGrp.name;
    }
    qDebug()<<"Вывод модели";
    for (auto it = list_gr->begin(); it != list_gr->end(); ++it) {
        repoGrp = *it;
        qDebug() << repoGrp.name;
    }


}



void MainWindow::on_saveFile_triggered()
{
    this->repoCabinets.save();
    this->repoSubjects.save();
    this->repoLessonsTimes.save();
    this->repoGroupStudents.save();
}

void MainWindow::on_cabinets_table_clicked(const QModelIndex &index)
{
    QList<Cabinet> cabinets_l;
    cabinets_l=this->repoCabinets.getAll();
    qDebug()<<"Репозиторий";
    foreach (Cabinet cabinet, cabinets_l) {
        qDebug()<<cabinet.building<<"\t"<<cabinet.floor<<"\t"<<cabinet.number<<"\n";
    }
     for (int i = 0;i<list_cb->size();i++) {
        qDebug()<<list_cb->at(i);
    }
        qDebug()<<"Индекс по нажатию"<<index.row();


<<<<<<< HEAD
    }

void MainWindow::on_subject_table_entered(const QModelIndex &index)
{
    qDebug()<<"Entered";
}


void MainWindow::on_subject_table_customContextMenuRequested(const QPoint &pos)
{

=======
>>>>>>> 0ff2c780bb8abae6a363d1bad10704d78028cc48
}
