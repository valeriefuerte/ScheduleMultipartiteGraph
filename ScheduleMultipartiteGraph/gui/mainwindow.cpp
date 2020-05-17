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
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "models/tablelistmodel.h"
#include "dialogWindowEmptyRow.h"
#include "dialogCabinetWindow.h"
#include "models/repository/repositorytemplate.h"
#include "gui/dialogLessonTimeWindow.h"
#include "gui/visualizationwidget.h"
#include "gui/group_subject.h"
#include "models/linkgroupsubject.h"
#include "gui/dialogLinkGroupSubjectWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

      ui->setupUi(this);
      this->initStorage();
      this->loadReps();


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

      //Инициализация диалоговых окон
      dialogEmptyRow = new DialogWindowEmptyRow();
      dialogEmptyRow->resize(300,100);

      dialogConfrimEdit = new DialogWindowConfirmEditRow();
      dialogConfrimEdit->resize(300,100);

      dialogSubject = new DialogSubjectWindow();
      dialogGroup = new DialogGroupWindow();
      dialogCabinet = new DialogCabinetWindow();
      dialogLessonTime = new DialogLessonTimeWindow();
      dialogLinkGroupSubject = new DialogLinkGroupSubjectWindow();
      testSubject();
      //dialogLinkGroupSubject->show();



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



      //connect(this,SIGNAL(sendSelectionCabinet(Cabinet)),dialogConfirmCabinet,SLOT(receiveSelectionCabinet(Cabinet)));

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


      // Виджет визуализации графа
      VisualizationWidget *w = new VisualizationWidget();
      ui->tabWidget->addTab(w,"Визуализация графа");
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
    repoSubjects.remove(repoSubjects.getById(repoSubjects.getByIndex(index).id).id);
    list_s->removeAt(index);
    ui->subject_table->model()->removeRow(index);
}

void MainWindow::receiveDataSubject(Subject subject){
     repoSubjects.add(subject);
     list_s->append(subject.name);

     int index =ui->subject_table->model()->rowCount();
     subjectModel->insertRow(index);

     const QModelIndex indexNext=subjectModel->index(index,0);
     subjectModel->setData(indexNext,QVariant(subject.name));
     visualRows(ui->subject_table,subjectModel);
     ui->subject_table->setCurrentIndex(indexNext);
 }

void MainWindow::receiveEditDataSubject(Subject subject){

    int index =ui->subject_table->selectionModel()->currentIndex().row();

    list_s->replace(index,subject.name);
    repoSubjects.update(repoSubjects.getById(repoSubjects.getByIndex(index).id).id,subject.name);

    const QModelIndex curSelectIndex=subjectModel->index(index,0);
    subjectModel->setData(curSelectIndex,QVariant(subject.name));
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

    menu->addAction(addSubject);
    menu->addAction(editSubject);
    menu->addAction(deleteSubject);

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
    this->repoGroupStudents.remove(repoGroupStudents.getByIndex(index).id);
    list_gr->removeAt(index);
    ui->group_table->model()->removeRow(index);
    ui->gr_sub_table->model()->removeRow(index);
}


void MainWindow::receiveDataGroup(GroupStudents group){
     repoGroupStudents.add(group);
     list_gr->append(group.name);

     int index =ui->group_table->model()->rowCount();
     groupModel->insertRow(index);
     gr_subModel->insertRow(index);

     const QModelIndex indexNext=groupModel->index(index,0);
     groupModel->setData(indexNext,QVariant(group.name));
     gr_subModel->setData(indexNext,QVariant(group.name));

     visualRows(ui->group_table,groupModel);
     visualRows(ui->gr_sub_table,gr_subModel);

     ui->group_table->setCurrentIndex(indexNext);
     ui->gr_sub_table->setCurrentIndex(indexNext);
 }
void MainWindow::receiveEditDataGroup(GroupStudents group){

    int index =ui->group_table->selectionModel()->currentIndex().row();

    list_gr->replace(index,group.name);
    repoGroupStudents.update(repoGroupStudents.getById(repoGroupStudents.getByIndex(index).id).id,group.name);

    const QModelIndex curSelectIndex=groupModel->index(index,0);
    groupModel->setData(curSelectIndex,QVariant(group.name));
    gr_subModel->setData(curSelectIndex,QVariant(group.name));
}

void MainWindow::customGroupMenuRequested(const QPoint &pos){

   QMenu *menu = new QMenu(this);

   QAction *addGroup = new QAction(("Добавить"),this);
   QAction *editGroup = new QAction(("Редактировать"),this);
   QAction *deleteGroup = new QAction(("Удалить"),this);

   connect(addGroup, SIGNAL(triggered()),this,SLOT(slotGroupAddRecord()));
   connect(editGroup, SIGNAL(triggered()),this,SLOT(slotGroupEditRecord()));
   connect(deleteGroup, SIGNAL(triggered()),this,SLOT(slotGroupRemoveRecord()));

   menu->addAction(addGroup);
   menu->addAction(editGroup);
   menu->addAction(deleteGroup);

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

     QString s = QString("%1%2%3").arg(cabinet.building).arg(cabinet.floor).arg(cabinet.number);
     repoCabinets.add(cabinet);
     list_cb->append(s);
     int index =ui->cabinets_table->model()->rowCount();

     cabinetModel->insertRow(index);
     const QModelIndex indexNext=cabinetModel->index(index,0);
     cabinetModel->setData(indexNext,QVariant(s));
     visualRows(ui->cabinets_table,cabinetModel);
     ui->cabinets_table->setCurrentIndex(indexNext);
}
void MainWindow::receiveEditDataCabinet(Cabinet cabinet){

    int index =ui->cabinets_table->selectionModel()->currentIndex().row();

    QString s = QString("%1%2%3").arg(cabinet.building).arg(cabinet.floor).arg(cabinet.number);
    list_cb->replace(index,s);
    repoCabinets.update(repoCabinets.getById(repoCabinets.getByIndex(index).id).id,cabinet);

    const QModelIndex curSelectIndex=cabinetModel->index(ui->cabinets_table->selectionModel()->currentIndex().row(),0);
    cabinetModel->setData(curSelectIndex,QVariant(s));
     /*QList<Cabinet> cab_l;
    cab_l=repCabinet->getAll();

    QString s = QString::number(cab_l.back().building)+QString::number(cab_l.back().floor)+QString::number(cab_l.back().number);
    qDebug()<<"Вывод принятого репозитория";
    QList<Cabinet> cabinets_l;
        cabinets_l=repCabinet->getAll();
         foreach (Cabinet cabinet, cabinets_l) {
            qDebug()<<cabinet.floor<<"\t"<<cabinet.number<<"\t"<<cabinet.building<<"\n";
        }
     repoCabinets.update(selectIndex,repCabinet->getById(0));
     list_cb->replace(selectIndex,s);*/
     //const QModelIndex indexNext=cabinetModel->index(selectIndex,0);
     //cabinetModel->setData(indexNext,QVariant(s));
    //qDebug()<<repCabinet->getById(0).building<<repCabinet->getById(0).floor<<repCabinet->getById(0).number;
    //repoCabinets.update(selectIndex,repCabinet->getById(0));

}

void MainWindow::customCabinetMenuRequested(const QPoint &pos){

   QMenu *menu = new QMenu(this);

   QAction *addCabinet = new QAction(("Добавить"),this);
   QAction *editCabinet = new QAction(("Редактировать"),this);
   QAction *deleteCabinet = new QAction(("Удалить"),this);

   connect(addCabinet, SIGNAL(triggered()),this,SLOT(slotCabinetAddRecord()));
   connect(editCabinet, SIGNAL(triggered()),this,SLOT(slotCabinetEditRecord()));
   connect(deleteCabinet, SIGNAL(triggered()),this,SLOT(slotCabinetRemoveRecord()));

   menu->addAction(addCabinet);
   menu->addAction(editCabinet);
   menu->addAction(deleteCabinet);

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

    menu->addAction(addTime);
    menu->addAction(editTime);
    menu->addAction(deleteTime);

    menu->popup(ui->time_table->viewport()->mapToGlobal(pos));
}

void MainWindow::receiveDataLessonTime(LessonTime lessonTime){


     QString s = QString("Четность:%1 %2 Время:%3").arg(lessonTime.parity).arg(receiveDay[lessonTime.dayOfWeek]).arg(lessonTime.time.toString());

     repoLessonTime.add(lessonTime);
     list_tm->append(s);
     int index =ui->time_table->model()->rowCount();

     timeModel->insertRow(index);
     const QModelIndex indexNext=timeModel->index(index,0);
     timeModel->setData(indexNext,QVariant(s));
     visualRows(ui->time_table,timeModel);
     ui->time_table->setCurrentIndex(indexNext);
     qDebug()<<repoLessonTime.getById(0).dayOfWeek<<repoLessonTime.getById(0).time<<repoLessonTime.getById(0).parity;

}
void MainWindow::receiveEditDataLessonTime(LessonTime lessonTime){

    int index =ui->time_table->selectionModel()->currentIndex().row();

    QString s = QString("Четность:%1 %2 Время:%3").arg(lessonTime.parity).arg(receiveDay[lessonTime.dayOfWeek]).arg(lessonTime.time.toString());
    list_tm->replace(repoLessonTime.getById(repoLessonTime.getByIndex(index).id).id,s);
    repoLessonTime.update(repoLessonTime.getById(repoLessonTime.getByIndex(index).id).id,lessonTime);

    const QModelIndex curSelectIndex=timeModel->index(ui->time_table->selectionModel()->currentIndex().row(),0);
    timeModel->setData(curSelectIndex,QVariant(s));
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
    for (int i=0; i<dialogLinkGroupSubject->repoLinkGroupSubjects.getAmount();i++){
        qDebug()<<dialogLinkGroupSubject->repoLinkGroupSubjects.getById(dialogLinkGroupSubject->repoLinkGroupSubjects.getByIndex(i).id).groupId<<
                  dialogLinkGroupSubject->repoLinkGroupSubjects.getById(dialogLinkGroupSubject->repoLinkGroupSubjects.getByIndex(i).id).subjectId
               <<dialogLinkGroupSubject->repoLinkGroupSubjects.getById(dialogLinkGroupSubject->repoLinkGroupSubjects.getByIndex(i).id).academicHours;
    }
}
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
        //int index =ui->subject_table->currentIndex().row()+1;
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


void MainWindow::on_saveFile_triggered()
{
    QJsonDocument json;
    QJsonObject object = json.object();

    object[this->repoCabinets.getTname()] = this->repoCabinets.toJson();
    object[this->repoSubjects.getTname()] = this->repoSubjects.toJson();
    object[this->repoLessonTime.getTname()] = this->repoLessonTime.toJson();
    object[this->repoGroupStudents.getTname()] = this->repoGroupStudents.toJson();
    object[this->repoLinkGroupSubject.getTname()] = this->repoLinkGroupSubject.toJson();

    json.setObject(object);

    QString jsonName = QString("storage/%1.json").arg(time(NULL));
    QFile jsonFine(jsonName);
    jsonFine.open(QFile::WriteOnly);
    jsonFine.write(json.toJson());
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
    // Достаем список файлов для сущности, с которой работает репозиторий
    QDir dir(this->dirStorage);
    dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    dir.setSorting(QDir::Name);
    QFileInfoList list = dir.entryInfoList();

    // Если файлы существуют, то считываем их
    if (!list.empty()){
        // Берем файл последний файл
        QString jsonName = QString("%1/%2").arg(this->dirStorage).arg(list.at(list.size()-1).fileName());
        this->loadReps(jsonName);
    }
}

void MainWindow::loadReps(QString jsonName)
{
    // Десериализуем
    QFile jsonFile(jsonName);
    jsonFile.open(QFile::ReadOnly);
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

    qDebug() << "work" << endl;
}

void MainWindow::initStorage() {
    QDir dirStorage(this->dirStorage);

    if (!dirStorage.exists()) {
        QDir().mkdir(this->dirStorage);
    }
}

