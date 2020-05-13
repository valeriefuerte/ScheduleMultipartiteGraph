#include "dialogAddlinkGroupSubject.h"
#include <qpushbutton.h>
#include <qlineedit.h>
#include <qlabel.h>
#include <qlayout.h>
#include <qcheckbox.h>
#include <QDebug>
#include <qvalidator.h>
#include<QFormLayout>
#include <models/repository/repositorytemplate.h>
#include <models/groupstudents.h>
#include <models/subject.h>

DialogAddLinkGroupSubject::DialogAddLinkGroupSubject(QWidget* parent): QDialog(parent)
{

    nameGroup = new QLabel();
    nameSubject = new QLabel();

    applyButton = new QPushButton("OK");
    applyButton->setMaximumWidth(80);

    academHours = new QLineEdit();
    academHours->setValidator(new QIntValidator(0,500,this));

    formLayout = new QFormLayout();

    btnLayout=new QVBoxLayout();
    btnLayout->addWidget(applyButton);

    formLayout->addRow("Группа:",nameGroup);
    formLayout->addRow("Предмет:",nameSubject);
    formLayout->addRow("Академические часы",academHours);
    formLayout->addWidget(applyButton);
    setLayout(formLayout);
    connect(applyButton,SIGNAL(clicked()),this,SLOT(apply_clicked()));
}
DialogAddLinkGroupSubject::~DialogAddLinkGroupSubject(){
    delete this;
}
void DialogAddLinkGroupSubject::addLinkGroupSubject(int indexGroup,int indexSubject,
                                   RepositoryTemplate<GroupStudents> repoGroupStud, RepositoryTemplate<Subject> repoSubject ){
    indexRGroup = indexGroup;
    indexRSub = indexSubject;

    editDataRepoGroup(repoGroupStud);
    editDataRepoSubject(repoSubject);

        /*qDebug()<<"RepoGroupStudents: ";
        for (int i = 0; i<repoGroupStud.getAmount(); i++){
            qDebug()<<repoGroupStud.getByIndex(i).name;
        }
        qDebug()<<"RepoRecGroupStudents: ";
        for (int i = 0; i<receiveRepGroup.getAmount(); i++){
            qDebug()<<receiveRepGroup.getByIndex(i).name;
        }
        qDebug()<<"RepoSubjects: ";
       for (int i = 0; i<repoSubject.getAmount(); i++){
           qDebug()<<repoSubject.getByIndex(i).name;
       }
       qDebug()<<"RepoRecSubjects: ";
       for (int i = 0; i<receiveRepSubject.getAmount(); i++){
           qDebug()<<receiveRepSubject.getByIndex(i).name;
       }*/

           /*qDebug()<<"RepoSubject: "<<repoSubjects.getAmount()<<"RepoSubject: "<<repoRecSubject.getAmount();
           for (int i =0; i<repoRecSubject.getAmount(); i++){
                qDebug()<<repoRecSubject.getById(i).name;
          }*/

    nameGroup->setText(repoGroupStud.getById(repoGroupStud.getByIndex(indexGroup).id).name);
    nameSubject->setText(repoSubject.getById(repoSubject.getByIndex(indexRSub).id).name);


}
void DialogAddLinkGroupSubject::apply_clicked(){

  int academic= academHours->text().toInt();

  if (!changeAcH){
     emit sendRepoGroupSubject(LinkGroupSubject(receiveRepGroup.getById(receiveRepGroup.getByIndex(indexRGroup).id).id,
     receiveRepSubject.getById(receiveRepSubject.getByIndex(indexRSub).id).id, academic),receiveRepSubject.getById(receiveRepSubject.getByIndex(indexRSub).id).name);
   }
   else
  {
    changeObject.academicHours=academic;
    emit sendChangeAcH(nameSubject->text(), changeObject);
  }

   changeAcH=false;
   this->close();
 }


void DialogAddLinkGroupSubject::receiveSelecteDataRepoGrSub(QString nameGr,QString nameSub,LinkGroupSubject gr_sub){

    nameGroup->setText(nameGr);
    nameSubject->setText(nameSub);
    academHours->setText(QString("%1").arg(gr_sub.academicHours));

    changeObject = gr_sub;
    changeAcH=true;
}


void DialogAddLinkGroupSubject::setTitle(){

    this->setWindowTitle("Добавление предмета");
}

void DialogAddLinkGroupSubject::changeTitle(){
    this->setWindowTitle("Изменение академических часов");
}

void DialogAddLinkGroupSubject::editDataRepoGroup(RepositoryTemplate<GroupStudents> repoGroupStudents){
    //Проверка на изменения(удаление, добавление, редактирование) репозиториев в главной вкладке
    if (receiveRepGroup.getAmount()==0){
        for (int i =0; i<repoGroupStudents.getAmount(); i++){
            receiveRepGroup.add(repoGroupStudents.getByIndex(i));
        }

    }else
          if (repoGroupStudents.getAmount()>receiveRepGroup.getAmount()){
            int raz = repoGroupStudents.getAmount()-receiveRepGroup.getAmount();
            int addE = receiveRepGroup.getAmount();
            for (int i =0; i<raz; i++){
                receiveRepGroup.add(repoGroupStudents.getByIndex(i));
                ++addE;
            }
    }else
          if (repoGroupStudents.getAmount()<receiveRepGroup.getAmount()){
            int raz = receiveRepGroup.getAmount()-repoGroupStudents.getAmount();
            int delE = receiveRepGroup.getAmount()-1;
            for (int i =0; i<raz; i++){
                receiveRepGroup.removeByIndex(delE);
            --delE;
            }
    }
    else
         if (repoGroupStudents.getAmount()==receiveRepGroup.getAmount()){
            for (int i =0; i<repoGroupStudents.getAmount(); i++){
                if (repoGroupStudents.getById(repoGroupStudents.getByIndex(i).id).name!=receiveRepGroup.getById(receiveRepGroup.getByIndex(i).id).name){
                    receiveRepGroup.update(receiveRepGroup.getById(receiveRepGroup.getByIndex(i).id).id,repoGroupStudents.getById(repoGroupStudents.getByIndex(i).id).name);
                }
            }
          }
}

void DialogAddLinkGroupSubject::editDataRepoSubject(RepositoryTemplate<Subject> repoSubjects){
    //Проверка на изменения(удаление, добавление, редактирование) репозиториев в главной вкладке
    if (receiveRepSubject.getAmount()==0){
        for (int i =0; i<repoSubjects.getAmount(); i++){
            receiveRepSubject.add(repoSubjects.getByIndex(i));
        }

    }else
          if (repoSubjects.getAmount()>receiveRepSubject.getAmount()){
            int raz = repoSubjects.getAmount()-receiveRepSubject.getAmount();
            int addE = receiveRepSubject.getAmount();
            for (int i =0; i<raz; i++){
                receiveRepSubject.add(repoSubjects.getByIndex(addE));
                ++addE;
            }
    }else
          if (repoSubjects.getAmount()<receiveRepSubject.getAmount()){
            int raz = receiveRepSubject.getAmount()-repoSubjects.getAmount();
            int delE = receiveRepSubject.getAmount()-1;
            for (int i =0; i<raz; i++){
                receiveRepSubject.removeByIndex(delE);
            --delE;
            }
    }
    else
         if (repoSubjects.getAmount()==receiveRepSubject.getAmount()){
            for (int i =0; i<repoSubjects.getAmount(); i++){
                if (repoSubjects.getById(repoSubjects.getByIndex(i).id).name!=receiveRepSubject.getById(receiveRepSubject.getByIndex(i).id).name){
                    receiveRepSubject.update(receiveRepSubject.getById(receiveRepSubject.getByIndex(i).id).id,repoSubjects.getById(repoSubjects.getByIndex(i).id).name);
                }
            }
          }
  }

void DialogAddLinkGroupSubject::closeEvent(QCloseEvent *){
    academHours->clear();
}

