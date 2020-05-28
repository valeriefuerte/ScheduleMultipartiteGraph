#ifndef DIALOGSUBJECTWINDOW_H
#define DIALOGSUBJECTWINDOW_H
#include <QDialog>
#include <QLabel>
#include<QLineEdit>
#include<QFormLayout>
#include <models/repository/repositorytemplate.h>
#include <models/subject.h>
class DialogSubjectWindow: public QDialog{
    Q_OBJECT
public:
    DialogSubjectWindow(QWidget* parent=0);
    ~DialogSubjectWindow();
    bool flag;
    void clearLineEdit();
    void editTitle();
    void addTitle();
    void outputEditData(Subject editSubject);

signals:
    void sendDataSubject(Subject subject);
    void sendEditDataSubject(Subject subject);
private slots:
    void apply_clicked();
public slots:
    private:
    QFormLayout *formLayout;
    QVBoxLayout *btnLayout;

    QPushButton *applyButton;

    QLineEdit *subjectLineEdit;
};
#endif // DIALOGSUBJECTWINDOW_H
