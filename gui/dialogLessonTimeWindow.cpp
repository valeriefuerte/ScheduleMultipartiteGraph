#include <qpushbutton.h>
#include <QDateTime>
#include <QDateTimeEdit>
#include <QLineEdit>
#include <QDate>
#include <QTime>
#include <QDebug>
#include <QDialog>
#include "dialogLessonTimeWindow.h"


DialogLessonTimeWindow::DialogLessonTimeWindow(QWidget* parent): QDialog(parent)
{
    this->setWindowTitle("Данные");
    applyButton = new QPushButton("OK");
    applyButton->setMaximumWidth(80);

    formLayout = new QFormLayout();
    btnLayout=new QVBoxLayout();

    btnLayout->addWidget(applyButton);

    dateTimeEdit = new QDateTimeEdit(QDate::currentDate());
    timeEdit = new QDateTimeEdit(QTime::currentTime());

    formLayout->addRow("дата",dateTimeEdit);
    formLayout->addRow("время",timeEdit);

    formLayout->addWidget(applyButton);
    setLayout(formLayout);

    repoTime = new RepositoryGeneral<LessonTime>;

    connect(applyButton,SIGNAL(clicked()),this,SLOT(apply_clicked()));


}

DialogLessonTimeWindow::~DialogLessonTimeWindow(){

}

void DialogLessonTimeWindow::apply_clicked(){
    LessonTime *lt = new LessonTime(timeEdit->time(),dateTimeEdit->date());
    repoTime->add(*lt);
    qDebug()<<repoTime->getById(0).datetime;
}
