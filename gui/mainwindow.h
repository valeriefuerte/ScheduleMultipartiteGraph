#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "models/router.h"
#include "models/cabinet.h"
#include "models/groupstudents.h"
#include "models/lessontime.h"
#include "models/subject.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_fieldsTableView_doubleClicked(const QModelIndex &index);

    void on_tabWidget_currentChanged(int index);

private:
    Ui::MainWindow *ui;

    RepositoryGeneral<Cabinet> repoCabinets;
    RepositoryGeneral<GroupStudents> repoGroupStudents;
    RepositoryGeneral<LessonTime> repoLessonsTimes;
    RepositoryGeneral<Subject> repoSubjects;
};

#endif // MAINWINDOW_H
