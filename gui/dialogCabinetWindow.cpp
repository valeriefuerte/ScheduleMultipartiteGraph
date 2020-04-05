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
   Cabinet *c=new Cabinet();
   repoCabinets->add(*c);

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
    if (!flag){
    int number = numberLineEdit->text().toInt();
    int floor = floorLineEdit->text().toInt();
    int building=buildingLineEdit->text().toInt();
        if (buildingLineEdit->text()==""||floorLineEdit->text()==""||numberLineEdit->text()==""){
            addEmpty = true;
            DialogWindowEmptyRow *cer = new DialogWindowEmptyRow();
            cer->show();
        }else{
            Cabinet *cabinet = new Cabinet(number,floor,building);
            repoCabinets->update(0,*cabinet);
            emit sendDataCabinet(repoCabinets);
       }
}else{
        qDebug()<<"Размер транзита до редактирования"<<repoCabinets->currentCount;
        //Получение изменных значений
        int buildingCh=buildingLineEdit->text().toInt();
        int floorCh = floorLineEdit->text().toInt();
        int numberCh = numberLineEdit->text().toInt();
        Cabinet *changCabinet =new Cabinet(numberCh,floorCh,buildingCh);

        repoCabinets->update(0,*changCabinet);

        QList<Cabinet> cab;
        cab = repoCabinets->getAll();
        qDebug()<<"Output Dialog";
        foreach (Cabinet c, cab) {
            qDebug()<<c.building<<c.floor<<c.number;
        }
        cab.clear();
        emit sendEditDataCabinet(repoCabinets);
    }
if (!addEmpty){
        numberLineEdit->clear();
        floorLineEdit->clear();
        buildingLineEdit->clear();
        //repoCabinets->remove(0);
        qDebug()<<"Размер транзита"<<repoCabinets->currentCount;
        QList<Cabinet> cab;
        /*cab = repoCabinets->getAll();
        qDebug()<<"after remove Dialog";
        foreach (Cabinet c, cab) {
            qDebug()<<c.building<<c.floor<<c.number;
        }*/
        qDebug()<<repoCabinets->getById(0).building<<repoCabinets->getById(0).floor<<repoCabinets->getById(0).number;
        flag = false;
        this->close();
        }
else {
    addEmpty=false;
}
}
void DialogCabinetWindow::receiveSelectionCabinet(Cabinet cabinet){
    flag = true;
    //Вывод значений из главной формы
    QString building = QString::number(cabinet.building);
    QString number = QString::number(cabinet.number);
    QString floor = QString::number(cabinet.floor);
    buildingLineEdit->setText(building);
    numberLineEdit->setText(number);
    floorLineEdit->setText(floor);
}


