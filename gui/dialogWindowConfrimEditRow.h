#ifndef DIALOGWINDOWCONFRIMEDITROW_H
#define DIALOGWINDOWCONFRIMEDITROW_H
#include<QDialog>
class DialogWindowConfirmEditRow: public QDialog{
    Q_OBJECT
public:
    DialogWindowConfirmEditRow(QWidget* parent=0);
    ~DialogWindowConfirmEditRow();

signals:
private slots:
    void clicked_btn();
private:
    QPushButton *applyButton;

};
#endif // DIALOGWINDOWCONFRIMEDITROW_H
