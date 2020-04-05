#ifndef DIALOGCABINETWINDOW_H
#define DIALOGCABINETWINDOW_H
#include <QDialog>
#include <QLabel>
#include<QLineEdit>
#include<QFormLayout>
#include <models/repository/repositorytemplate.h>
#include <models/cabinet.h>



class DialogCabinetWindow: public QDialog{
    Q_OBJECT
public:
    DialogCabinetWindow(QWidget* parent=0);
    ~DialogCabinetWindow();
    RepositoryTemplate<Cabinet> *repoCabinets;
    bool flag;
    bool addEmpty;
    void clearLineEdit();


signals:
    void sendDataCabinet(Cabinet cabinet);
    void sendEditDataCabinet(RepositoryTemplate<Cabinet> *repCabinet);
private slots:
    void apply_clicked();
public slots:
    void receiveSelectionCabinet(Cabinet cabinet);
    private:
    QFormLayout *formLayout;
    QVBoxLayout *btnLayout;

    QPushButton *applyButton;

    QLineEdit *numberLineEdit;
    QLineEdit *floorLineEdit;
    QLineEdit *buildingLineEdit;
};

#endif // DIALOGCABINETWINDOW_H
