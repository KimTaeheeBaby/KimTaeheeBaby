#-------------------------------------------------
#
# Project created by QtCreator 2018-04-18T19:28:37
#
#-------------------------------------------------

QT       += core gui


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BackgroundSubtractor
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


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    ImgSeqProcessor.cpp \
    mythread.cpp \
    Vibe.cpp \
    vibe-background-sequential.c

HEADERS += \
        mainwindow.h \
    ImgSeqProcessor.h \
    mythread.h \
    Vibe.h \
    vibe-background-sequential.h

FORMS += \
    mainwindow.ui

INCLUDEPATH += F:/opencv/newBuild/install/include \
                F:/opencv/newBuild/install/include/opencv \
                F:/opencv/newBuild/install/include/opencv2
LIBS += F:/opencv/newBuild/install/x64/vc15/lib/opencv_world341.lib
