TEMPLATE = app
LANGUAGE = c++
CONFIG += qt warn_off thread exceptions
TARGET = icon

INCLUDEPATH += \
    ../include \
    ../include/H5IconGui

HEADERS       = \
    hiconmainwindow.h \
    hframe.h \
    hiconframe.h \
    hiconwidget.h \
    hicontreewidget.h \
    #hiconsymbol.h \
    #hicontemplate.h \
    hicondocument.h \
    hiconscene.h \
    hiconmgr.h \
    hiconstate.h \
    hpropertydlg.h \
    hiconpreview.h \
    #hiconshowpattern.h \
    hiconcommand.h \
    habout.h

SOURCES       = main.cpp \
    hiconmainwindow.cpp \
    hframe.cpp \
    hiconframe.cpp \
    hiconwidget.cpp \
    hicontreewidget.cpp \
    #hiconsymbol.cpp \
    #hicontemplate.cpp \
    hicondocument.cpp \
    hiconscene.cpp \
    hiconmgr.cpp \
    hiconstate.cpp \
    hpropertydlg.cpp \
    hiconpreview.cpp \
    #hiconshowpattern.cpp \
    hiconcommand.cpp \
    habout.cpp

RESOURCES     = \
    icon.qrc \
    qmres.qrc \
    qss.qrc


FORMS += \
    UI/propertydlg.ui \
    UI/iconpreview.ui \
    UI/about.ui

unix{

    LIBS += -L ../lib/ -lH5IconGui
}

win32{
   LIBS += \
         ../lib/H5IconGui.lib
}
QT += widgets
QT += xml



