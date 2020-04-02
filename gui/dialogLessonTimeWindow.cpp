#include <qpushbutton.h>
#include <QDateTime>
#include <QDateTimeEdit>
#include <QLineEdit>
#include <QDate>
#include <QTime>
#include <QDebug>
#include "dialogLessonTimeWindow.h"


dialogLessonTimeWindow::dialogLessonTimeWindow()
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

    qDebug()<<dateTimeEdit->dateTime();




}
