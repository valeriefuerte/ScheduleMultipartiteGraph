#include "dialogAddlinkGroupSubject.h"
#include <qpushbutton.h>
#include <qlineedit.h>
#include <qlabel.h>
#include <qlayout.h>
#include <qcheckbox.h>
#include <QDebug>
#include <qvalidator.h>
#include<QFormLayout>
#include <QMessageBox>
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


    nameGroup->setText(repoGroupStud.getById(repoGroupStud.getByIndex(indexGroup).id).name);
    nameSubject->setText(repoSubject.getById(repoSubject.getByIndex(indexRSub).id).name);


}
void DialogAddLinkGroupSubject::apply_clicked(){

  int academic= academHours->text().toInt();
  if (academHours->text()==""||academic==0){
      QMessageBox::information(this,"Ошибка","Поле ввода пусто или равно 0!");
      return;
  }
  if (!changeAcH){
     emit sendRepoGroupSubject(LinkGroupSubject(receiveRepGroup.getByIndex(indexRGroup).id,
     receiveRepSubject.getById(receiveRepSubject.getByIndex(indexRSub).id).id, academic),receiveRepSubject.getById(receiveRepSubject.getByIndex(indexRSub).id).name);
   }
   else
  {
    changeObject.academicHours=academic;
    emit sendChangeAcH(nameSubject->text(), changeObject);
  }

   changeAcH=false;

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
     receiveRepGroup=repoGroupStudents;
}

void DialogAddLinkGroupSubject::editDataRepoSubject(RepositoryTemplate<Subject> repoSubjects){
    //Проверка на изменения(удаление, добавление, редактирование) репозиториев в главной вкладке
  receiveRepSubject=repoSubjects;
  }

void DialogAddLinkGroupSubject::closeEvent(QCloseEvent *){
    academHours->clear();

}

