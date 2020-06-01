#include <QtGui>
#include <QApplication>
#include <QTableView>
#include <QTreeView>
#include <QListView>
#include <QSplitter>
#include <QHeaderView>
#include <QDebug>
#include <QAbstractTableModel>
#include <QTime>
#include <QMessageBox>
#include "mainwindow.h"
#include "dialogSaveAs.h"
#include "ui_mainwindow.h"

#include "models/tablelistmodel.h"
#include "dialogWindowEmptyRow.h"
#include "dialogCabinetWindow.h"
#include "models/repository/repositorytemplate.h"
#include "gui/dialogLessonTimeWindow.h"

#include "gui/group_subject.h"
#include "models/linkgroupsubject.h"
#include "gui/dialogLinkGroupSubjectWindow.h"
#include "gui/scheduletableview.h"


#include "models/scheduletableabstractmodule.h"
#include "models/scheduefilterproxymodel.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    receiveDay[1]="Понедельник";
    receiveDay[2]="Вторник";
    receiveDay[3]="Среда";
    receiveDay[4]="Четверг";
    receiveDay[5]="Пятница";
    receiveDay[6]="Суббота";


    receiveDay[1]="Понедельник";
    receiveDay[2]="Вторник";
    receiveDay[3]="Среда";
    receiveDay[4]="Четверг";
    receiveDay[5]="Пятница";
    receiveDay[6]="Суббота";

    //Инициализация моделей QTableView
    list_s = new QStringList();
    list_gr = new QStringList();
    list_cb=new QStringList();
    list_tm = new QStringList();

    //Начальная визуализация QTableViewsendGroupStudents
    //Таблица "Предметы"
    subjectModel = new TableListModel(*list_s);
    ui->subject_table->setContextMenuPolicy(Qt::CustomContextMenu);

    //Таблица "Группы"
    groupModel=new TableListModel(*list_gr);
    ui->group_table->setContextMenuPolicy(Qt::CustomContextMenu);

    //Таблица Кабинеты
    cabinetModel=new TableListModel(*list_cb);
    ui->cabinets_table->setContextMenuPolicy(Qt::CustomContextMenu);

    //Таблица время
    timeModel = new TableListModel(*list_tm);
    ui->time_table->setContextMenuPolicy(Qt::CustomContextMenu);

    //Таблица группы_дисциплины
    gr_subModel = new TableListModel(*list_gr);
    ui->gr_sub_table->setContextMenuPolicy(Qt::CustomContextMenu);

    dialogSubject = new DialogSubjectWindow();
    dialogGroup = new DialogGroupWindow();
    dialogCabinet = new DialogCabinetWindow();
    dialogLessonTime = new DialogLessonTimeWindow();
    dialogLinkGroupSubject = new DialogLinkGroupSubjectWindow();

    dialogConfrimEdit = new DialogWindowConfirmEditRow();
    dialogConfrimEdit->resize(300,100);


    /*qDebug()<<repoSubjects.getAmount();
      qDebug()<<repoGroupStudents.getAmount();
      qDebug()<<repoCabinets.getAmount();
      qDebug()<<repoLessonTime.getAmount();
      qDebug()<<dialogLinkGroupSubject->repoLinkGroupSubjects.getAmount();
      */

    this->initStorage();

    // диалоговое окно для работы с файлами
    dSaveAs = new DialogSaveAs();

    this->loadReps();
    //testSubject();



    //Таблица Предметы
    connect(dialogSubject, SIGNAL(sendDataSubject(Subject)), this, SLOT(receiveDataSubject(Subject)));

    connect(dialogSubject, SIGNAL(sendEditDataSubject(Subject)), this,SLOT(receiveEditDataSubject(Subject)));

    connect(ui->subject_table,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(customSubjectMenuRequested(QPoint)));
    //Таблица Группы
    connect(dialogGroup, SIGNAL(sendDataGroup(GroupStudents)), this, SLOT(receiveDataGroup(GroupStudents)));

    connect(dialogGroup, SIGNAL(sendEditDataGroup(GroupStudents)), this,SLOT(receiveEditDataGroup(GroupStudents)));

    connect(ui->group_table,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(customGroupMenuRequested(QPoint)));
    //Таблица Кабинеты
    connect(dialogCabinet, SIGNAL(sendDataCabinet(Cabinet)), this, SLOT(receiveDataCabinet(Cabinet)));

    connect(dialogCabinet, SIGNAL(sendEditDataCabinet(Cabinet)), this,SLOT(receiveEditDataCabinet(Cabinet)));

    connect(ui->cabinets_table,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(customCabinetMenuRequested(QPoint)));
    //Таблица Время
    connect(dialogLessonTime, SIGNAL(sendDataLessonTime(LessonTime)), this, SLOT(receiveDataLessonTime(LessonTime)));

    connect(dialogLessonTime, SIGNAL(sendEditDataLessonTime(LessonTime)), this,SLOT(receiveEditDataLessonTime(LessonTime)));

    connect(ui->time_table,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(customTimeMenuRequested(QPoint)));
    //Таблица Группы_Предметы
    connect(ui->gr_sub_table,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(customGroupSubjectMenuRequested(QPoint)));

    //получение имени нового файла
    connect(dSaveAs,SIGNAL(sendFileName(QString,QString,bool)),this,SLOT(receiveFileName(QString,QString,bool)));

    //получение имени файла для открытия
    connect(dSaveAs,SIGNAL(sendSelectedFileName(QString,QString)),this,SLOT(receiveOpenFileName(QString, QString)));

    //получение имени файла для удаления
    connect(dSaveAs,SIGNAL(sendDeleteFileName(QString,QString)),this,SLOT(receiveDeleteFileName(QString,QString)));
    // получение изменений репозитория repoLinkGroupSubject
    connect(dialogLinkGroupSubject,SIGNAL(editMainRepoLinkGroupSubject(RepositoryTemplate<LinkGroupSubject>)),this,SLOT(receiveEditRepoLinkGrSb(RepositoryTemplate<LinkGroupSubject>)));

    //    qDebug() << "Кабинеты: " << endl;
    //    for (auto it = this->repoCabinets.begin(), end = this->repoCabinets.end(); it < end; ++it) {
    //        auto element = *it;
    //        qDebug() << element.toString() << endl;
    //    }

    //    qDebug() << endl << "Время: " << endl;
    //    for (auto it = this->repoLessonsTimes.begin(), end = this->repoLessonsTimes.end(); it < end; ++it) {
    //        auto element = *it;
    //        qDebug() << element.toString() << endl;
    //    }

    //    qDebug() << endl << "Группы: " << endl;
    //    for (auto it = this->repoGroupStudents.begin(), end = this->repoGroupStudents.end(); it < end; ++it) {
    //        auto element = *it;
    //        qDebug() << element.toString() << endl;
    //    }

    //    qDebug() << endl << "Дисциплины: " << endl;
    //    for (auto it = this->repoSubjects.begin(), end = this->repoSubjects.end(); it < end; ++it) {
    //        auto element = *it;
    //        qDebug() << element.toString() << endl;
    //    }

    //    auto s = this->repoSubjects.getById(2);
    //    qDebug() << "Получение по id" << endl;
    //    qDebug() << s.toString() << endl;

    //    qDebug() << "Получение по параметрам" << endl;
    //    for (auto e : this->repoSubjects.getByParameters(Subject("йцуйцу"))) {
    //        qDebug() << e.toString() << endl;
    //    }

    //    qDebug() << "Добавление элемента 'Новый элемент'" << endl;
    //    this->repoSubjects.add(Subject("Новый элемент"));
    //    qDebug() << endl << "Дисциплины: " << endl;
    //    for (auto e : this->repoSubjects.getAll()) {
    //        qDebug() << e.toString() << endl;
    //    }

    //    qDebug() << "Изменение элемента 'Новый элемент' на 'Измененный элемент'" << endl;
    //    this->repoSubjects.update(4, Subject("Измененный элемент"));
    //    qDebug() << endl << "Дисциплины: " << endl;
    //    for (auto e : this->repoSubjects.getAll()) {
    //        qDebug() << e.toString() << endl;
    //    }

    //    qDebug() << "Удаление элемента 'Измененный элемент'" << endl;
    //    this->repoSubjects.remove(4);
    //    qDebug() << endl << "Дисциплины: " << endl;
    //    for (auto e : this->repoSubjects.getAll()) {
    //        qDebug() << e.toString() << endl;
    //    }

    //MY VERSION

    // Расписние
    //    QList<TestLesson> planetList;
    //    planetList.append(TestLesson("Jupiter", 23.1, 1.326));
    //    planetList.append(TestLesson("Saturn", 9.0, 0.687));
    //    planetList.append(TestLesson("Uranus", 	8.7, 1.271));
    //    planetList.append(TestLesson("Neptune", 11.0, 1.638));
    //    planetList.append(TestLesson("Earth", 9.8, 5.514));
    //    planetList.append(TestLesson("Venus", 8.9, 5.243));
    //    planetList.append(TestLesson("Mars", 3.7, 3.933));
    //    planetList.append(TestLesson("Mercury", 3.7, 5.427));

    //    QList<TestLesson> planetList2;
    //    planetList2.append(TestLesson("J", 23.1, 1.326));
    //    planetList2.append(TestLesson("S", 9.0, 0.687));
    //    planetList2.append(TestLesson("U", 	8.7, 1.271));
    //    planetList2.append(TestLesson("N", 11.0, 1.638));
    //    planetList2.append(TestLesson("E", 9.8, 5.514));
    //    planetList2.append(TestLesson("V", 8.9, 5.243));
    //    planetList2.append(TestLesson("M", 3.7, 3.933));
    //    planetList2.append(TestLesson("Me", 3.7, 5.427));

    //    ScheduleTableAbstractModule *model = new ScheduleTableAbstractModule(planetList);
    //    ScheduleTableAbstractModule *model2 = new ScheduleTableAbstractModule(planetList2);
    schedueWidget = new ScheduleWidget (nullptr,this);
    ui->tabWidget->addTab(schedueWidget,"Расписание");
    //ui->tabWidget->currentIndex();

    //connect(tabWidget,SIGNAL(currentChanged(int)),this,SLOT())



    // Виджет визуализации графа
    graphWidget = new VisualizationWidget();
    ui->tabWidget->addTab(graphWidget,"Визуализация графа");

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::visualRows(QTableView *table, TableListModel *model){
    table->setModel(model);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void MainWindow::slotSubjectAddRecord()
{
    dialogSubject->addTitle();
    dialogSubject->clearLineEdit();
    dialogSubject->show();
}
void MainWindow::slotSubjectEditRecord()
{
    dialogSubject->show();
    dialogSubject->editTitle();
    dialogSubject->outputEditData(repoSubjects.getById(repoSubjects.getByIndex(ui->subject_table->selectionModel()->currentIndex().row()).id));
}
void MainWindow::slotSubjectRemoveRecord()
{
    int index =ui->subject_table->selectionModel()->currentIndex().row();

    dialogLinkGroupSubject->delOnSubofLinkGroupSubject(repoSubjects.getByIndex(index).id);
    repoSubjects.remove(repoSubjects.getByIndex(index).id);

    list_s->removeAt(index);
    ui->subject_table->model()->removeRow(index);
}

void MainWindow::receiveDataSubject(Subject subject){
    if (checkidenticalDataRepo(subject.name)!=1){
        repoSubjects.add(subject);
        list_s->append(subject.name);

        int index =subjectModel->rowCount();
        subjectModel->insertRow(index);

        const QModelIndex indexNext=subjectModel->index(index,0);
        subjectModel->setData(indexNext,QVariant(subject.name));
        visualRows(ui->subject_table,subjectModel);
        ui->subject_table->setCurrentIndex(indexNext);

        dialogSubject->close();
    }
}

void MainWindow::receiveEditDataSubject(Subject subject){

    int index =ui->subject_table->selectionModel()->currentIndex().row();

    list_s->replace(index,subject.name);
    repoSubjects.update(repoSubjects.getById(repoSubjects.getByIndex(index).id).id,subject.name);

    const QModelIndex curSelectIndex=subjectModel->index(index,0);
    subjectModel->setData(curSelectIndex,QVariant(subject.name));

    dialogSubject->close();
}
void MainWindow::customSubjectMenuRequested(const QPoint &pos)
{
    QMenu *menu = new QMenu(this);


    QAction *addSubject = new QAction(("Добавить"),this);
    QAction *editSubject = new QAction(("Редактировать"),this);
    QAction *deleteSubject = new QAction(("Удалить"),this);


    connect(addSubject, SIGNAL(triggered()),this,SLOT(slotSubjectAddRecord()));
    connect(editSubject, SIGNAL(triggered()),this,SLOT(slotSubjectEditRecord()));
    connect(deleteSubject, SIGNAL(triggered()),this,SLOT(slotSubjectRemoveRecord()));

    if (list_s->isEmpty()){
        menu->addAction(addSubject);
    }
    else
    {
        menu->addAction(addSubject);
        menu->addAction(editSubject);
        menu->addAction(deleteSubject);
    }
    menu->popup(ui->subject_table->viewport()->mapToGlobal(pos));
}

void MainWindow::slotGroupAddRecord()
{
    dialogGroup->addTitle();
    dialogGroup->clearLineEdit();
    dialogGroup->show();
}

void MainWindow::slotGroupEditRecord()
{
    dialogGroup->show();
    dialogGroup->editTitle();
    dialogGroup->outputEditData(repoGroupStudents.getById(repoGroupStudents.getByIndex(ui->group_table->selectionModel()->currentIndex().row()).id));

}

void MainWindow::slotGroupRemoveRecord()
{
    int index =ui->group_table->selectionModel()->currentIndex().row();


    dialogLinkGroupSubject->delOnGrofLinkGroupSubject(repoGroupStudents.getByIndex(index).id);

    this->repoGroupStudents.remove(repoGroupStudents.getByIndex(index).id);

    list_gr->removeAt(index);
    ui->group_table->model()->removeRow(index);
    ui->gr_sub_table->model()->removeRow(index);
}


void MainWindow::receiveDataGroup(GroupStudents group){
    if (checkidenticalDataRepo(group.name)!=1){
        repoGroupStudents.add(group);
        list_gr->append(group.name);

        int index =groupModel->rowCount();
        groupModel->insertRow(index);
        gr_subModel->insertRow(index);

        const QModelIndex indexNext=groupModel->index(index,0);
        groupModel->setData(indexNext,QVariant(group.name));
        gr_subModel->setData(indexNext,QVariant(group.name));

        visualRows(ui->group_table,groupModel);
        visualRows(ui->gr_sub_table,gr_subModel);

        ui->group_table->setCurrentIndex(indexNext);
        ui->gr_sub_table->setCurrentIndex(indexNext);

        dialogGroup->close();
    }
}

void MainWindow::receiveEditDataGroup(GroupStudents group){

    int index =ui->group_table->selectionModel()->currentIndex().row();

    list_gr->replace(index,group.name);
    repoGroupStudents.update(repoGroupStudents.getById(repoGroupStudents.getByIndex(index).id).id,group.name);

    const QModelIndex curSelectIndex=groupModel->index(index,0);
    groupModel->setData(curSelectIndex,QVariant(group.name));
    gr_subModel->setData(curSelectIndex,QVariant(group.name));

    dialogGroup->close();
}

void MainWindow::customGroupMenuRequested(const QPoint &pos){

    QMenu *menu = new QMenu(this);

    QAction *addGroup = new QAction(("Добавить"),this);
    QAction *editGroup = new QAction(("Редактировать"),this);
    QAction *deleteGroup = new QAction(("Удалить"),this);

    connect(addGroup, SIGNAL(triggered()),this,SLOT(slotGroupAddRecord()));
    connect(editGroup, SIGNAL(triggered()),this,SLOT(slotGroupEditRecord()));
    connect(deleteGroup, SIGNAL(triggered()),this,SLOT(slotGroupRemoveRecord()));

    if (list_gr->isEmpty()){
        menu->addAction(addGroup);
    }
    else
    {
        menu->addAction(addGroup);
        menu->addAction(editGroup);
        menu->addAction(deleteGroup);
    }
    menu->popup(ui->group_table->viewport()->mapToGlobal(pos));


}

void MainWindow::slotCabinetAddRecord()
{
    dialogCabinet->addTitle();
    dialogCabinet->clearLineEdit();
    dialogCabinet->show();
}
void MainWindow::slotCabinetEditRecord()
{
    dialogCabinet->show();
    dialogCabinet->editTitle();
    dialogCabinet->outputEditData(repoCabinets.getById(repoCabinets.getByIndex(ui->cabinets_table->selectionModel()->currentIndex().row()).id));
}
void MainWindow::slotCabinetRemoveRecord()
{
    int index =ui->cabinets_table->selectionModel()->currentIndex().row();
    list_cb->removeAt(index);
    repoCabinets.remove(repoCabinets.getById(repoCabinets.getByIndex(index).id).id);
    ui->cabinets_table->model()->removeRow(index);
}
void MainWindow::receiveDataCabinet(Cabinet cabinet){
    if (checkidenticalDataCabinets(cabinet)!=1){
        QString s = QString("%1%2%3").arg(cabinet.building).arg(cabinet.floor).arg(cabinet.number);
        repoCabinets.add(cabinet);
        list_cb->append(s);
        int index =cabinetModel->rowCount();

        cabinetModel->insertRow(index);
        const QModelIndex indexNext=cabinetModel->index(index,0);
        cabinetModel->setData(indexNext,QVariant(s));
        visualRows(ui->cabinets_table,cabinetModel);
        ui->cabinets_table->setCurrentIndex(indexNext);

        dialogCabinet->close();
    }
}
void MainWindow::receiveEditDataCabinet(Cabinet cabinet){

    int index =ui->cabinets_table->selectionModel()->currentIndex().row();

    QString s = QString("%1%2%3").arg(cabinet.building).arg(cabinet.floor).arg(cabinet.number);
    list_cb->replace(index,s);
    repoCabinets.update(repoCabinets.getById(repoCabinets.getByIndex(index).id).id,cabinet);

    const QModelIndex curSelectIndex=cabinetModel->index(ui->cabinets_table->selectionModel()->currentIndex().row(),0);
    cabinetModel->setData(curSelectIndex,QVariant(s));


    dialogCabinet->close();
}

void MainWindow::customCabinetMenuRequested(const QPoint &pos){

    QMenu *menu = new QMenu(this);

    QAction *addCabinet = new QAction(("Добавить"),this);
    QAction *editCabinet = new QAction(("Редактировать"),this);
    QAction *deleteCabinet = new QAction(("Удалить"),this);

    connect(addCabinet, SIGNAL(triggered()),this,SLOT(slotCabinetAddRecord()));
    connect(editCabinet, SIGNAL(triggered()),this,SLOT(slotCabinetEditRecord()));
    connect(deleteCabinet, SIGNAL(triggered()),this,SLOT(slotCabinetRemoveRecord()));
    if (list_cb->isEmpty()){
        menu->addAction(addCabinet);
    }
    else
    {
        menu->addAction(addCabinet);
        menu->addAction(editCabinet);
        menu->addAction(deleteCabinet);
    }

    menu->popup(ui->cabinets_table->viewport()->mapToGlobal(pos));
}

void MainWindow::slotTimeAddRecord()
{
    dialogLessonTime->show();
    dialogLessonTime->addTitle();
    dialogLessonTime->clearLineEdit();
}
void MainWindow::slotTimeEditRecord()
{
    dialogLessonTime->show();
    dialogLessonTime->editTitle();
    dialogLessonTime->outputEditData(repoLessonTime.getById(repoLessonTime.getByIndex(ui->time_table->selectionModel()->currentIndex().row()).id));
}
void MainWindow::slotTimeRemoveRecord()
{
    int index =ui->time_table->selectionModel()->currentIndex().row();
    list_tm->removeAt(index);
    repoLessonTime.remove(repoLessonTime.getById(repoLessonTime.getByIndex(index).id).id);
    ui->time_table->model()->removeRow(index);
}

void MainWindow::customTimeMenuRequested(const QPoint &pos){

    QMenu *menu = new QMenu(this);

    QAction *addTime = new QAction(("Добавить"),this);
    QAction *editTime = new QAction(("Редактировать"),this);
    QAction *deleteTime = new QAction(("Удалить"),this);

    connect(addTime, SIGNAL(triggered()),this,SLOT(slotTimeAddRecord()));
    connect(editTime, SIGNAL(triggered()),this,SLOT(slotTimeEditRecord()));
    connect(deleteTime, SIGNAL(triggered()),this,SLOT(slotTimeRemoveRecord()));
    if (list_tm->isEmpty()){
        menu->addAction(addTime);
    }
    else
    {
        menu->addAction(addTime);
        menu->addAction(editTime);
        menu->addAction(deleteTime);
    }
    menu->popup(ui->time_table->viewport()->mapToGlobal(pos));
}

void MainWindow::receiveDataLessonTime(LessonTime lessonTime){

    if (checkidenticalDataTime(lessonTime)!=1){
        QString s = QString("Четность:%1 %2 Время:%3").arg(lessonTime.parity).arg(receiveDay[lessonTime.dayOfWeek]).arg(lessonTime.time.toString());

        repoLessonTime.add(lessonTime);
        list_tm->append(s);
        int index =timeModel->rowCount();

        timeModel->insertRow(index);
        const QModelIndex indexNext=timeModel->index(index,0);
        timeModel->setData(indexNext,QVariant(s));
        visualRows(ui->time_table,timeModel);
        ui->time_table->setCurrentIndex(indexNext);

        dialogLessonTime->close();
    }

}
void MainWindow::receiveEditDataLessonTime(LessonTime lessonTime){

    int index =ui->time_table->selectionModel()->currentIndex().row();

    QString s = QString("Четность:%1 %2 Время:%3").arg(lessonTime.parity).arg(receiveDay[lessonTime.dayOfWeek]).arg(lessonTime.time.toString());
    list_tm->replace(repoLessonTime.getById(repoLessonTime.getByIndex(index).id).id,s);
    repoLessonTime.update(repoLessonTime.getById(repoLessonTime.getByIndex(index).id).id,lessonTime);

    const QModelIndex curSelectIndex=timeModel->index(ui->time_table->selectionModel()->currentIndex().row(),0);
    timeModel->setData(curSelectIndex,QVariant(s));

    dialogLessonTime->close();
}


void MainWindow::customGroupSubjectMenuRequested(const QPoint &pos){

    QMenu *menu = new QMenu(this);

    QAction *addSG= new QAction(("Соотнести"),this);

    connect(addSG, SIGNAL(triggered()),this,SLOT(slotAddSG()));

    menu->addAction(addSG);
    menu->popup( ui->gr_sub_table->viewport()->mapToGlobal(pos));

}

void MainWindow::slotAddSG(){
    dialogLinkGroupSubject->receiveGroup(ui->gr_sub_table->selectionModel()->currentIndex().row(),*list_s,repoGroupStudents,repoSubjects);
    dialogLinkGroupSubject->show();
    qDebug()<<"Репозиторий групп_предметов";
    for (int i=0; i<repoLinkGroupSubject.getAmount();i++){
        qDebug()<<repoLinkGroupSubject.getById(repoLinkGroupSubject.getByIndex(i).id).groupId<<
                  repoLinkGroupSubject.getById(repoLinkGroupSubject.getByIndex(i).id).subjectId
               <<repoLinkGroupSubject.getById(repoLinkGroupSubject.getByIndex(i).id).academicHours;
    }

}
//тестовое заполнение данными
void MainWindow::testSubject(){

    QHash<int,Subject> subHash;
    subHash[0]=Subject("АКЗ");
    subHash[1]=Subject("Иностранный язык");
    subHash[2]=Subject("СКВПС");
    subHash[3]=Subject("ООТРП");
    subHash[4]=Subject("Верификация ПО");
    subHash[5]=Subject("РВС");
    for (int i =0; i<subHash.size();i++){
        list_s->append(subHash[i].name);
    }

    QHash<int,GroupStudents> grHash;
    grHash[0]=GroupStudents("5303");
    grHash[1]=GroupStudents("5304");
    grHash[2]=GroupStudents("5305");
    grHash[3]=GroupStudents("5306");
    grHash[4]=GroupStudents("5307");
    grHash[5]=GroupStudents("5308");
    for (int i =0; i<grHash.size();i++){
        list_gr->append(grHash[i].name);
    }

    for (int i =0; i<=5; i++){
        subjectModel->insertRow(i);
        groupModel->insertRow(i);
        gr_subModel->insertRow(i);

        repoSubjects.add(subHash[i]);
        repoGroupStudents.add(grHash[i]);


        const QModelIndex indexNext=subjectModel->index(i,0);

        groupModel->setData(indexNext,QVariant(grHash[i].name));
        subjectModel->setData(indexNext,QVariant(subHash[i].name));
        gr_subModel->setData(indexNext,QVariant(grHash[i].name));

        visualRows(ui->group_table,groupModel);
        visualRows(ui->subject_table,subjectModel);
        visualRows(ui->gr_sub_table,gr_subModel);

        ui->subject_table->setCurrentIndex(indexNext);
        ui->group_table->setCurrentIndex(indexNext);
        ui->gr_sub_table->setCurrentIndex(indexNext);
    }

}
void MainWindow::on_subject_table_clicked(const QModelIndex &index)
{
    QList<Subject> repSubjects;

    Subject reSubject = Subject();
    Subject moSubject=Subject();
    repSubjects = repoSubjects.getAll();

    qDebug()<<"Вывод репозитория";
    for (auto it = repSubjects.begin(); it != repSubjects.end(); ++it) {
        reSubject = *it;
        qDebug() << reSubject.name;
    }
    qDebug()<<"Вывод модели";
    for (auto it = list_s->begin(); it != list_s->end(); ++it) {
        moSubject = *it;
        qDebug() << moSubject.name;
    }
}
void MainWindow::on_group_table_clicked(const QModelIndex &index)
{

    QList<GroupStudents> list_groups;
    GroupStudents  stGrp= GroupStudents();
    GroupStudents  repoGrp= GroupStudents();

    list_groups = this->repoGroupStudents.getAll();

    //QStringList list_s;
    qDebug()<<"Вывод репозитория";
    for (auto it = list_groups.begin(); it != list_groups.end(); ++it) {
        stGrp = *it;
        qDebug() << stGrp.name;
    }
    qDebug()<<"Вывод модели";
    for (auto it = list_gr->begin(); it != list_gr->end(); ++it) {
        repoGrp = *it;
        qDebug() << repoGrp.name;
    }


}
// сохранение прогресса в запущенном файле
void MainWindow::on_saveFile_triggered()
{
    QJsonDocument json;
    QJsonObject object = json.object();

    //repoLinkGroupSubject = dialogLinkGroupSubject->repoLinkGroupSubjects;

    object[this->repoCabinets.getTname()] = this->repoCabinets.toJson();
    object[this->repoSubjects.getTname()] = this->repoSubjects.toJson();
    object[this->repoLessonTime.getTname()] = this->repoLessonTime.toJson();
    object[this->repoGroupStudents.getTname()] = this->repoGroupStudents.toJson();
    object[this->repoLinkGroupSubject.getTname()] = this->repoLinkGroupSubject.toJson();

    json.setObject(object);

    QFile jsonFile(curPathFile);
    if (jsonFile.open(QFile::WriteOnly)){
        jsonFile.write(json.toJson());
        jsonFile.close();
        ui->status_label->setText("Прогресс успешно сохранен!");
    }
    else {
        QMessageBox::information(this,"Файл","Ошибка записи в файл!");
    }
}
//сохранить файл с раскрытием диалогового окна
void MainWindow::on_saveAs_triggered(){
    //путь до директории с файлами
    dSaveAs->setModal(true);
    dSaveAs->changeDialogSaveFile();
    dSaveAs->show();
}
//загрузить файл из хранилища storage
void MainWindow::on_openFile_triggered(){
    dSaveAs->setModal(true);
    dSaveAs->changeDialogOpenFile();
    dSaveAs->show();

}
//удаление файла
void MainWindow::on_deleteFile_triggered(){
    dSaveAs->setModal(true);
    dSaveAs->changeDialogDeleteFile();
    dSaveAs->show();

}


void MainWindow::receiveDeleteFileName(QString pathFile,QString nameFile){

    QFile jsonFile(pathFile);

    //проверка на ввод имени файла
    if (nameFile==""){
        QMessageBox::information(this,"Ошибка","Вы не ввели имя файла!");
        return;

    }
    QDir dir(this->dirStorage);
    dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    dir.setSorting(QDir::Name);
    QFileInfoList list;

    if (pathFile==curPathFile){
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Удаление", "Вы действительно хотите удалить "
                                                        "файл с которым вы работаете в данный момент?",QMessageBox::Yes|QMessageBox::No);
        if (reply==QMessageBox::Yes){

            jsonFile.open(QFile::ReadOnly);
            jsonFile.remove();
            jsonFile.close();

            list = dir.entryInfoList();

            //если после удаления не осталось файлов
            if (list.empty()||!list.empty()){
                clearModel();

                ui->saveFile->setEnabled(false);
                ui->saveAs->setEnabled(false);
                ui->deleteFile->setEnabled(false);

                RepositoryTemplate<Cabinet> lrepoCabinet;
                RepositoryTemplate<Subject> lrepoSubject;
                RepositoryTemplate<LessonTime> lrepoLessonTime;
                RepositoryTemplate<GroupStudents> lrepoGroupStudent;
                RepositoryTemplate<LinkGroupSubject> lrepoLinkGroupSubject;

                this->repoCabinets=lrepoCabinet;
                this->repoSubjects=lrepoSubject;
                this->repoLessonTime=lrepoLessonTime;
                this->repoGroupStudents=lrepoGroupStudent;
                this->repoLinkGroupSubject=lrepoLinkGroupSubject;
                //обнуление буфера группы_предметы
                dialogLinkGroupSubject->repoLinkGroupSubjects = lrepoLinkGroupSubject;
                this->setWindowTitle("no name");
                ui->status_label->setText("Файл успешно удален!");
            }

            dSaveAs->close();


        }
        else {
            return;
        }
    }
    else{
        if (jsonFile.open(QFile::ReadOnly)){
            jsonFile.remove();
            jsonFile.close();
            ui->status_label->setText("Файл успешно удален!");
        }
        else {
            QMessageBox::information(this,"Ошибка","Удаляемый файл не обнаружен!");
        }
    }

}

//получение имени файла для открытия
void MainWindow::receiveOpenFileName(QString pathFile, QString nameFile){

    loadOnSelectedFile(pathFile, nameFile);
}
//создание нового файла
void MainWindow::on_newFile_triggered(){
    dSaveAs->changeDialogNewFile();
    dSaveAs->show();

}

//загрузка файла по выбору
void MainWindow::loadOnSelectedFile(QString pathFile, QString nameFile){
    QFile jsonFile(pathFile);

    //проверка на ввод имени файла
    if (nameFile==""){
        QMessageBox::information(this,"Ошибка","Вы не ввели имя файла!");
        return;

    }


    if (jsonFile.open(QFile::ReadOnly)){
        curPathFile = pathFile;
        QJsonDocument json = QJsonDocument().fromJson(jsonFile.readAll());
        QJsonObject object = json.object();


        RepositoryTemplate<Cabinet> lrepoCabinet;
        RepositoryTemplate<Subject> lrepoSubject;
        RepositoryTemplate<LessonTime> lrepoLessonTime;
        RepositoryTemplate<GroupStudents> lrepoGroupStudent;
        RepositoryTemplate<LinkGroupSubject> lrepoLinkGroupSubject;

        QJsonObject objectCabinets = object[lrepoCabinet.getTname()].toObject();
        QJsonObject objectSubjects = object[lrepoSubject.getTname()].toObject();
        QJsonObject objectLessonTime = object[lrepoLessonTime.getTname()].toObject();
        QJsonObject objectGroupStudents = object[lrepoGroupStudent.getTname()].toObject();
        QJsonObject objectLinkGroupSubject = object[lrepoLinkGroupSubject.getTname()].toObject();

        lrepoCabinet.fromJson(objectCabinets);
        lrepoSubject.fromJson(objectSubjects);
        lrepoLessonTime.fromJson(objectLessonTime);
        lrepoGroupStudent.fromJson(objectGroupStudents);
        lrepoLinkGroupSubject.fromJson(objectLinkGroupSubject);
        jsonFile.close();

        this->setWindowTitle(nameFile+".json");
        //присвоение данных буферу группы_предметы
        dialogLinkGroupSubject->repoLinkGroupSubjects = lrepoLinkGroupSubject;

        this->repoCabinets=lrepoCabinet;
        this->repoSubjects=lrepoSubject;
        this->repoLessonTime=lrepoLessonTime;
        this->repoGroupStudents=lrepoGroupStudent;
        this->repoLinkGroupSubject=lrepoLinkGroupSubject;

        ui->saveFile->setEnabled(true);
        ui->saveAs->setEnabled(true);
        ui->deleteFile->setEnabled(true);

        clearModel();
        loadModelonRepo();
        dSaveAs->close();
        ui->status_label->setText("Файл успешно загружен!");



    }
    else{
        QMessageBox::information(this,"Файл","Ошибка чтения файла!");

    }
}
void MainWindow::receiveFileName(QString pathFile, QString nameFile, bool createFlag){

    if (nameFile==""){
        QMessageBox::information(this,"Ошибка","Вы не ввели имя файла!");
        return;

    }
    QDir dir(this->dirStorage);
    dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    dir.setSorting(QDir::Name);

    QFileInfoList list = dir.entryInfoList();

    if (!list.empty()){
        for (int i = 0; i<list.size(); i++){
            if (pathFile==QDir::currentPath()+"/"+list.at(i).filePath()){
                QMessageBox::information(this,"Ошибка","Файл с таким именем существует!");
                idenFlag = true;
                break;
            }
        }
    }
    if (idenFlag){
        idenFlag = false;
        return;
    }
    if (!createFlag){
        QJsonDocument json;
        QJsonObject object = json.object();

        //repoLinkGroupSubject = dialogLinkGroupSubject->repoLinkGroupSubjects;

        object[this->repoCabinets.getTname()] = this->repoCabinets.toJson();
        object[this->repoSubjects.getTname()] = this->repoSubjects.toJson();
        object[this->repoLessonTime.getTname()] = this->repoLessonTime.toJson();
        object[this->repoGroupStudents.getTname()] = this->repoGroupStudents.toJson();
        object[this->repoLinkGroupSubject.getTname()] = this->repoLinkGroupSubject.toJson();

        json.setObject(object);

        QString jsonName = QString(pathFile).arg(time(NULL));
        QFile jsonFile(jsonName);
        if (jsonFile.open(QFile::WriteOnly)){
            jsonFile.write(json.toJson());
            jsonFile.close();

            clearModel();
            clearRepository();
            loadReps(jsonName);
            this->setWindowTitle(nameFile+".json");

            dSaveAs->close();

            ui->status_label->setText("Новый файл успешно сохранен!");
        }
        else {
            QMessageBox::information(this,"Файл","Ошибка записи в файл!");
        }

    }
    else{

        clearModel();
        clearRepository();

        QJsonDocument json;
        QJsonObject object = json.object();

        object[this->repoCabinets.getTname()] = this->repoCabinets.toJson();
        object[this->repoSubjects.getTname()] = this->repoSubjects.toJson();
        object[this->repoLessonTime.getTname()] = this->repoLessonTime.toJson();
        object[this->repoGroupStudents.getTname()] = this->repoGroupStudents.toJson();
        object[this->repoLinkGroupSubject.getTname()] = this->repoLinkGroupSubject.toJson();

        json.setObject(object);

        QString jsonName = QString(pathFile).arg(time(NULL));
        QFile jsonFile(jsonName);
        if (jsonFile.open(QFile::WriteOnly)){
            jsonFile.write(json.toJson());
            jsonFile.close();
            createFlag=false;

            loadReps(jsonName);

            this->setWindowTitle(nameFile+".json");
            dSaveAs->close();

            ui->saveFile->setEnabled(true);
            ui->saveAs->setEnabled(true);
            ui->deleteFile->setEnabled(true);
            ui->openFile->setEnabled(true);
            ui->status_label->setText("Файл успешно загружен!");

        }
        else{
            QMessageBox::information(this,"Файл","Ошибка записи в файл!");

        }
    }
}

void MainWindow::on_cabinets_table_clicked(const QModelIndex &index)
{
    QList<Cabinet> cabinets_l;
    cabinets_l=this->repoCabinets.getAll();
    qDebug()<<"Репозиторий";
    foreach (Cabinet cabinet, cabinets_l) {
        qDebug()<<cabinet.building<<"\t"<<cabinet.floor<<"\t"<<cabinet.number<<"\n";
    }
    for (int i = 0;i<list_cb->size();i++) {
        qDebug()<<list_cb->at(i);
    }
    qDebug()<<"Индекс по нажатию"<<index.row();
}


void MainWindow::loadReps()
{
    QDate lastDate;
    QTime lastTime;
    // Достаем список файлов для сущности, с которой работает репозиторий
    QDir dir(this->dirStorage);

    dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    dir.setSorting(QDir::Name);
    QFileInfoList list = dir.entryInfoList();
    //буфер для сравнения
    QFileInfoList buffer;
    //последний созданный файл
    QString lastFile;

    // Если файлы существуют, то считываем их
    if (!list.empty()){
        if (list.size()<2){
            //если один файл
            lastFile = list.back().fileName();
        } else
        {
            //Последняя дата создания
            lastDate = list.first().created().date();

            //поиск последнего добавленного файла
            for (int i =1; i<list.size(); i++){
                if (lastDate<list.at(i).created().date()){
                    lastDate=list.at(i).created().date();
                }
            }

            for (int i =0; i<list.size(); i++){
                if (lastDate==list.at(i).created().date()){
                    buffer.append(list.at(i));
                }
            }

            lastTime = buffer.first().created().time();
            lastFile=buffer.first().fileName();

            for (int i =1; i<buffer.size(); i++){
                if (lastTime<buffer.at(i).created().time()){
                    lastTime= buffer.at(i).created().time();
                    lastFile = buffer.at(i).fileName();
                }
            }

        }
        QFileInfo fileInfo;

        //qDebug()<<lastTime;
        // Берем файл последний измененный файл
        QString jsonName =QDir::currentPath()+"/"+QString("%1/%2").arg(this->dirStorage).arg(lastFile);
        this->setWindowTitle(lastFile);

        this->loadReps(jsonName);
        ui->status_label->setText("Файл успешно загружен!");
    }
    else {
        this->setWindowTitle("no name");
        ui->status_label->setText("Файлов не обнаружено!");
        ui->saveFile->setEnabled(false);
        ui->saveAs->setEnabled(false);
        ui->openFile->setEnabled(false);
        ui->deleteFile->setEnabled(false);
    }
}

void MainWindow::loadReps(QString jsonName)
{
    // Десериализуем
    QFile jsonFile(jsonName);
    if (jsonFile.open(QFile::ReadOnly)){
        QJsonDocument json = QJsonDocument().fromJson(jsonFile.readAll());
        QJsonObject object = json.object();

        QJsonObject objectCabinets = object[this->repoCabinets.getTname()].toObject();
        QJsonObject objectSubjects = object[this->repoSubjects.getTname()].toObject();
        QJsonObject objectLessonTime = object[this->repoLessonTime.getTname()].toObject();
        QJsonObject objectGroupStudents = object[this->repoGroupStudents.getTname()].toObject();
        QJsonObject objectLinkGroupSubject = object[this->repoLinkGroupSubject.getTname()].toObject();

        this->repoCabinets.fromJson(objectCabinets);
        this->repoSubjects.fromJson(objectSubjects);
        this->repoLessonTime.fromJson(objectLessonTime);
        this->repoGroupStudents.fromJson(objectGroupStudents);
        this->repoLinkGroupSubject.fromJson(objectLinkGroupSubject);
        jsonFile.close();

        curPathFile = jsonName;

        loadModelonRepo();
    }
    else {
        QMessageBox::information(this,"Файл","Ошибка чтения файла!");
    }


}

void MainWindow::initStorage() {
    QDir dirStorage(this->dirStorage);


    if (!dirStorage.exists()) {
        QDir().mkdir(this->dirStorage);
    }
}

// загрузка моделей по файлу
void MainWindow::loadModelonRepo(){


    dialogLinkGroupSubject->repoLinkGroupSubjects=repoLinkGroupSubject;

    for (int i =0; i<repoSubjects.getAmount();i++){
        list_s->append(repoSubjects.getByIndex(i).name);
        subjectModel->insertRow(i);

        subjectModel->setData(subjectModel->index(i,0),QVariant(repoSubjects.getByIndex(i).name));
        visualRows(ui->subject_table,subjectModel);

    }
    for (int i =0; i<repoGroupStudents.getAmount();i++){
        list_gr->append(repoGroupStudents.getByIndex(i).name);

        groupModel->insertRow(i);
        gr_subModel->insertRow(i);

        groupModel->setData(groupModel->index(i,0),QVariant(repoGroupStudents.getByIndex(i).name));
        gr_subModel->setData(gr_subModel->index(i,0),QVariant(repoGroupStudents.getByIndex(i).name));

        visualRows(ui->group_table,groupModel);
        visualRows(ui->gr_sub_table,gr_subModel);

    }
    for (int i =0; i<repoCabinets.getAmount();i++){
        list_cb->append(QString("%1%2%3").arg(repoCabinets.getByIndex(i).building)
                        .arg(repoCabinets.getByIndex(i).floor).arg(repoCabinets.getByIndex(i).number));
        cabinetModel->insertRow(i);

        cabinetModel->setData(cabinetModel->index(i,0),QVariant(QString("%1%2%3").arg(repoCabinets.getByIndex(i).building)
                                                                .arg(repoCabinets.getByIndex(i).floor).arg(repoCabinets.getByIndex(i).number)));

        visualRows(ui->cabinets_table,cabinetModel);

    }
    for (int i =0; i<repoLessonTime.getAmount();i++){
        list_tm->append(QString("Четность:%1 %2 Время:%3").arg(repoLessonTime.getByIndex(i).parity).arg(receiveDay[repoLessonTime.getByIndex(i).dayOfWeek]).
                arg(repoLessonTime.getByIndex(i).time.toString()));
        timeModel->insertRow(i);

        timeModel->setData(timeModel->index(i,0),QVariant(QString("Четность:%1 %2 Время:%3").arg(repoLessonTime.getByIndex(i).parity).arg(receiveDay[repoLessonTime.getByIndex(i).dayOfWeek]).
                           arg(repoLessonTime.getByIndex(i).time.toString())));

        visualRows(ui->time_table,timeModel);
    }



}

void MainWindow::clearTableView(QTableView *tableView, TableListModel *model){

    if (model->rowCount()!=0){
        int r = tableView->model()->rowCount();
        r--;
        while(model->rowCount()>0){
            tableView->model()->removeRow(r);
            r--;
        }
        visualRows(tableView,model);
        if (model->rowCount()==0){
            while(tableView->model()->rowCount()>0){
                tableView->model()->removeRow(r);
                r--;
            }
        }
    }

}

void MainWindow::clearModel(){
    //Очищение QStringList таблиц
    if(list_s->size()!=0){
        list_s->clear();
    }
    if (list_gr->size()!=0){
        list_gr->clear();
    }
    if (list_cb->size()!=0){
        list_cb->clear();
    }
    if(list_tm->size()!=0){
        list_tm->clear();
    }

    //Очищение AbstarctModel таблиц
    clearTableView(ui->subject_table,subjectModel);
    clearTableView(ui->group_table,groupModel);
    clearTableView(ui->cabinets_table,cabinetModel);
    clearTableView(ui->time_table,timeModel);
    clearTableView(ui->gr_sub_table,gr_subModel);
}
//очищение репозиториев
void MainWindow::clearRepository(){
    RepositoryTemplate<Cabinet> lrepoCabinet;
    RepositoryTemplate<Subject> lrepoSubject;
    RepositoryTemplate<LessonTime> lrepoLessonTime;
    RepositoryTemplate<GroupStudents> lrepoGroupStudent;
    RepositoryTemplate<LinkGroupSubject> lrepoLinkGroupSubject;

    repoCabinets= lrepoCabinet;
    repoSubjects = lrepoSubject;
    repoLessonTime = lrepoLessonTime;
    repoGroupStudents = lrepoGroupStudent;
    repoLinkGroupSubject = lrepoLinkGroupSubject;
    //обнуление буфера группы_предметы
    dialogLinkGroupSubject->repoLinkGroupSubjects = lrepoLinkGroupSubject;
}
//изменение основного репозитория RepoLinkGroupSubject в соответствии c изменениями буфера
void MainWindow::receiveEditRepoLinkGrSb(RepositoryTemplate<LinkGroupSubject> recEditRepoGrSb){
    repoLinkGroupSubject = recEditRepoGrSb;
}
//проверка на одинаковые данные в репозиториях repoSubjects, repoGroupStudents
int MainWindow::checkidenticalDataRepo(QString name){
    if (name!=nullptr&&repoSubjects.getAmount()!=0){
        for (int i =0; i<repoSubjects.getAmount();i++){
            if (name==repoSubjects.getByIndex(i).name){
                QMessageBox::information(this,"Ошибка","Данный предмет существует!");
                return 1;

            }
        }
    }
    if (name!=nullptr&&repoGroupStudents.getAmount()!=0){
        for (int i =0; i<repoGroupStudents.getAmount();i++){
            if (name==repoGroupStudents.getByIndex(i).name){
                QMessageBox::information(this,"Ошибка","Данная группа существует!");
                return 1;

            }
        }
    }

}

int MainWindow::checkidenticalDataCabinets(Cabinet cab){
    if (repoCabinets.getAmount()!=0){
        for (int i =0; i<repoCabinets.getAmount();i++){
            if (repoCabinets.getByIndex(i).floor==cab.floor&&repoCabinets.getByIndex(i).number==cab.number&&
                    repoCabinets.getByIndex(i).building==cab.building){
                QMessageBox::information(this,"Ошибка","Данный кабинет существует!");
                return 1;

            }
        }
    }
}

int MainWindow::checkidenticalDataTime(LessonTime lt){
    if (repoLessonTime.getAmount()!=0){
        for (int i =0; i<repoLessonTime.getAmount();i++){
            if (repoLessonTime.getByIndex(i).time==lt.time&&repoLessonTime.getByIndex(i).parity==lt.parity&&
                    repoLessonTime.getByIndex(i).dayOfWeek==lt.dayOfWeek){
                QMessageBox::information(this,"Ошибка","Данное время уже задано!");
                return 1;

            }
        }
    }
}

void MainWindow::on_tabWidget_tabBarClicked(int index)
{
    qDebug()<<"StartSchedule";
    if (index == 2 || index == 3) {
        Graph graph = Graph(
                    this->repoCabinets,
                    this->repoGroupStudents,
                    this->repoLessonTime,
                    this->repoSubjects,
                    this->repoLinkGroupSubject
                    );

        this->graph = graph.fit();
        QList<Lesson> lessons = transformGrapthToLessons();
        //qDebug()<<this->graph;
        ScheduleTableAbstractModule *model = new ScheduleTableAbstractModule(lessons);
        this->schedueWidget->updateModel(model);
    }

}

void MainWindow::updatatingVisualization(int index)
{
    //    if( index == 3) {

    //    }
}

QList<Lesson> MainWindow::transformGrapthToLessons()
{
    qDebug()<<this->graph.size();
    QList<Lesson> lessons;
    for (int i = 0; i < graph.size(); i++) {

        //        QString group = this->repoGroupStudents.getById(graph[i][0]).name;
        //        QString subject = this->repoSubjects.getById(graph[i][1]).name;
        //        int floor = this->repoCabinets.getByIndex(graph[i][2]).floor;
        //        lessons.append(Lesson(group,subject,floor));

        GroupStudents group = this->repoGroupStudents.getById(graph[i][0]);
        Subject subject = this->repoSubjects.getById(graph[i][1]);
        Cabinet cabinet = this->repoCabinets.getByIndex(graph[i][2]);
        LessonTime lessonTime = this->repoLessonTime.getById(graph[i][3]);
        lessons.append(Lesson(group,subject,cabinet,lessonTime,receiveDay));

    }
    return lessons;

}
