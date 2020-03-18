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

    //void on_tabWidget_currentChanged(int index);


    void on_addSubjectButton_clicked();

    void on_removeSubjectButton_clicked();

    void on_confirmSubjectButton_clicked();

    void on_addGroupButton_clicked();

    void on_removeGroupButton_clicked();

    void on_confirmGroupButton_clicked();

    void on_addCabinetsButton_clicked();

    void on_removeCabinetsButton_clicked();

    void on_confirmCabinetsButton_clicked();

    void on_addTimeButton_clicked();

    void on_removeTimeButton_clicked();

    void on_confirmTimeButton_clicked();

private:
    Ui::MainWindow *ui;
    RepositoryGeneral<Cabinet> repoCabinets;
    RepositoryGeneral<GroupStudents> repoGroupStudents;
    RepositoryGeneral<LessonTime> repoLessonsTimes;
    RepositoryGeneral<Subject> repoSubjects;
};

#endif // MAINWINDOW_H
