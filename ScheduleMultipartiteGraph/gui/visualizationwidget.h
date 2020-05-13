#ifndef VISUALIZATIONWIDGET_H
#define VISUALIZATIONWIDGET_H

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QSlider>
#include <QGroupBox>
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

signals:

public slots:
    void resetGraphWidget();
private:
    GraphWidget *graphWidget;
    QGroupBox *menu;
    QGroupBox *createMenu();
};

#endif // VISUALIZATIONWIDGET_H
