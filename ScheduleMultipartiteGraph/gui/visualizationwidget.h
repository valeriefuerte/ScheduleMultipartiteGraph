#ifndef VISUALIZATIONWIDGET_H
#define VISUALIZATIONWIDGET_H

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QSlider>
#include <QGroupBox>
#include <QBoxLayout>
#include "filterwidget.h"
#include "gui/graphwidget.h"

class GraphWidget;

//
//@brief в конструкторе (mainwindow.cpp) добавить
// VisualizationWidget *w = new VisualizationWidget();
//ui->tabWidget->addTab(w,"GraphWidgetDemo");
// (не забудьте об #include)
class VisualizationWidget : public QWidget
{
    Q_OBJECT
public:
    explicit VisualizationWidget(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *event) override;

signals:

public slots:
    void resetGraphWidget();
private:
    //виджет визуализации графа
    GraphWidget *graphWidget;
    //меню
    QGroupBox *menu;
    QBoxLayout *visualGraphLayout;
    //функция по созданию меню
    QGroupBox *createMenu();
    FilterWidget *filter;
};

#endif // VISUALIZATIONWIDGET_H
