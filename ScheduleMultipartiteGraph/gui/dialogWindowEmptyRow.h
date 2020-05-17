#ifndef DIALOGWINDOW_H
#define DIALOGWINDOW_H
#include <QDialog>
class DialogWindowEmptyRow: public QDialog{
    Q_OBJECT
public:
    DialogWindowEmptyRow(QWidget* parent=0);
    ~DialogWindowEmptyRow();

signals:
private slots:
    void clicked_btn();
private:
    QPushButton *applyButton;

};

#endif // DIALOGWINDOW_H
