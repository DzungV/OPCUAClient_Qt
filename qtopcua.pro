QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
INCLUDEPATH += include

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    QCodeEditor_Example.cpp \
    main.cpp \
    mainwindow.cpp \
    protocol.cpp \
    src/Design/QCodeEditorDesign.cpp \
    src/Design/QCodeEditorSheets.cpp \
    src/Design/QLineColumnPadding.cpp \
    src/Design/QSyntaxRule.cpp \
    src/Design/XmlHelper.cpp \
    src/Widgets/QCodeEditor.cpp \
    src/Widgets/QCodeEditorEvents.cpp \
    src/Widgets/QCodeEditorHighlighter.cpp \
    src/Widgets/QCodeEditorLineWidget.cpp \
    src/Widgets/QCodeEditorPopup.cpp \
    src/Widgets/QCodeEditorSlots.cpp

HEADERS += \
    QCodeEditor_Example.hpp \
    include/KGL/Design/QCodeEditorDesign.hpp \
    include/KGL/Design/QCodeEditorSheets.hpp \
    include/KGL/Design/QLineColumnPadding.hpp \
    include/KGL/Design/QSyntaxRule.hpp \
    include/KGL/Design/XmlHelper.hpp \
    include/KGL/KGLConfig.hpp \
    include/KGL/Widgets/QCodeEditor.hpp \
    include/KGL/Widgets/QCodeEditorHighlighter.hpp \
    include/KGL/Widgets/QCodeEditorLineWidget.hpp \
    include/KGL/Widgets/QCodeEditorPopup.hpp \
    mainwindow.h \
    protocol.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

LIBS += -L"D:\Qt\5.15.2\msvc2015_64\lib" -lopen62541

RESOURCES += \
    files/res.qrc






