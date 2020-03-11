#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gui/graphwidget.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Router& router = Router::getInstance();
    //    ui->label->setText(router.getRepository()->helloString());

    // установка оформления statusBar
    //    ui->statusBar->setStyleSheet("background-color: #333; color: #33bb33");
    //    ui->statusBar->setFont(QFont("Consolas", 14));
    //    ui->statusBar->showMessage(tr("State: ready 0123456789"));
    GraphWidget *ww = new GraphWidget();

    ui->tabWidget->addTab(ww,"GRAPH");
}

MainWindow::~MainWindow()
{
    delete ui;
}
