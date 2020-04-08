#include "gui/dialogWindowConfrimEditRow.h"
#include <qpushbutton.h>
#include <qlineedit.h>
#include <qlabel.h>
#include <qlayout.h>
#include <qcheckbox.h>
#include <QDebug>

DialogWindowConfirmEditRow::DialogWindowConfirmEditRow(QWidget* parent): QDialog(parent)
{
  this->setWindowTitle("Предупреждение");


  applyButton=new QPushButton("OK",this);
  applyButton->setMaximumWidth(80);

  QLabel *label_msg=new QLabel();
  label_msg->setText("Пожалуйста, подтвердите добавление");
  connect(applyButton,SIGNAL(clicked()),this,SLOT(clicked_btn()));


  QVBoxLayout *mainlayout=new QVBoxLayout(this);
  mainlayout->addWidget(label_msg,0,Qt::AlignHCenter);
  mainlayout->addWidget(applyButton,0,Qt::AlignHCenter);




}

DialogWindowConfirmEditRow::~DialogWindowConfirmEditRow(){

}
void DialogWindowConfirmEditRow::clicked_btn(){
        this->close();

}
