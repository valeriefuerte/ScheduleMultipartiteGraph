#ifndef DIALOGLESSONTIMEWINDOW_H
#define DIALOGLESSONTIMEWINDOW_H
#include<QDialog>
#include <QDialog>
#include <QLabel>
#include<QLineEdit>
#include <QDateTimeEdit>
#include<QFormLayout>

class dialogLessonTimeWindow: public QDialog
{
public:
    dialogLessonTimeWindow();
private:
    QPushButton *applyButton;

    QFormLayout *formLayout;
    QVBoxLayout *btnLayout;


    QDateTimeEdit *dateTimeEdit;
    QDateTimeEdit *timeEdit;
};

#endif // DIALOGLESSONTIMEWINDOW_H
