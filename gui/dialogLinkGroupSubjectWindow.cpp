#include "dialogLinkGroupSubjectWindow.h"
#include <qpushbutton.h>
#include <qlineedit.h>
#include <qlabel.h>
#include <qlayout.h>
#include <qcheckbox.h>
#include <QDebug>
#include<QFormLayout>
#include<models/repository/repositorytemplate.h>
#include<models/cabinet.h>
#include <gui/mainwindow.h>
#include <QTableView>
#include <QHeaderView>
#include <QMenu>
#include "dialogAddlinkGroupSubject.h"

DialogLinkGroupSubjectWindow::DialogLinkGroupSubjectWindow(QWidget* parent): QDialog(parent)
{
    this->setWindowFlags(Qt::Window);
    this->resize(1000,800);
    list_s = new QStringList();
    list_link_subject = new QStringList();

    table_link_subject = new QTableView(this);
    link_sub_model = new TableListModel(*list_link_subject);

    label_allSub = new QLabel();
    label_link = new QLabel();
    label_allSub->setText("Все предметы");

    table_subject = new QTableView(this);
    table_subject->setContextMenuPolicy(Qt::CustomContextMenu);

    gridLayout = new QGridLayout;

    dialogLinkGS = new DialogAddLinkGroupSubject();

    connect(table_subject,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(customLinkGroupSubjectMenuRequested(QPoint)));
    connect(dialogLinkGS,SIGNAL(sendRepoGroupSubject(LinkGroupSubject,QString)),this,SLOT(receiveRepoGroupSubject(LinkGroupSubject,QString)));


    //int index =table_subject->currentIndex().row()+1;
    /*list_all_subject->append("Математика");
    link_sub_model = new TableListModel(*list_all_subject);
    table_subject->setModel(link_sub_model);
    table_subject->show();*/

    //link_sub_model->insertRow(index);

    //const QModelIndex indexNext=link_sub_model->index(index,0);
    //link_sub_model->setData(indexNext,QVariant("Математика"));
    //visualRows(table_subject,link_sub_model);
    //table_subject->setCurrentIndex(indexNext);
 }

void DialogLinkGroupSubjectWindow::receiveGroup(int currentIndex,QStringList list_sub,RepositoryTemplate<GroupStudents> repoGroupStudents,RepositoryTemplate<Subject> repoSubjects){

   indexGroup = currentIndex;
   label_link->setText(QString("Предметы группы %1").arg(repoGroupStudents.getById(repoGroupStudents.getByIndex(currentIndex).id).name));


    for (int i =0; i<list_sub.size(); i++){
       list_s->append(list_sub.at(i));
   }

     for (int i =0; i<repoGroupStudents.getAmount(); i++){
        repoRecGroupStudent.add(repoGroupStudents.getById(i));
     }


   for (int i =0; i<repoSubjects.getAmount(); i++){
       repoRecSubject.add(repoSubjects.getById(i).name);
   }
   if (!recList){
        sub_model = new TableListModel(*list_s);
        recList =true;
    }
   visualRows(table_subject,sub_model);
   visualRows(table_link_subject,link_sub_model);

   gridLayout->addWidget(label_allSub,0,0,1,100,Qt::AlignHCenter);
   gridLayout->addWidget(label_link,0,100,1,100,Qt::AlignHCenter);
   gridLayout->addWidget(table_subject,20,0,100,100);
   gridLayout->addWidget(table_link_subject,20,100,100,100);

   this->setLayout(gridLayout);
   if (table_link_subject->model()->rowCount()!=0){
        clearTableView();
   }
   if (repoLinkGroupSubjects.getAmount()!=0){
       for (int i =0; i<repoLinkGroupSubjects.getAmount(); i++){
           if (repoGroupStudents.getById(repoGroupStudents.getByIndex(currentIndex).id).id==repoLinkGroupSubjects.getById(repoLinkGroupSubjects.getByIndex(i).id).groupId){
               insertTableView(repoSubjects.getById(repoLinkGroupSubjects.getById(repoLinkGroupSubjects.getByIndex(i).id).subjectId).name);
          }
       }
   }
  /* qDebug()<<"репоПредметы";
   for (int i =0; i<repoRecSubject.getAmount(); i++){
       qDebug()<<repoRecSubject.getById(i).name;
   }
   qDebug()<<"репоГруппы";
   for (int i =0; i<repoRecGroupStudent.getAmount(); i++){
       qDebug()<<repoRecGroupStudent.getById(i).name;
   }
   qDebug()<<"список";
   for (int i =0; i<list_s->size(); i++){
      qDebug()<<list_s->at(i);
  }*/

}

void DialogLinkGroupSubjectWindow::insertTableView(QString nameS){
    int index =table_link_subject->currentIndex().row()+1;

    link_sub_model->insertRow(index);
    const QModelIndex indexNext=link_sub_model->index(index,0);
    link_sub_model->setData(indexNext,QVariant(nameS));
    visualRows(table_link_subject,link_sub_model);
    table_link_subject->setCurrentIndex(indexNext);
}


void DialogLinkGroupSubjectWindow::customLinkGroupSubjectMenuRequested(const QPoint &pos){
    QMenu *menu = new QMenu(this);

    QAction *addSubject = new QAction(("Добавить в группу"),this);
    indexSubject=table_subject->selectionModel()->currentIndex().row();
    connect(addSubject, SIGNAL(triggered()),this,SLOT(slotLinkSubject_GroupAddRecord()));
    menu->addAction(addSubject);
    menu->popup(table_subject->viewport()->mapToGlobal(pos));
    indexSubject=table_subject->selectionModel()->currentIndex().row();
}
void DialogLinkGroupSubjectWindow::slotLinkSubject_GroupAddRecord(){

   dialogLinkGS->addLinkGroupSubject(indexGroup,indexSubject, repoRecGroupStudent,repoRecSubject);
   dialogLinkGS->show();

}

void DialogLinkGroupSubjectWindow::receiveRepoGroupSubject(LinkGroupSubject gr_sub,QString nameSubject){

    repoLinkGroupSubjects.add(gr_sub);
    int index =table_link_subject->currentIndex().row()+1;

    link_sub_model->insertRow(index);
    const QModelIndex indexNext=link_sub_model->index(index,0);
    link_sub_model->setData(indexNext,QVariant(nameSubject));
    visualRows(table_link_subject,link_sub_model);
    table_link_subject->setCurrentIndex(indexNext);

}
void DialogLinkGroupSubjectWindow::clearTableView(){
    int r = table_link_subject->model()->rowCount();
    r--;
    while(link_sub_model->rowCount()>0){
     table_link_subject->model()->removeRow(r);
     r--;
  }
  visualRows(table_link_subject,link_sub_model);
}

void DialogLinkGroupSubjectWindow::visualRows(QTableView *table, TableListModel *model){
    table->setModel(model);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->show();
}

void DialogLinkGroupSubjectWindow::closeEvent(QCloseEvent *){

}


