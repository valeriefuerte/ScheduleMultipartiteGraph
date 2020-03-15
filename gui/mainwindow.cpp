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


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Router& router = Router::getInstance();
    QStringList list_s, list_tech, list_gr, list_cab, list_times;
    list_s <<"Ин.яз"<<"АКЗ"<<"РСОС"<<"СК в ПС"<<"ООТРП";
    list_tech <<"Комисарова"<<"Черниченко"<<"Самойленко"<<"Колянов"<<"Спицын"<<"Борисенко";
    list_gr<<"5303"<<"5304"<<"5373"<<"5374"<<"5381";
    list_cab<<"2122"<<"3313"<<"3404"<<"3410"<<"3413"<<"5322";

    StringListModel *model = new StringListModel(list_s);
    StringListModel *model1 = new StringListModel(list_tech);
    StringListModel *model2 = new StringListModel(list_gr);
    StringListModel *model3 = new StringListModel(list_cab);
    ui->subject_table->setModel(model);
    ui->teacher_table->setModel(model1);
    ui->group_table->setModel(model2);
    ui->cabinets_table->setModel(model3);

    ui->subject_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->teacher_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->group_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->cabinets_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);




    // установка оформления statusBar
//    ui->statusBar->setStyleSheet("background-color: #333; color: #33bb33");
//    ui->statusBar->setFont(QFont("Consolas", 14));
//    ui->statusBar->showMessage(tr("State: ready 0123456789"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

