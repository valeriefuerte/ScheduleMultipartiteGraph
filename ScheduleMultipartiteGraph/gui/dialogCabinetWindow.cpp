#include "dialogCabinetWindow.h"
#include <qpushbutton.h>
#include <qlineedit.h>
#include <qlabel.h>
#include <qlayout.h>
#include <qcheckbox.h>
#include <QDebug>
#include<QFormLayout>
#include <QMessageBox>
#include<models/repository/repositorytemplate.h>
#include<models/cabinet.h>
#include <gui/mainwindow.h>

 DialogCabinetWindow::DialogCabinetWindow(QWidget* parent): QDialog(parent)
{
   flag = false;
   addEmpty=false;

   //this->setWindowTitle("Данные");
   applyButton = new QPushButton("OK");
   applyButton->setMaximumWidth(80);


   formLayout = new QFormLayout();
   btnLayout=new QVBoxLayout();

   btnLayout->addWidget(applyButton);

   numberLineEdit = new QLineEdit();
   floorLineEdit = new QLineEdit();
   buildingLineEdit = new QLineEdit();

   buildingLineEdit->setValidator(new QIntValidator(0,100,this));
   floorLineEdit->setValidator(new QIntValidator(0,10,this));
   numberLineEdit->setValidator(new QIntValidator(0,100,this));

   formLayout->addRow("Корпус",buildingLineEdit);
   formLayout->addRow("Этаж",floorLineEdit);
   formLayout->addRow("Номер",numberLineEdit);

   formLayout->addWidget(applyButton);
   setLayout(formLayout);
   connect(applyButton,SIGNAL(clicked()),this,SLOT(apply_clicked()));
 }

 void DialogCabinetWindow::clearLineEdit(){
     numberLineEdit->clear();
     floorLineEdit->clear();
     buildingLineEdit->clear();
 }

DialogCabinetWindow::~DialogCabinetWindow(){
    delete this;
}

void DialogCabinetWindow::apply_clicked(){

  int number = numberLineEdit->text().toInt();
  int floor = floorLineEdit->text().toInt();
  int building = buildingLineEdit->text().toInt();
  if ((numberLineEdit->text().isEmpty()&&floorLineEdit->text().isEmpty()&&buildingLineEdit->text().isEmpty())){
          QMessageBox::information(this,"Ошибка","Заполнены не все поля ввода!");
   }
    else if ((numberLineEdit->text().isEmpty()&&!floorLineEdit->text().isEmpty()&&!buildingLineEdit->text().isEmpty())) {
      QMessageBox::information(this,"Ошибка","Заполнены не все поля ввода!");

    }
  else if ((numberLineEdit->text().isEmpty()&&floorLineEdit->text().isEmpty()&&!buildingLineEdit->text().isEmpty())) {
      QMessageBox::information(this,"Ошибка","Заполнены не все поля ввода!");

    }
  else if ((numberLineEdit->text().isEmpty()&&!floorLineEdit->text().isEmpty()&&buildingLineEdit->text().isEmpty())) {
      QMessageBox::information(this,"Ошибка","Заполнены не все поля ввода!");
    }
  else if ((!numberLineEdit->text().isEmpty()&&floorLineEdit->text().isEmpty()&&!buildingLineEdit->text().isEmpty())) {
      QMessageBox::information(this,"Ошибка","Заполнены не все поля ввода!");
    }
  else if ((!numberLineEdit->text().isEmpty()&&floorLineEdit->text().isEmpty()&&buildingLineEdit->text().isEmpty())) {
      QMessageBox::information(this,"Ошибка","Заполнены не все поля ввода!");
    }
  else if ((!numberLineEdit->text().isEmpty()&&!floorLineEdit->text().isEmpty()&&buildingLineEdit->text().isEmpty())) {
      QMessageBox::information(this,"Ошибка","Заполнены не все поля ввода!");
    }
else {
        if (!flag){
            Cabinet cabinet(number,floor,building);
            emit sendDataCabinet(cabinet);
        } else if (flag){
            emit sendEditDataCabinet(Cabinet(numberLineEdit->text().toInt(),floorLineEdit->text().toInt(),buildingLineEdit->text().toInt()));

        }
        flag = false;
    }

}

void DialogCabinetWindow::editTitle(){
    this->setWindowTitle("Редактирование");
}
void DialogCabinetWindow::addTitle(){
    this->setWindowTitle("Добавление");
}

void DialogCabinetWindow::outputEditData(Cabinet cabinetEdit){
    flag = true;

    buildingLineEdit->setText(QString("%1").arg(cabinetEdit.building));
    floorLineEdit->setText(QString("%1").arg(cabinetEdit.floor));
    numberLineEdit->setText(QString("%1").arg(cabinetEdit.number));

}



