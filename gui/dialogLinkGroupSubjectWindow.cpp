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
    table_link_subject->setContextMenuPolicy(Qt::CustomContextMenu);

    label_allSub = new QLabel();
    label_link = new QLabel();
    label_allSub->setText("Все предметы");

    table_subject = new QTableView(this);
    table_subject->setContextMenuPolicy(Qt::CustomContextMenu);

    gridLayout = new QGridLayout;

    dialogLinkGS = new DialogAddLinkGroupSubject();

    connect(table_subject,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(customGroupSubjectMenuRequested(QPoint)));
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

   //обновление списка
   if (!recList){
       for (int i =0; i<list_sub.size(); i++){
          list_s->append(list_sub.at(i));
       }
      sub_model = new TableListModel(*list_s);
      recList = true;
    }
    else
   {
       for (int i =0; i<list_sub.size(); i++){
          list_s->append(list_sub.at(i));
          insertTableView(list_s->last(),table_subject,sub_model);
        }

   }

    editDataRepoGroup(repoGroupStudents);
    editDataRepoSubject(repoSubjects);

    /* qDebug()<<"RepoGroupStudents: ";
    for (int i = 0; i<repoGroupStudents.getAmount(); i++){
        qDebug()<<repoGroupStudents.getByIndex(i).name;
    }
    qDebug()<<"RepoRecGroupStudents: ";
    for (int i = 0; i<repoRecGroupStudent.getAmount(); i++){
        qDebug()<<repoRecGroupStudent.getByIndex(i).name;
    }
    qDebug()<<"RepoSubjects: ";
   for (int i = 0; i<repoSubjects.getAmount(); i++){
       qDebug()<<repoSubjects.getByIndex(i).name;
   }
   qDebug()<<"RepoRecSubjects: ";
   for (int i = 0; i<repoRecSubject.getAmount(); i++){
       qDebug()<<repoRecSubject.getByIndex(i).name;
   }*/

       /*qDebug()<<"RepoSubject: "<<repoSubjects.getAmount()<<"RepoSubject: "<<repoRecSubject.getAmount();
       for (int i =0; i<repoRecSubject.getAmount(); i++){
            qDebug()<<repoRecSubject.getById(i).name;
      }*/


   visualRows(table_subject,sub_model);
   visualRows(table_link_subject,link_sub_model);

   gridLayout->addWidget(label_allSub,0,0,1,100,Qt::AlignHCenter);
   gridLayout->addWidget(label_link,0,100,1,100,Qt::AlignHCenter);
   gridLayout->addWidget(table_subject,20,0,100,100);
   gridLayout->addWidget(table_link_subject,20,100,100,100);

   this->setLayout(gridLayout);
   if (table_link_subject->model()->rowCount()!=0){
        clearTableView(table_link_subject,link_sub_model);
   }
   if (repoLinkGroupSubjects.getAmount()!=0){
       for (int i =0; i<repoLinkGroupSubjects.getAmount(); i++){
           if (repoGroupStudents.getById(repoGroupStudents.getByIndex(currentIndex).id).id==repoLinkGroupSubjects.getById(repoLinkGroupSubjects.getByIndex(i).id).groupId){
               insertTableView(repoSubjects.getById(repoLinkGroupSubjects.getById(repoLinkGroupSubjects.getByIndex(i).id).subjectId).name,table_link_subject,link_sub_model);
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

void DialogLinkGroupSubjectWindow::insertTableView(QString nameS, QTableView *tableView, TableListModel *model){
    int index =tableView->currentIndex().row()+1;

    model->insertRow(index);
    const QModelIndex indexNext=model->index(index,0);
    model->setData(indexNext,QVariant(nameS));
    visualRows(tableView,model);
    tableView->setCurrentIndex(indexNext);
}


void DialogLinkGroupSubjectWindow::customGroupSubjectMenuRequested(const QPoint &pos){
    QMenu *menu = new QMenu(this);
    QAction *addSubject = new QAction(("Добавить в группу"),this);
    indexSubject=table_subject->selectionModel()->currentIndex().row();
    connect(addSubject, SIGNAL(triggered()),this,SLOT(slotLinkSubject_GroupAddRecord()));
    menu->addAction(addSubject);
    menu->popup(table_subject->viewport()->mapToGlobal(pos));
}
void DialogLinkGroupSubjectWindow::slotLinkSubject_GroupAddRecord(){

   dialogLinkGS->addLinkGroupSubject(indexGroup,indexSubject, repoRecGroupStudent,repoRecSubject);
   dialogLinkGS->show();

}

void DialogLinkGroupSubjectWindow::customLinkGroupSubjectMenuRequested(const QPoint &pos){
    QMenu *menu = new QMenu(this);
    QAction *deleteSubject = new QAction(("Удалить"),this);

    /*indexSubject=table_subject->selectionModel()->currentIndex().row();
    connect(addSubject, SIGNAL(triggered()),this,SLOT(slotLinkSubject_GroupAddRecord()));
    menu->addAction(addSubject);
    menu->popup(table_subject->viewport()->mapToGlobal(pos));
    indexSubject=table_subject->selectionModel()->currentIndex().row();*/
}

void DialogLinkGroupSubjectWindow::receiveRepoGroupSubject(LinkGroupSubject gr_sub,QString nameSubject){

    QString sub_hr = QString("Предмет: %1; Академические часы: %2").arg(nameSubject).arg(gr_sub.academicHours);
    repoLinkGroupSubjects.add(gr_sub);
    int index =table_link_subject->currentIndex().row()+1;

    link_sub_model->insertRow(index);
    const QModelIndex indexNext=link_sub_model->index(index,0);
    link_sub_model->setData(indexNext,QVariant(sub_hr));
    visualRows(table_link_subject,link_sub_model);
    table_link_subject->setCurrentIndex(indexNext);

}
void DialogLinkGroupSubjectWindow::clearTableView(QTableView *tableView, TableListModel *model){
    int r = tableView->model()->rowCount();
    r--;
    while(model->rowCount()>0){
     tableView->model()->removeRow(r);
     r--;
  }
  visualRows(tableView,model);
}

void DialogLinkGroupSubjectWindow::visualRows(QTableView *table, TableListModel *model){
    table->setModel(model);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->show();
}

void DialogLinkGroupSubjectWindow::editDataRepoGroup(RepositoryTemplate<GroupStudents> repoGroupStudents){
    //Проверка на изменения(удаление, добавление, редактирование) репозиториев в главной вкладке
    if (repoRecGroupStudent.getAmount()==0){
        for (int i =0; i<repoGroupStudents.getAmount(); i++){
            repoRecGroupStudent.add(repoGroupStudents.getById(i));
        }

    }else
          if (repoGroupStudents.getAmount()>repoRecGroupStudent.getAmount()){
            int raz = repoGroupStudents.getAmount()-repoRecGroupStudent.getAmount();
            int addE = repoRecGroupStudent.getAmount();
            for (int i =0; i<raz; i++){
                repoRecGroupStudent.add(repoGroupStudents.getById(repoGroupStudents.getByIndex(addE).id));
                ++addE;
            }
    }else
          if (repoGroupStudents.getAmount()<repoRecGroupStudent.getAmount()){
            int raz = repoRecGroupStudent.getAmount()-repoGroupStudents.getAmount();
            int delE = repoRecGroupStudent.getAmount()-1;
            for (int i =0; i<raz; i++){
                repoRecGroupStudent.removeByIndex(delE);
            --delE;
            }
    }
    else
         if (repoGroupStudents.getAmount()==repoRecGroupStudent.getAmount()){
            for (int i =0; i<repoGroupStudents.getAmount(); i++){
                if (repoGroupStudents.getByIndex(i).name!=repoRecGroupStudent.getByIndex(i).name){
                    repoRecGroupStudent.update(repoGroupStudents.getById(repoGroupStudents.getByIndex(i).id).id,repoGroupStudents.getByIndex(i).name);
                }
            }
          }
}

void DialogLinkGroupSubjectWindow::editDataRepoSubject(RepositoryTemplate<Subject> repoSubjects){
    //Проверка на изменения(удаление, добавление, редактирование) репозиториев в главной вкладке
    if (repoRecSubject.getAmount()==0){
        for (int i =0; i<repoSubjects.getAmount(); i++){
            repoRecSubject.add(repoSubjects.getByIndex(i));
        }

    }else
          if (repoSubjects.getAmount()>repoRecSubject.getAmount()){
            int raz = repoSubjects.getAmount()-repoRecSubject.getAmount();
            int addE = repoRecSubject.getAmount();
            for (int i =0; i<raz; i++){
                repoRecSubject.add(repoSubjects.getById(repoSubjects.getByIndex(addE).id));
                ++addE;
            }
    }else
          if (repoSubjects.getAmount()<repoRecSubject.getAmount()){
            int raz = repoRecSubject.getAmount()-repoSubjects.getAmount();
            int delE = repoRecSubject.getAmount()-1;
            for (int i =0; i<raz; i++){
                repoRecSubject.removeByIndex(delE);
            --delE;
            }
    }
    else
         if (repoSubjects.getAmount()==repoRecSubject.getAmount()){
            for (int i =0; i<repoSubjects.getAmount(); i++){
                if (repoSubjects.getByIndex(i).name!=repoRecSubject.getByIndex(i).name){
                    repoRecSubject.update(repoSubjects.getById(repoSubjects.getByIndex(i).id).id,repoSubjects.getByIndex(i).name);
                }
            }
          }
  }
void DialogLinkGroupSubjectWindow::closeEvent(QCloseEvent *){
    if (list_s->size()!=0){
      list_s->clear();
      clearTableView(table_subject,sub_model);
    }
}

