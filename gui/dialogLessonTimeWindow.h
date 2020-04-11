#ifndef DIALOGLESSONTIMEWINDOW_H
#define DIALOGLESSONTIMEWINDOW_H
#include<QDialog>
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QDateTimeEdit>
#include <QFormLayout>
#include <QComboBox>
#include <models/repository/repositorytemplate.h>
#include <models/lessontime.h>

class DialogLessonTimeWindow: public QDialog{
Q_OBJECT

public:
    DialogLessonTimeWindow(QWidget* parent=0);
    ~DialogLessonTimeWindow();
    void editTitle();
    void addTitle();
    void outputEditData(LessonTime);
    void clearLineEdit();
    bool flag;

    QHash<QString, int> hashAddDay;
    QHash<int, QString> hashEditDay;

private:

    QComboBox *dayList;

    QPushButton *applyButton;

    QFormLayout *formLayout;
    QVBoxLayout *btnLayout;

    QLineEdit *parityEdit;
    QLineEdit *dayWeekEdit;
    QDateTimeEdit *timeEdit;


    RepositoryTemplate<LessonTime> *repoTime;
signals:
    void sendDataLessonTime(LessonTime);

    void sendEditDataLessonTime(LessonTime);

private slots:
    void apply_clicked();
};

#endif // DIALOGLESSONTIMEWINDOW_H
