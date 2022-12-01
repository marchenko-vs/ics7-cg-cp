QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++14

SOURCES += \
    face.cpp \
    main.cpp \
    mainwindow.cpp \
    matrix.cpp \
    object.cpp \
    vertex.cpp

HEADERS += \
    face.h \
    mainwindow.h \
    matrix.h \
    object.h \
    vertex.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
