#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gui/visualizationwidget.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Router& router = Router::getInstance();
    VisualizationWidget *w = new VisualizationWidget();
    ui->tabWidget->addTab(w,"GraphWidgetDemo");
//    ui->label->setText(router.getRepository()->helloString());

    // установка оформления statusBar
//    ui->statusBar->setStyleSheet("background-color: #333; color: #33bb33");
//    ui->statusBar->setFont(QFont("Consolas", 14));
//    ui->statusBar->showMessage(tr("State: ready 0123456789"));
}

MainWindow::~MainWindow()
{
    delete ui;
}
