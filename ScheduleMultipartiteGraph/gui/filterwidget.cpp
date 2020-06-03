#include "filterwidget.h"
#include "ui_filterwidget.h"
#include <QDebug>
FilterWidget::FilterWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FilterWidget)
{
    ui->setupUi(this);
    connect(this->ui->useFilter,&QPushButton::clicked,this,&FilterWidget::getFilterData);

}

FilterWidget::~FilterWidget()
{
    delete ui;
}

FilterData FilterWidget::getFilterData()
{

    FilterData data;
    qDebug()<<"usingFilter";
    return data;
    //Example
    //data.someData1 = ui->comboBox->currentText();
}
