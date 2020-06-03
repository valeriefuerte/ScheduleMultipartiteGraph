#include <qpushbutton.h>
#include <QComboBox>
#include <QDateTime>
#include <QDateTimeEdit>
#include <QLineEdit>
#include <QDate>
#include <QTime>
#include <QDebug>
#include <QDialog>
#include <QMessageBox>
#include "dialogLessonTimeWindow.h"


DialogLessonTimeWindow::DialogLessonTimeWindow(QWidget* parent): QDialog(parent)
{
    this->setWindowTitle("Данные");
    applyButton = new QPushButton("OK");
    applyButton->setMaximumWidth(80);
    dayList = new QComboBox();

    hashAddDay["Понедельник"]=1;
    hashAddDay["Вторник"]=2;
    hashAddDay["Среда"]=3;
    hashAddDay["Четверг"]=4;
    hashAddDay["Пятница"]=5;
    hashAddDay["Суббота"]=6;

    hashEditDay[1]="Понедельник";
    hashEditDay[2]="Вторник";
    hashEditDay[3]="Среда";
    hashEditDay[4]="Четверг";
    hashEditDay[5]="Пятница";
    hashEditDay[6]="Суббота";

    dayList->addItem("Понедельник");
    dayList->addItem("Вторник");
    dayList->addItem("Среда");
    dayList->addItem("Четверг");
    dayList->addItem("Пятница");
    dayList->addItem("Суббота");

    formLayout = new QFormLayout();
    btnLayout=new QVBoxLayout();

    parityEdit = new QLineEdit();
    dayWeekEdit = new QLineEdit();
    timeEdit = new QDateTimeEdit(QTime(0,0));

    btnLayout->addWidget(applyButton);
    parityEdit->setValidator(new QIntValidator(0,2,this));
    dayWeekEdit->setValidator(new QIntValidator(0,7,this));

    formLayout->addRow("Четность недели",parityEdit);
    formLayout->addRow("День недели",dayList);
    formLayout->addRow("Время",timeEdit);

    formLayout->addWidget(applyButton);
    setLayout(formLayout);
    connect(applyButton,SIGNAL(clicked()),this,SLOT(apply_clicked()));
}

DialogLessonTimeWindow::~DialogLessonTimeWindow(){

}

void DialogLessonTimeWindow::apply_clicked(){
if (parityEdit->text().isEmpty()&&timeEdit->text()=="  :00"){
    QMessageBox::information(this,"Ошибка","Заполнены не все поля ввода!");
}
 else if (!parityEdit->text().isEmpty()&&timeEdit->text()=="  :00"){

    QMessageBox::information(this,"Ошибка","Заполнены не все поля ввода!");
}
else if (parityEdit->text().isEmpty()&&timeEdit->text()!="  :00"){

   QMessageBox::information(this,"Ошибка","Заполнены не все поля ввода!");
}
else if (!flag){

        emit sendDataLessonTime(LessonTime(parityEdit->text().toInt(),hashAddDay[dayList->currentText()],timeEdit->time()));

   } else if (flag){
        emit sendEditDataLessonTime(LessonTime(parityEdit->text().toInt(),hashAddDay[dayList->currentText()],timeEdit->time()));

   }
     flag = false;
}

void DialogLessonTimeWindow::editTitle(){
    this->setWindowTitle("Редактирование");
}
void DialogLessonTimeWindow::addTitle(){
    this->setWindowTitle("Добавление");
}
void DialogLessonTimeWindow::clearLineEdit(){
    parityEdit->clear();
    dayWeekEdit->clear();
    timeEdit->clear();
}

void DialogLessonTimeWindow::outputEditData(LessonTime lessonEdit){
    flag = true;

    parityEdit->setText(QString("%1").arg(lessonEdit.parity));
    dayList->setCurrentText(hashEditDay[lessonEdit.dayOfWeek]);
    //dayWeekEdit->setText(QString("%1").arg(lessonEdit.dayOfWeek));
    timeEdit->setTime(lessonEdit.time);
}
