#include "scheduletableview.h"


#include <QScrollBar>
#include <QHeaderView>
#include "models/scheduletableabstractmodule.h"

ScheduleTableView::ScheduleTableView(QAbstractItemModel * model, QWidget *parent):QTableView(parent)
{
    setModel(model);
    frozenTableView = new QTableView(this);
    this->setSortingEnabled(true);
    init();

    //connect the headers and scrollbars
    connect(horizontalHeader(),&QHeaderView::sectionResized, this,
            &ScheduleTableView::updateSectionWidth);
    connect(verticalHeader(),&QHeaderView::sectionResized, this,
            &ScheduleTableView::updateSectionHeight);

    connect(frozenTableView->verticalScrollBar(), &QAbstractSlider::valueChanged,
            verticalScrollBar(), &QAbstractSlider::setValue);
    connect(verticalScrollBar(), &QAbstractSlider::valueChanged,
            frozenTableView->verticalScrollBar(), &QAbstractSlider::setValue);


}


ScheduleTableView::~ScheduleTableView()
{
    delete frozenTableView;
}

void ScheduleTableView::changeModel(QAbstractItemModel *model)
{
    setModel(model);
    frozenTableView->setModel(this->model());
}


void ScheduleTableView::init()
{
    frozenTableView->setModel(model());
    frozenTableView->setSortingEnabled(true);
    frozenTableView->setFocusPolicy(Qt::NoFocus);
    frozenTableView->verticalHeader()->hide();
    frozenTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);

    viewport()->stackUnder(frozenTableView);



    frozenTableView->setStyleSheet("QTableView { border: none;"
                                   "background-color: #8EDE21;"
                                   "selection-background-color: #999}");
    frozenTableView->setSelectionModel(selectionModel());
    for (int col = 1; col < model()->columnCount(); ++col)
        frozenTableView->setColumnHidden(col, true);

    frozenTableView->setColumnWidth(0, columnWidth(0) );

    frozenTableView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    frozenTableView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    frozenTableView->show();

    updateFrozenTableGeometry();

    setHorizontalScrollMode(ScrollPerPixel);
    setVerticalScrollMode(ScrollPerPixel);
    frozenTableView->setVerticalScrollMode(ScrollPerPixel);
}




void ScheduleTableView::updateSectionWidth(int logicalIndex, int /* oldSize */, int newSize)
{
    if (logicalIndex == 0){
        frozenTableView->setColumnWidth(0, newSize);
        updateFrozenTableGeometry();
    }
}

void ScheduleTableView::updateSectionHeight(int logicalIndex, int /* oldSize */, int newSize)
{
    frozenTableView->setRowHeight(logicalIndex, newSize);
}
//! [sections]



void ScheduleTableView::resizeEvent(QResizeEvent * event)
{
    QTableView::resizeEvent(event);
    updateFrozenTableGeometry();
}



//! [navigate]
QModelIndex ScheduleTableView::moveCursor(CursorAction cursorAction,
                                          Qt::KeyboardModifiers modifiers)
{
    QModelIndex current = QTableView::moveCursor(cursorAction, modifiers);

    if (cursorAction == MoveLeft && current.column() > 0
            && visualRect(current).topLeft().x() < frozenTableView->columnWidth(0) ){
        const int newValue = horizontalScrollBar()->value() + visualRect(current).topLeft().x()
                - frozenTableView->columnWidth(0);
        horizontalScrollBar()->setValue(newValue);
    }
    return current;
}


void ScheduleTableView::scrollTo (const QModelIndex & index, ScrollHint hint){
    if (index.column() > 0)
        QTableView::scrollTo(index, hint);
}


void ScheduleTableView::updateFrozenTableGeometry()
{
    frozenTableView->setGeometry(verticalHeader()->width() + frameWidth(),
                                 frameWidth(), columnWidth(0),
                                 viewport()->height()+horizontalHeader()->height());
}

