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
    this->setWindowTitle("Добавление предмета");
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

    for (int i =0; i<repoGroupStud.getAmount(); i++){
        receiveRepGroup.add(repoGroupStud.getById(i));
    }

    for (int i =0; i<repoSubject.getAmount(); i++){
      receiveRepSubject.add(repoSubject.getById(i));
    }
    nameGroup->setText(repoGroupStud.getById(repoGroupStud.getByIndex(indexGroup).id).name);
    nameSubject->setText(repoSubject.getById(repoSubject.getByIndex(indexSubject).id).name);


}
void DialogAddLinkGroupSubject::apply_clicked(){
    int academic= academHours->text().toInt();
    repoLinkGrSub.add(LinkGroupSubject(receiveRepGroup.getById(receiveRepGroup.getByIndex(indexRGroup).id).id,
                     receiveRepSubject.getById(receiveRepSubject.getByIndex(indexRSub).id).id, academic));
   emit sendRepoGroupSubject(repoLinkGrSub,receiveRepSubject.getById(receiveRepSubject.getByIndex(indexRSub).id).name);
   academHours->clear();
   this->close();
 }


