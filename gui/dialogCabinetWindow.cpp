#include "dialogCabinetWindow.h"
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

 DialogCabinetWindow::DialogCabinetWindow(QWidget* parent): QDialog(parent)
{
   repoCabinets=new RepositoryTemplate<Cabinet>;
   flag = false;
   addEmpty=false;

   this->setWindowTitle("Данные");
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
    int building=buildingLineEdit->text().toInt();
    Cabinet cabinet(number,floor,building);
    emit sendDataCabinet(cabinet);
    this->close();
}
void DialogCabinetWindow::receiveSelectionCabinet(Cabinet cabinet){

}


