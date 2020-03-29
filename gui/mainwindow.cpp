#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "models/table_model.h"
#include <QtGui>
#include <QApplication>
#include <QTableView>
#include <QTreeView>
#include <QListView>
#include <QSplitter>
#include <QHeaderView>
#include <QDebug>
#include <QAbstractTableModel>
QStringList *list_s = new QStringList();
QStringList *list_gr = new QStringList();
QStringList *list_cb=new QStringList();
QStringList *list_tm = new QStringList();

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
      ui->setupUi(this);
      /*connect(ui->addSubjectButton,SIGNAL(clicked()),this,SLOT(on_addSubjectButton_clicked()));
      connect(ui->confirmSubjectButton,SIGNAL(clicked()),this,SLOT(on_confirmSubjectButton_clicked()));
      connect(ui->removeSubjectButton,SIGNAL(clicked()),this,SLOT(on_removeSubjectButton_clicked()));
      connect(ui->subject_table,SIGNAL(DoubleClicked(index)),this,SLOT(on_subject_table_doubleClicked(index)));*/



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


void MainWindow::on_addSubjectButton_clicked()
{
    list_s->append("");
    this->repoSubjects.add(Subject(""));
    StringListModel *model = new StringListModel(*list_s);
    ui->subject_table->setModel(model);
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
    this->repoSubjects.update(index,str);
    list_s->replace(index,str);
}

void MainWindow::on_addGroupButton_clicked()
{
    list_gr->append("");
    this->repoGroupStudents.add(GroupStudents(""));
    StringListModel *model = new StringListModel(*list_gr);
    ui->group_table->setModel(model);
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
    this->repoGroupStudents.update(index,str);
    list_gr->replace(index,str);
}

void MainWindow::on_addCabinetsButton_clicked()
{
    list_cb->append("");
    StringListModel *model = new StringListModel(*list_cb);
    ui->cabinets_table->setModel(model);
    ui->cabinets_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void MainWindow::on_removeCabinetsButton_clicked()
{
    int r =ui->cabinets_table->selectionModel()->currentIndex().row();
    list_cb->removeAt(r);
    ui->cabinets_table->model()->removeRow(r);
}

void MainWindow::on_confirmCabinetsButton_clicked()
{
    int index = ui->cabinets_table->selectionModel()->currentIndex().row();
    QVariant value = ui->cabinets_table->selectionModel()->currentIndex().data();
    QString str = value.toString();
    list_cb->replace(index,str);
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
    //int in = ui->group_table->selectionModel()->currentIndex().row();

    // Переменные куда будем записывать значения (нужны для отладки)
    QList<Subject> subjects;
    Subject subject = Subject();

    // Добавляем различные преметы
    /*this->repoSubjects.add(Subject("АКЗ"));
    this->repoSubjects.add(Subject("РЯП"));
    this->repoSubjects.add(Subject("ООТРвПО"));
    this->repoSubjects.add(Subject("ВиАПО"));
    Subject sub = Subject();
    sub =this->repoSubjects.getById(1);
    QString t = sub.name;
    qDebug()<<"Получить по id"<<t;
    // Получить все предметы*/
    subjects = this->repoSubjects.getAll();

    QStringList list_s;
    qDebug()<<"Вывод всех";
    for (auto it = subjects.begin(); it != subjects.end(); ++it) {
        subject = *it;
        qDebug() << subject.name;
    }


    /*QList<Subject> subjects;
    Subject subject = Subject();

    // Получить все предметы
    subjects = this->repoSubjects.getAll();

    QStringList list_s;

    for (auto it = subjects.begin(); it != subjects.end(); ++it) {
        subject = *it;
        qDebug() << subject.name;*/
    //}

}

void MainWindow::on_group_table_clicked(const QModelIndex &index)
{
    QList<GroupStudents> group;
    GroupStudents groups = GroupStudents();
    group = this->repoGroupStudents.getAll();

        qDebug()<<"Вывод всех";
        for (auto it = group.begin(); it != group.end(); ++it) {
            groups = *it;
            qDebug() << groups.name;
        }

}
