#ifndef FILTERWIDGET_H
#define FILTERWIDGET_H

#include <QWidget>
#include "models/filterdata.h"
namespace Ui {
class FilterWidget;
}


class FilterWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FilterWidget(QWidget *parent = nullptr);

    ~FilterWidget();
signals:
    void filterDone();
public slots:
    FilterData getFilterData();

private:
    Ui::FilterWidget *ui;
};

#endif // FILTERWIDGET_H
