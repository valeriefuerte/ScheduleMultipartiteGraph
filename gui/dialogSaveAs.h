#ifndef DIALOGSAVEAS_H
#define DIALOGSAVEAS_H

#include <QDialog>
#include <QFileSystemModel>
#include <QDir>

namespace Ui {
class DialogSaveAs;
}

class DialogSaveAs : public QDialog
{
    Q_OBJECT

public:
    //изменеие содержимого формы для загрузки файла
    void changeDialogOpenFile();
    //изменение содержимого формы для сохранения файла
    void changeDialogSaveFile();
    //изменение содержимого формы для создания нового файла
    void changeDialogNewFile();
    //изменение содержимого формы для удаления файла
    void changeDialogDeleteFile();



    //директория с данными
    QString rootPath;
    //текущий путь
    QString curpath;

    //путь файла для загрузки
    QString pathFile;

    //имя файла
    QString fileName;

    bool openFile = true;

    explicit DialogSaveAs(QWidget *parent = nullptr);
    ~DialogSaveAs();

private slots:

    void closeEvent(QCloseEvent *);

    void on_table_file_dir_doubleClicked(const QModelIndex &index);

    void on_table_file_dir_clicked(const QModelIndex &index);

    void on_saveButton_clicked();

    void on_openButton_clicked();

    void on_createButton_clicked();

    void on_deleteButton_clicked();

private:
    Ui::DialogSaveAs *ui;
    QFileSystemModel *model;


signals:
    //отправка имени сохраненного файла
    void sendFileName(QString,QString,bool);

    //отправка имени выбранного файла для открытия
    void sendSelectedFileName(QString, QString);

    //отправка имени удаляемого файла
    void sendDeleteFileName(QString,QString);
};

#endif // DIALOGSAVEAS_H
