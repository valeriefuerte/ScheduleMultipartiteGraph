#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "models/router.h"
#include "models/cabinet.h"
#include "models/groupstudents.h"
#include "models/lessontime.h"
#include "models/subject.h"
#include "models/table_model.h"

#include "dialogSubjectWindow.h"
#include "dialogGroupWindow.h"
#include "dialogWindowEmptyRow.h"
#include "dialogCabinetWindow.h"
#include "dialogWindowConfrimEditRow.h"
#include "dialogLessonTimeWindow.h"



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
private:

signals:
    void sendSelectionCabinet(Cabinet cabinet);
private slots:

    //void on_tabWidget_currentChanged(int index);

    void receiveEditDataSubject(Subject);

    void receiveDataSubject(Subject);

    void receiveEditDataGroup(GroupStudents);

    void receiveDataGroup(GroupStudents);

    void receiveEditDataCabinet(Cabinet);

    void receiveDataCabinet(Cabinet);

    void slotSubjectAddRecord();

    void slotSubjectRemoveRecord();

    void slotSubjectEditRecord();

    void slotGroupAddRecord();

    void slotGroupEditRecord();

    void slotGroupRemoveRecord();

    void slotCabinetAddRecord();

    void slotCabinetEditRecord();

    void slotCabinetRemoveRecord();

    void on_addTimeButton_clicked();

    void on_removeTimeButton_clicked();

    void on_confirmTimeButton_clicked();

    void on_subject_table_clicked(const QModelIndex &index);

    void on_group_table_clicked(const QModelIndex &index);

    void on_saveFile_triggered();

    void on_cabinets_table_clicked(const QModelIndex &index);

    //Контекстные меню
    void customSubjectMenuRequested(const QPoint &pos);

    void customGroupMenuRequested(const QPoint &pos);

    void customCabinetMenuRequested(const QPoint &pos);

    //void customTimeMenuRequested(const QPoint &pos);


private:
    Ui::MainWindow *ui;

    //Модели QTableView
    QStringList *list_s;
    QStringList *list_gr;
    QStringList *list_cb;
    QStringList *list_tm;

    //Диалоговые окна
    DialogSubjectWindow *dialogSubject;
    DialogGroupWindow *dialogGroup;
    DialogWindowEmptyRow *dialogEmptyRow;
    DialogWindowConfirmEditRow *dialogConfrimEdit;
    DialogCabinetWindow *dialogCabinet;
    DialogLessonTimeWindow *dialogLessonTime;

    //Абстрактные модели QTableView
    StringListModel *subjectModel;
    StringListModel *groupModel;
    StringListModel *cabinetModel;

    //Репозитории
    RepositoryTemplate<Cabinet> repoCabinets;
    RepositoryTemplate<GroupStudents> repoGroupStudents;
    RepositoryTemplate<LessonTime> repoLessonsTimes;
    RepositoryTemplate<Subject> repoSubjects;
};

#endif // MAINWINDOW_H
