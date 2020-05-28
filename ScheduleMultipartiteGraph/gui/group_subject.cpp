#include "group_subject.h"
#include "models/tablelistmodel.h"
#include "gui/mainwindow.h"
#include <QMainWindow>
#include "ui_mainwindow.h"
#include <QMenu>
#include "qobject.h"

void GroupSubject::receiveGroup(QStringList *list_gr, MainWindow *obj)
{
    object = obj;
    gr_sub_model = new TableListModel(*list_gr);
    visualRows(object->ui->gr_sub_table,gr_sub_model);
}

void GroupSubject::visualRows(QTableView *table, TableListModel *model){
    table->setModel(model);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}



void GroupSubject::slotAddSG(){
    qDebug()<<"Работает соотнести!";
}

void GroupSubject::customGroupSubjectMenuRequested(const QPoint &pos){

   QMenu *menu = new QMenu(object);

   QAction *addSG= new QAction(("Соотнести"),object);

   connect(addSG, SIGNAL(triggered()),this,SLOT(slotAddSG()));

   menu->addAction(addSG);

   menu->popup( object->ui->gr_sub_table->viewport()->mapToGlobal(pos));
}
