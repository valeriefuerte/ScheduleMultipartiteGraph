#include "visualizationwidget.h"
#include "gui/graphwidget.h"
#include <QHBoxLayout>
VisualizationWidget::VisualizationWidget(QWidget *parent) : QWidget(parent),
  graphWidget(new GraphWidget(this)),
  menu(createMenu())

{

  //  QHBoxLayout *HLay = new
   // slider->setOrientation(Qt::Horizontal);
    // slider->setRange(0,10);
}

void VisualizationWidget::resetGraphWidget()
{

}

QGroupBox* VisualizationWidget::createMenu()
{
    QGroupBox *nmenu = new QGroupBox(this);
    QPushButton *resetButton = new QPushButton("RESET");

    QSlider *slider = new QSlider();
    slider->setOrientation(Qt::Horizontal);

    connect(resetButton,&QPushButton::clicked,graphWidget,&GraphWidget::resetFilter);

    QHBoxLayout *layout = new QHBoxLayout();
    layout->addWidget(resetButton);
    layout->addWidget(slider);
    nmenu->setLayout(layout);
    return nmenu;

}
