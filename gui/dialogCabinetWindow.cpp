#include "dialogCabinetWindow.h"
#include <qpushbutton.h>
#include <qlineedit.h>
#include <qlabel.h>
#include <qlayout.h>
#include <qcheckbox.h>
#include <QDebug>
#include<QFormLayout>
#include<models/repository/repositorygeneral.h>
#include<models/cabinet.h>
#include <gui/mainwindow.h>

 DialogCabinetWindow::DialogCabinetWindow(QWidget* parent): QDialog(parent)
{
   repoCabinets=new RepositoryGeneral<Cabinet>;
   flag = false;
   this->setWindowTitle("Данные");
   applyButton = new QPushButton("OK");
   applyButton->setMaximumWidth(80);


   formLayout = new QFormLayout();
   btnLayout=new QVBoxLayout();

   btnLayout->addWidget(applyButton);

   numberLineEdit = new QLineEdit();
   floorLineEdit = new QLineEdit();
   buildingLineEdit = new QLineEdit();

   formLayout->addRow("Корпус",buildingLineEdit);
   formLayout->addRow("Этаж",floorLineEdit);
   formLayout->addRow("Номер",numberLineEdit);


   formLayout->addWidget(applyButton);
   setLayout(formLayout);
   connect(applyButton,SIGNAL(clicked()),this,SLOT(apply_clicked()));
   //connect(ui,SIGNAL(sendSelectionCabinet(Cabinet cabinet)),this,SLOT(receiveSelectionCabinet(RepositoryGeneral*)));

}

DialogCabinetWindow::~DialogCabinetWindow(){
    delete this;
}

void DialogCabinetWindow::apply_clicked(){
    int number = numberLineEdit->text().toInt();
    int floor = floorLineEdit->text().toInt();
    int building=buildingLineEdit->text().toInt();
    Cabinet *cabinet = new Cabinet(number,floor,building);
    repoCabinets->add(*cabinet);
    emit sendDataCabinet(repoCabinets);

    numberLineEdit->clear();
    floorLineEdit->clear();
    buildingLineEdit->clear();
    repoCabinets->remove(0);
    this->close();


}
void DialogCabinetWindow::receiveSelectionCabinet(RepositoryGeneral<Cabinet> *repoCabinet){
 qDebug()<<"hello";
}


