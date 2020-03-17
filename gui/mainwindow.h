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

private:
    QStringList *list_s;
    Ui::MainWindow *ui;
    RepositoryGeneral<Cabinet> repoCabinets;
    RepositoryGeneral<GroupStudents> repoGroupStudents;
    RepositoryGeneral<LessonTime> repoLessonsTimes;
    RepositoryGeneral<Subject> repoSubjects;
};

#endif // MAINWINDOW_H
