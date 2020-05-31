#include "dialogSubjectWindow.h"
#include <qpushbutton.h>
#include <qlineedit.h>
#include <qlabel.h>
#include <qlayout.h>
#include <qcheckbox.h>
#include <QDebug>
#include<QFormLayout>
#include <QMessageBox>
#include<models/repository/repositorytemplate.h>
#include<models/subject.h>
#include <gui/mainwindow.h>

 DialogSubjectWindow::DialogSubjectWindow(QWidget* parent): QDialog(parent)
{
   flag = false;

   applyButton = new QPushButton("OK");
   applyButton->setMaximumWidth(80);

   formLayout = new QFormLayout();
   btnLayout=new QVBoxLayout();
   btnLayout->addWidget(applyButton);

   subjectLineEdit = new QLineEdit();


   formLayout->addRow("Предмет",subjectLineEdit);
   formLayout->addWidget(applyButton);

   setLayout(formLayout);
   connect(applyButton,SIGNAL(clicked()),this,SLOT(apply_clicked()));
 }

 void DialogSubjectWindow::clearLineEdit(){
       subjectLineEdit->clear();
 }


DialogSubjectWindow::~DialogSubjectWindow(){
    delete this;
}

void DialogSubjectWindow::apply_clicked(){
   if (!subjectLineEdit->text().isEmpty()){
        if (!flag){

            emit sendDataSubject(Subject (subjectLineEdit->text()));

        } else if (flag){
            emit sendEditDataSubject(Subject(subjectLineEdit->text()));

        }
    flag = false;
   }
   else {
       QMessageBox::information(this,"Ошибка","Поле ввода пусто!");
   }

}

void DialogSubjectWindow::editTitle(){
    this->setWindowTitle("Редактирование");
}
void DialogSubjectWindow::addTitle(){
    this->setWindowTitle("Добавление");
}

void DialogSubjectWindow::outputEditData(Subject cabinetEdit){
    flag = true;
    subjectLineEdit->setText(cabinetEdit.name);
}



