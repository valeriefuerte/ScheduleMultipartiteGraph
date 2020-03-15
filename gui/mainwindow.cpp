#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    Router& router = Router::getInstance();
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

void MainWindow::on_fieldsTableView_doubleClicked(const QModelIndex &index)
{


}

void MainWindow::on_tabWidget_currentChanged(int index)
{
    // Создаем репозиторий
    repositorySubjects repoSubjects = repositorySubjects();

    // Переменные куда будем записывать значения (нужны для отладки)
    QList<Subject> subjects;
    Subject subject = Subject();

    // Добавляем различные преметы
    repoSubjects.add(Subject(1, "АКЗ"));
    repoSubjects.add(Subject(2, "РЯП"));
    repoSubjects.add(Subject(3, "ООТРвПО"));
    repoSubjects.add(Subject(4, "ВиАПО"));

    // Получить все предметы
    subjects = repoSubjects.getAll();

    // Получить конкретный предмет
    subject = repoSubjects.getById(1);

    // Удалить конкретный предмет
    repoSubjects.remove(2);

    // Изменить конкретный предмет
    repoSubjects.update(3, Subject(3, "СКвПС"));
}
