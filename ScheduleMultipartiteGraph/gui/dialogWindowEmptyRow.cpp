#include "dialogWindowEmptyRow.h"
#include <qpushbutton.h>
#include <qlineedit.h>
#include <qlabel.h>
#include <qlayout.h>
#include <qcheckbox.h>
#include <QDebug>

DialogWindowEmptyRow::DialogWindowEmptyRow(QWidget* parent): QDialog(parent)
{
  this->setWindowTitle("Предупреждение");


  applyButton=new QPushButton("OK",this);
  applyButton->setMaximumWidth(80);

  QLabel *label_msg=new QLabel();
  label_msg->setText("                             Ваша запись пуста.\n"
                     "Пожалуйста добавьте данные и нажмите кнопку ок");
  connect(applyButton,SIGNAL(clicked()),this,SLOT(clicked_btn()));


  QVBoxLayout *mainlayout=new QVBoxLayout(this);
  mainlayout->addWidget(label_msg,0,Qt::AlignHCenter);
  mainlayout->addWidget(applyButton,0,Qt::AlignHCenter);




}

DialogWindowEmptyRow::~DialogWindowEmptyRow(){

}
void DialogWindowEmptyRow::clicked_btn(){
        this->close();

}
