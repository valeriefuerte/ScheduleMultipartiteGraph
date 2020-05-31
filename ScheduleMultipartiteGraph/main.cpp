#include "gui/mainwindow.h"
#include <QApplication>
#include<iostream>
#include <QDebug>
#include <QTextCodec>
using namespace std;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec *codec1 = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForLocale(codec1);
    MainWindow w;
    w.show();


    return a.exec();
}
