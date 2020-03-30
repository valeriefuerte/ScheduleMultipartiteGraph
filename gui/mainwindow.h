#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "models/router.h"
#include "models/cabinet.h"
#include "models/groupstudents.h"
#include "models/lessontime.h"
#include "models/subject.h"
#include "dialogWindowEmptyRow.h"
#include "gui/dialogCabinetWindow.h";
#include "gui/dialogWindowConfrimEditRow.h"
#include "models/table_model.h"
#include <QTableView>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    void  visualRows(QTableView *table,StringListModel *model);
    ~MainWindow();
signals:
    //void sendSelectionCabinet(Cabinet cabinet);
private slots:

    //void on_tabWidget_currentChanged(int index);

    void receiveDataCabinet(RepositoryGeneral<Cabinet> *repcabinet);

    void on_addSubjectButton_clicked();

    void on_removeSubjectButton_clicked();

    void on_confirmSubjectButton_clicked();

    void on_addGroupButton_clicked();

    void on_removeGroupButton_clicked();

    void on_confirmGroupButton_clicked();

    void on_addCabinetsButton_clicked();

    void on_removeCabinetsButton_clicked();


    void on_addTimeButton_clicked();

    void on_removeTimeButton_clicked();

    void on_confirmTimeButton_clicked();

    void on_subject_table_clicked(const QModelIndex &index);

    void on_group_table_clicked(const QModelIndex &index);



    void on_cabinets_table_clicked(const QModelIndex &index);

    void on_cabinets_table_doubleClicked(const QModelIndex &index);


    void on_editCabinetsButton_clicked();

private:
    Ui::MainWindow *ui;

    //Модели QTableView
    QStringList *list_s;
    QStringList *list_gr;
    QStringList *list_cb;
    QStringList *list_tm;

    //Диалоговые окна
    DialogWindowEmptyRow *dialogEmptyRow;
    DialogWindowConfirmEditRow *dialogConfrimEdit;
    DialogCabinetWindow *dialogConfirmCabinet;

    //Абстрактные модели QTableView
    StringListModel *subjectModel;
    StringListModel *groupModel;
    StringListModel *cabinetModel;

    //Репозитории
    RepositoryGeneral<Cabinet> repoCabinets;
    RepositoryGeneral<GroupStudents> repoGroupStudents;
    RepositoryGeneral<LessonTime> repoLessonsTimes;
    RepositoryGeneral<Subject> repoSubjects;
};

#endif // MAINWINDOW_H
