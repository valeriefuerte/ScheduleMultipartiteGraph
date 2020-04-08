#include "dialogGroupWindow.h"
#include <qpushbutton.h>
#include <qlineedit.h>
#include <qlabel.h>
#include <qlayout.h>
#include <qcheckbox.h>
#include <QDebug>
#include<QFormLayout>
#include<models/repository/repositorytemplate.h>
#include<models/groupstudents.h>
#include <gui/mainwindow.h>

 DialogGroupWindow::DialogGroupWindow(QWidget* parent): QDialog(parent)
{
   flag = false;

   applyButton = new QPushButton("OK");
   applyButton->setMaximumWidth(80);


   formLayout = new QFormLayout();
   btnLayout=new QVBoxLayout();
   btnLayout->addWidget(applyButton);

   groupLineEdit = new QLineEdit();

   formLayout->addRow("Группа",groupLineEdit);
   formLayout->addWidget(applyButton);

   setLayout(formLayout);
   connect(applyButton,SIGNAL(clicked()),this,SLOT(apply_clicked()));
 }

 void DialogGroupWindow::clearLineEdit(){
       groupLineEdit->clear();
 }


DialogGroupWindow::~DialogGroupWindow(){
    delete this;
}

void DialogGroupWindow::apply_clicked(){
if (!flag){
    emit sendDataGroup(GroupStudents(groupLineEdit->text()));
    this->close();
 } else if (flag){
     emit sendEditDataGroup(GroupStudents(groupLineEdit->text()));
    this->close();
 }
    flag = false;
}

void DialogGroupWindow::editTitle(){
    this->setWindowTitle("Редактирование");
}
void DialogGroupWindow::addTitle(){
    this->setWindowTitle("Добавление");
}

void DialogGroupWindow::outputEditData(GroupStudents groupEdit){
    flag = true;
    groupLineEdit->setText(groupEdit.name);
}
