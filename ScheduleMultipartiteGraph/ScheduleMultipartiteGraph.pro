#-------------------------------------------------
#
# Project created by QtCreator 2018-12-02T15:42:15
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ScheduleMultipartiteGraph
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
    exceptions/graphexception.cpp \
    gui/dialogAddlinkGroupSubject.cpp \
    gui/dialogCabinetWindow.cpp \
    gui/dialogGroupWindow.cpp \
    gui/dialogLessonTimeWindow.cpp \
    gui/dialogLinkGroupSubjectWindow.cpp \
    gui/dialogSaveAs.cpp \
    gui/dialogSubjectWindow.cpp \
    gui/dialogWindowConfrimEditRow.cpp \
    gui/dialogWindowEmptyRow.cpp \
    gui/edge.cpp \
    gui/filterwidget.cpp \
    gui/graphwidget.cpp \
    gui/node.cpp \
    gui/scheduletableview.cpp \
    gui/schedulewidget.cpp \
    gui/visualizationwidget.cpp \
    gui/mainwindow.cpp \
    main.cpp \
    models/abstractnoderepository.cpp \
    models/cabinet.cpp \
    models/filterdata.cpp \
    models/groupstudents.cpp \
    models/lessontime.cpp \
    models/linkgroupsubject.cpp \
    models/repository/repository.cpp \
    models/repository/repositorytemplate.cpp \
    models/router.cpp \
    models/scheduefilterproxymodel.cpp \
    models/scheduletableabstractmodule.cpp \
    models/subject.cpp \
    models/tablelistmodel.cpp \
    someTestData/planettablemodel.cpp


HEADERS += \
    exceptions/graphexception.h \
    gui/dialogAddlinkGroupSubject.h \
    gui/dialogCabinetWindow.h \
    gui/dialogGroupWindow.h \
    gui/dialogLessonTimeWindow.h \
    gui/dialogLinkGroupSubjectWindow.h \
    gui/dialogSaveAs.h \
    gui/dialogSubjectWindow.h \
    gui/dialogWindowConfrimEditRow.h \
    gui/dialogWindowEmptyRow.h \
    gui/edge.h \
    gui/filterwidget.h \
    gui/graphwidget.h \
    gui/node.h \
    gui/scheduletableview.h \
    gui/schedulewidget.h \
    gui/visualizationwidget.h \
    gui/mainwindow.h \
    models/TestLesson.h \
    models/abstractnoderepository.h \
    models/cabinet.h \
    models/filterdata.h \
    models/linkgroupsubject.h \
    models/repository/repositorytemplate.h \
    models/groupstudents.h \
    models/lessontime.h \
    models/repository/repository.h \
    models/router.h \
    models/router.h \
    models/scheduefilterproxymodel.h \
    models/scheduletableabstractmodule.h \
    models/subject.h \
    models/tablelistmodel.h \
    someTestData/planet.h \
    someTestData/planettablemodel.h



FORMS += \
        gui/dialogSaveAs.ui \
        gui/filterwidget.ui \
        gui/mainwindow.ui

# Default rules for deployment.
 INSTALLS += target
