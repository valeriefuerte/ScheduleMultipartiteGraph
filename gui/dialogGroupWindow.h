#ifndef DIALOGGROUPWINDOW_H
#define DIALOGGROUPWINDOW_H
#include <QDialog>
#include <QLabel>
#include<QLineEdit>
#include<QFormLayout>
#include <models/repository/repositorytemplate.h>
#include <models/groupstudents.h>
class DialogGroupWindow: public QDialog{
    Q_OBJECT
public:
    DialogGroupWindow(QWidget* parent=0);
    ~DialogGroupWindow();
    bool flag;
    void clearLineEdit();
    void editTitle();
    void addTitle();
    void outputEditData(GroupStudents);
signals:
    void sendDataGroup(GroupStudents);
    void sendEditDataGroup(GroupStudents);
private slots:
    void apply_clicked();
public slots:
    private:
    QFormLayout *formLayout;
    QVBoxLayout *btnLayout;

    QPushButton *applyButton;

    QLineEdit *groupLineEdit;
};
#endif // DIALOGGROUPWINDOW_H
