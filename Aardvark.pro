#-------------------------------------------------
#
# Project created by QtCreator 2019-02-06T22:02:45
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Aardvark
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
        main.cpp \
        mainwindow.cpp \
    logdocwindow.cpp \
    SettingPanel/epushbutton.cpp \
    SettingPanel/settingpanel.cpp \
    SettingPanel/fontform.cpp

HEADERS += \
        mainwindow.h \
    logdocwindow.h \
    SettingPanel/epushbutton.h \
    SettingPanel/settingpanel.h \
    SettingPanel/fontform.h

FORMS += \
    mainwindow.ui \
    logdocwindow.ui \
    SettingPanel/fontform.ui

INCLUDEPATH += \
    "E:/code/sci/QScintilla_gpl-2.10.8/Qt4Qt5"
LIBS += -LE:/code/sci/QScintilla_gpl-2.10.8/build-qscintilla-Desktop_Qt_5_11_2_MinGW_32bit-Debug/debug -lqscintilla2_qt5d

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

DISTFILES +=
