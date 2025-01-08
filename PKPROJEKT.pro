QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    arx.cpp \
    arxwidget.cpp \
    generator.cpp \
    innewartosciwidget.cpp \
    main.cpp \
    mainwindow.cpp \
    pid.cpp \
    pidwidget.cpp \
    symulacja.cpp

HEADERS += \
    arx.h \
    arxwidget.h \
    generator.h \
    glowne.h \
    innewartosciwidget.h \
    mainwindow.h \
    pid.h \
    pidwidget.h \
    symulacja.h \
    zarzadzanie_plikami.h

FORMS += \
    arxwidget.ui \
    innewartosciwidget.ui \
    mainwindow.ui \
    pidwidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
