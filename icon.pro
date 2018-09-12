TEMPLATE = app
LANGUAGE = c++
CONFIG += qt warn_off thread exceptions
TARGET = icon

INCLUDEPATH += \
    ../include \
    ../include/H5IconGui \
    ../include/H5IconHelp

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
    hiconpreview.h \
    #hiconshowpattern.h \
    hiconcommand.h \
    habout.h \
    hiconop.h

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
    hiconpreview.cpp \
    #hiconshowpattern.cpp \
    hiconcommand.cpp \
    habout.cpp \
    hiconop.cpp \
    hiconmainwindowactions.cpp

RESOURCES     = \
    icon.qrc \
    qmres.qrc \
    qss.qrc


FORMS += \
    #UI/propertydlg.ui \
    UI/iconpreview.ui \
    UI/about.ui

LIBS += -L../lib -lH5IconGui -lH5IconHelp -ldatafile
unix{
    UI_DIR = temp/ui
    MOC_DIR = temp/moc
    OBJECTS_DIR	= temp/obj
    LIBS += \

}

win32{
    UI_DIR = temp/ui
    MOC_DIR = temp/moc
    OBJECTS_DIR	= temp/obj
    LIBS += \
}

QT += widgets
QT += xml



