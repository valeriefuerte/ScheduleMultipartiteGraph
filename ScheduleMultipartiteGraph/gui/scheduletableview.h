#ifndef SCHEDULETABLEVIEW_H
#define SCHEDULETABLEVIEW_H

#include <QTableView>

class ScheduleTableAbstractModule;

class ScheduleTableView : public QTableView {
     Q_OBJECT

public:
      ScheduleTableView(QAbstractItemModel * model,QWidget *parent = nullptr);
      ~ScheduleTableView();
      void changeModel(QAbstractItemModel *model);
      //

protected:
      void resizeEvent(QResizeEvent *event) override;
      QModelIndex moveCursor(CursorAction cursorAction, Qt::KeyboardModifiers modifiers) override;
      void scrollTo (const QModelIndex & index, ScrollHint hint = EnsureVisible) override;

private:

      QTableView *frozenTableView;
      void init();
      void updateFrozenTableGeometry();


private slots:
      void updateSectionWidth(int logicalIndex, int oldSize, int newSize);
      void updateSectionHeight(int logicalIndex, int oldSize, int newSize);

};

#endif // SCHEDULETABLEVIEW_H
