QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
INCLUDEPATH += include

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    alarmdialog.cpp \
    code_editor.cpp \
    files.cpp \
    highlighter.cpp \
    main.cpp \
    mainwindow.cpp \
    mythread.cpp \
    protocol.cpp \
    utils/conversion.cpp \
    utils/templates.cpp \
    widgets/geisttextedit.cpp

HEADERS += \
    alarmdialog.h \
    code_editor.h \
    files.h \
    highlighter.h \
    mainwindow.h \
    mythread.h \
    protocol.h \
    utils/conversion.h \
    utils/templates.h \
    widgets/geisttextedit.h

FORMS += \
    alarmdialog.ui \
    code_editor.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

LIBS += -L"D:\Qt\5.15.2\msvc2015_64\lib" -lopen62541

RESOURCES += \
    files/res.qrc

#INCLUDEPATH += include/KGL/Widgets





