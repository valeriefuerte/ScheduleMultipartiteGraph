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

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
      ui->setupUi(this);
      /*connect(ui->addButton,SIGNAL(pressed()),this,SLOT(on_addButton_pressed()));
      connect(ui->confirmButton,SIGNAL(clicked()),this,SLOT(on_confirmButton_clicked()));
      connect(ui->deleteButton,SIGNAL(clicked()),this,SLOT(on_deleteButton_clicked()));
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


/*void MainWindow::on_button_listener(){

    QPushButton *button = (QPushButton *)sender();
    if (QString(button->objectName())=="addButton"){
        list_s->append("");
        StringListModel *model = new StringListModel(*list_s);
        ui->subject_table->setModel(model);
        ui->subject_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    }
    if ((QString)button->objectName()=="confirmButton"){
        //QModelIndex f = model->index(0,0);
        //QVariant value = f.sibling(f.row(),f.column()).data();
        //int r =ui->subject_table->selectionModel()->currentIndex().row();
        //model->setData(f,value);
        int index = ui->subject_table->selectionModel()->currentIndex().row();
        QVariant value = ui->subject_table->selectionModel()->currentIndex().data();
        qDebug()<<ui->subject_table->selectionModel()->currentIndex().row();
        QString str = value.toString();
        list_s->replace(index,str);
       //qDebug()<<model->data(f,Qt::UserRole);
       //list_s->append(str);

    }

}*/



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
    StringListModel *model = new StringListModel(*list_s);
    ui->subject_table->setModel(model);
    ui->subject_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void MainWindow::on_removeSubjectButton_clicked()
{
    //qDebug()<<"Размер перед list удаление:"<<list_s->length();
    //qDebug()<<"Число строк перед удалением"<<ui->subject_table->model()->rowCount();
    int r =ui->subject_table->selectionModel()->currentIndex().row();
    //int c = ui->subject_table->selectionModel()->currentIndex().column();
    list_s->removeAt(r);
    ui->subject_table->model()->removeRow(r);
    //qDebug()<<"размер list после удаления:"<<list_s->length();
    //qDebug()<<"Число строк после удаления"<<ui->subject_table->model()->rowCount();


}

void MainWindow::on_confirmSubjectButton_clicked()
{
    int index = ui->subject_table->selectionModel()->currentIndex().row();
    QVariant value = ui->subject_table->selectionModel()->currentIndex().data();
    qDebug()<<ui->subject_table->selectionModel()->currentIndex().row();
    QString str = value.toString();
    list_s->replace(index,str);
}
