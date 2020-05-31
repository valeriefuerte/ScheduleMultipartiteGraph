#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "models/router.h"
#include "models/cabinet.h"
#include "models/groupstudents.h"
#include "models/lessontime.h"
#include "models/subject.h"
#include "models/linkgroupsubject.h"

#include "models/repository/repositorytemplate.h"

#include "models/graph.h"

#include "models/tablelistmodel.h"

#include "dialogSubjectWindow.h"
#include "dialogGroupWindow.h"
#include "dialogWindowEmptyRow.h"
#include "dialogCabinetWindow.h"
#include "dialogWindowConfrimEditRow.h"
#include "dialogLessonTimeWindow.h"
#include "dialogLinkGroupSubjectWindow.h"
#include "dialogSaveAs.h"

#include "visualizationwidget.h"

#include "models/Lesson.h"
#include <QTableView>

#include "gui/schedulewidget.h"
#include "gui/visualizationwidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    Ui::MainWindow *ui;
    void testSubject();
    explicit MainWindow(QWidget *parent = nullptr);
    void  visualRows(QTableView *table,TableListModel *model);
    void loadReps();
    void loadReps(QString jsonName);
    // Инициализация хранилищ.
    void initStorage();
    ~MainWindow();
private:

    QString dirStorage = "storage";
signals:
    void sendSelectionCabinet(Cabinet cabinet);

private slots:
    //void on_tabWidget_currentChanged(int index);
    //Предметы
    void slotSubjectAddRecord();

    void slotSubjectRemoveRecord();

    void slotSubjectEditRecord();

    void receiveEditDataSubject(Subject);

    void receiveDataSubject(Subject);
    //Группы
    void slotGroupAddRecord();

    void slotGroupEditRecord();

    void slotGroupRemoveRecord();

    void receiveEditDataGroup(GroupStudents);

    void receiveDataGroup(GroupStudents);
    //Кабинет
    void slotCabinetAddRecord();

    void slotCabinetEditRecord();

    void slotCabinetRemoveRecord();

    void receiveEditDataCabinet(Cabinet);
    //Время
    void slotTimeAddRecord();

    void slotTimeEditRecord();

    void slotTimeRemoveRecord();

    void receiveDataCabinet(Cabinet);
    //Группы_предметы

    void slotAddSG();

    //Контекстные меню
    void customSubjectMenuRequested(const QPoint &pos);

    void customGroupMenuRequested(const QPoint &pos);

    void customCabinetMenuRequested(const QPoint &pos);

    void customTimeMenuRequested(const QPoint &pos);

    void customGroupSubjectMenuRequested(const QPoint &pos);

    void receiveDataLessonTime(LessonTime);

    void receiveEditDataLessonTime(LessonTime);



    void on_subject_table_clicked(const QModelIndex &index);

    void on_group_table_clicked(const QModelIndex &index);

    void on_saveFile_triggered();

    void on_saveAs_triggered();

    void on_openFile_triggered();

    void on_newFile_triggered();

    void on_deleteFile_triggered();

    void on_cabinets_table_clicked(const QModelIndex &index);

    // получение имя нового сохраненного файла
    void  receiveFileName(QString,QString,bool);

    //получение названия файла для открытия
    void receiveOpenFileName(QString,QString);

    //получение имени удаляемого файла
    void receiveDeleteFileName(QString, QString);

    //получение изменений из буфера репозитория Группы_предметы
    void receiveEditRepoLinkGrSb(RepositoryTemplate<LinkGroupSubject>);


    void on_tabWidget_tabBarClicked(int index);

    void updatatingVisualization(int index);

     QList<Lesson> transformGrapthToLessons();

public slots:
private:
    //имя файла с которым работаем
    QString curPathFile;
    //флаг для нахождения одинаковых файлов
    bool idenFlag = false;

    QHash<int,QString> receiveDay;

    //Модели QTableView
    QStringList *list_s;
    QStringList *list_gr;
    QStringList *list_cb;
    QStringList *list_tm;
    QStringList *list_gr_sub;

    //Диалоговые окна
    DialogSubjectWindow *dialogSubject;
    DialogGroupWindow *dialogGroup;
    DialogWindowEmptyRow *dialogEmptyRow;
    DialogWindowConfirmEditRow *dialogConfrimEdit;
    DialogCabinetWindow *dialogCabinet;
    DialogLessonTimeWindow *dialogLessonTime;
    DialogLinkGroupSubjectWindow *dialogLinkGroupSubject;

    //Абстрактные модели QTableView
    TableListModel *subjectModel;
    TableListModel *groupModel;
    TableListModel *cabinetModel;
    TableListModel *timeModel;
    TableListModel *gr_subModel;

    //Репозитории
    RepositoryTemplate<Cabinet> repoCabinets;
    RepositoryTemplate<GroupStudents> repoGroupStudents;
    RepositoryTemplate<LessonTime> repoLessonTime;
    RepositoryTemplate<Subject> repoSubjects;
    RepositoryTemplate<LinkGroupSubject> repoLinkGroupSubject;

   //Виджеты
    ScheduleWidget *schedueWidget;
    VisualizationWidget *graphWidget;

    // Графа, двумерный Лист, строки это путь {groupId -> subjectId -> cabinetId -> lessonTimeId}
    QList<QList<int>> graph;
    //метод загрузки модели по файлу
    void loadModelonRepo();
    //диалоговое окно работы с файлами
    DialogSaveAs *dSaveAs;
    //очищение TableView
    void clearTableView(QTableView*, TableListModel*);
    //загрузка по выбранному файлу
    void loadOnSelectedFile(QString,QString);
    //очищение моделей
    void clearModel();
    //очищение репозиториев
    void clearRepository();
    //проверка на сопадения предметы, группы
    int  checkidenticalDataRepo(QString =nullptr);
    //проверка на сопадения кабинеты
    int  checkidenticalDataCabinets(Cabinet);
    //проверка на сопадения время
    int  checkidenticalDataTime(LessonTime);


};

#endif // MAINWINDOW_H
