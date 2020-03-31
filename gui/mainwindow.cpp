#include <QtGui>
#include <QApplication>
#include <QTableView>
#include <QTreeView>
#include <QListView>
#include <QSplitter>
#include <QHeaderView>
#include <QDebug>
#include <QAbstractTableModel>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "models/table_model.h"
#include "dialogWindowEmptyRow.h"
#include "dialogCabinetWindow.h"
#include "models/repository/repositorygeneral.h"

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
      list_s->append("");
      this->repoSubjects.add(Subject(""));
      subjectModel = new StringListModel(*list_s);
      visualRows(ui->subject_table,subjectModel);
      //Таблица "Группы"
      list_gr->append("");
      this->repoGroupStudents.add(GroupStudents(""));
      groupModel=new StringListModel(*list_gr);
      visualRows(ui->group_table,groupModel);
       //Таблица Кабинеты
      //list_cb->append("000");
      //repoCabinets.add(Cabinet());
      cabinetModel=new StringListModel(*list_cb);
      //visualRows(ui->cabinets_table,cabinetModel);

      //Инициализация диалоговых окон
      dialogEmptyRow = new DialogWindowEmptyRow();
      dialogEmptyRow->resize(300,100);

      dialogConfrimEdit = new DialogWindowConfirmEditRow();
      dialogConfrimEdit->resize(300,100);

      dialogConfirmCabinet = new DialogCabinetWindow();


      connect(dialogConfirmCabinet, SIGNAL(sendDataCabinet(RepositoryGeneral<Cabinet>*)), this,SLOT(receiveDataCabinet(RepositoryGeneral<Cabinet>*)));

      connect(dialogConfirmCabinet, SIGNAL(sendEditDataCabinet(RepositoryGeneral<Cabinet>*)), this,SLOT(receiveEditDataCabinet(RepositoryGeneral<Cabinet>*)));

      connect(this,SIGNAL(sendSelectionCabinet(Cabinet)),dialogConfirmCabinet,SLOT(receiveSelectionCabinet(Cabinet)));


//    Router& router = Router::getInstance();
//    QStringList list_s, list_tech, list_gr, list_cab, list_times;
//    list_s <<"Ин.яз"<<"АКЗ"<<"РСОС"<<"СК в ПС"<<"ООТРП";
//    list_tech <<"Комисарова"<<"Черниченко"<<"Самойленко"<<"Колянов"<<"Спицын"<<"Борисенко";
//    list_gr<<"5303"<<"5304"<<"5373"<<"5374"<<"5381";
//    list_cab<<"2122"<<"3313"<<"3404"<<"3410"<<"3413"<<"5322";

//    StringListModel *model = new StringListModel(list_s);
//    StringListModel *model1 = new StringListModel(list_tech);
//    StringListModel *model2 = new StringListModel(list_gr);
//    StringListModel *model3 = new StringListModel(list_cab);
//    ui->subject_table->setModel(model);
//    ui->teacher_table->setModel(model1);
//    ui->group_table->setModel(model2);
//    ui->cabinets_table->setModel(model3);

//    ui->subject_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
//    ui->teacher_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
//    ui->group_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
//    ui->cabinets_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);





            //setText(router.getRepository()->setHelloString());

    // установка оформления statusBar
//    ui->statusBar->setStyleSheet("background-color: #333; color: #33bb33");
      //    ui->statusBar->setFont(QFont("Consolas", 14));
//    ui->statusBar->showMessage(tr("State: ready 0123456789"));
}//

MainWindow::~MainWindow()
{
    delete ui;
}

/*void MainWindow::on_tabWidget_currentChanged(int index)
{
    // Переменные куда будем записывать значения (нужны для отладки)
    QList<Subject> subjects;
    Subject subject = Subject();

    // Добавляем различные преметы
    this->repoSubjects.add(Subject("АКЗ"));
    this->repoSubjects.add(Subject("РЯП"));
    this->repoSubjects.add(Subject("ООТРвПО"));
    this->repoSubjects.add(Subject("ВиАПО"));

    // Получить все предметы
    subjects = this->repoSubjects.getAll();

    QStringList list_s;

    for (auto it = subjects.begin(); it != subjects.end(); ++it) {
        subject = *it;
        list_s << subject.name;
    }

    StringListModel *model = new StringListModel(list_s);
    ui->subject_table->setModel(model);
    ui->subject_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);*/

//    // Получить конкретный предмет
//    subject = repoSubjects.getById(1);

//    // Удалить конкретный предмет
//    repoSubjects.remove(2);

//    // Изменить конкретный предмет
//    repoSubjects.update(3, Subject("СКвПС"));
//}

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

    this->repoSubjects.add(Subject(""));
    const QModelIndex indexNext=subjectModel->index(index,0);

    ui->subject_table->setCurrentIndex(indexNext);
    ui->subject_table->setModel(subjectModel);
    ui->subject_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);



}

void MainWindow::on_removeSubjectButton_clicked()
{

    int index =ui->subject_table->selectionModel()->currentIndex().row();
    this->repoSubjects.remove(index);
    list_s->removeAt(index);
    ui->subject_table->model()->removeRow(index);

}

void MainWindow::on_confirmSubjectButton_clicked()
{
    int index = ui->subject_table->selectionModel()->currentIndex().row();
    QVariant value = ui->subject_table->selectionModel()->currentIndex().data();
    QString str = value.toString();
    if ((index==-1)||(str=="")){
        qDebug()<<"Confirm";
        dialogEmptyRow->show();
    }
    else{
        this->repoSubjects.update(index,str);
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
       int index =ui->group_table->selectionModel()->currentIndex().row()+1;
       groupModel->insertRow(index);

       this->repoGroupStudents.add(GroupStudents(""));
       const QModelIndex indexNext=groupModel->index(index,0);

       ui->group_table->setCurrentIndex(indexNext);
       ui->group_table->setModel(groupModel);
       ui->group_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
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

    if ((index==-1)||(str=="")){
        dialogEmptyRow->show();
    }
    else{
        this->repoGroupStudents.update(index,str);
        list_gr->replace(index,str);
     }
}

void MainWindow::on_addCabinetsButton_clicked()
{
    dialogConfirmCabinet->show();
 }

void MainWindow::receiveDataCabinet(RepositoryGeneral<Cabinet> *receivedCab){
     QList<Cabinet> cab_l;
     cab_l=receivedCab->getAll();
     QString s = QString::number(cab_l.back().building)+QString::number(cab_l.back().floor)+QString::number(cab_l.back().number);
     repoCabinets.add(receivedCab->getById(0));
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
    qDebug()<<repoCabinets.getById(index).building<<repoCabinets.getById(index).floor<<repoCabinets.getById(index).number;
    dialogConfirmCabinet->show();
}
void MainWindow::receiveEditDataCabinet(RepositoryGeneral<Cabinet> *repCabinet){
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
    list_tm->append("");
    StringListModel *model = new StringListModel(*list_tm);
    ui->time_table->setModel(model);
    ui->time_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
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
    qDebug()<<ui->subject_table->cursor().pos();
    QList<Subject> subjects;
    Subject subject = Subject();
    subjects = this->repoSubjects.getAll();

    qDebug()<<"Вывод репозитория";
    for (auto it = subjects.begin(); it != subjects.end(); ++it) {
        subject = *it;
        qDebug() << subject.name;
    }
    qDebug()<<"Вывод модели";
    for (auto it = list_s->begin(); it != list_s->end(); ++it) {
        subject = *it;
        qDebug() << subject.name;
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
    }









