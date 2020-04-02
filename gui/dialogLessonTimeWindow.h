#ifndef DIALOGLESSONTIMEWINDOW_H
#define DIALOGLESSONTIMEWINDOW_H
#include<QDialog>
#include <QDialog>
#include <QLabel>
#include<QLineEdit>
#include <QDateTimeEdit>
#include<QFormLayout>
#include <models/repository/repositorygeneral.h>
#include <models/lessontime.h>

class DialogLessonTimeWindow: public QDialog{
Q_OBJECT

public:
    DialogLessonTimeWindow(QWidget* parent=0);
    ~DialogLessonTimeWindow();
private:
    QPushButton *applyButton;

    QFormLayout *formLayout;
    QVBoxLayout *btnLayout;


    QDateTimeEdit *dateTimeEdit;
    QDateTimeEdit *timeEdit;

    RepositoryGeneral<LessonTime> *repoTime;
signals:

private slots:
    void apply_clicked();
};

#endif // DIALOGLESSONTIMEWINDOW_H
