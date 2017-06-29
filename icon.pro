QT += widgets

HEADERS       = \
    iconapi.h \
    hiconmainwindow.h \
    hiconoper.h \
    hframe.h \
    hiconframe.h \
    hiconwidget.h \
    hicontreewidget.h \
    hiconsymbol.h \
    hbaseobj.h \
    hicontype.h \
    hicontemplate.h \
    hicondocument.h \
    hnewicondlg.h \
    hdrawtool.h \
    hiconscene.h \
    #hevent.h \
    hiconmgr.h \
    hiconstate.h \
    #hiconobjitem.h \
    hpropertydlg.h \
    hiconrectitem.h \
    hiconellipseitem.h \
    hiconobj.h \
    hiconpolygonitem.h \
    hiconarcitem.h \
    hiconpieitem.h \
    hiconpreview.h \
    hicontextitem.h \
    hiconshowpattern.h \
    hiconlineitem.h
    #hlineobj.h \
    #hellipseobj.h
SOURCES       = main.cpp \
    hiconmainwindow.cpp \
    hiconoper.cpp \
    hframe.cpp \
    hiconframe.cpp \
    hiconwidget.cpp \
    hicontreewidget.cpp \
    hiconsymbol.cpp \
    hbaseobj.cpp \
    hicontype.cpp \
    hicontemplate.cpp \
    hicondocument.cpp \
    hnewicondlg.cpp \
    hdrawtool.cpp \
    hiconscene.cpp \
    #hevent.cpp \
    hiconmgr.cpp \
    hiconstate.cpp \
    #hiconobjitem.cpp \
    hpropertydlg.cpp \
    hiconrectitem.cpp \
    hiconellipseitem.cpp \
    hiconobj.cpp \
    hiconpolygonitem.cpp \
    hiconarcitem.cpp \
    hiconpieitem.cpp \
    hiconpreview.cpp \
    hicontextitem.cpp \
    hiconshowpattern.cpp \
    hiconlineitem.cpp
    #hlineobj.cpp \
    #hellipseobj.cpp
RESOURCES     = \
    icon.qrc \
    qmres.qrc
QT += xml

FORMS += \
    UI/newicondlg.ui \
    UI/propertydlg.ui \
    UI/iconpreview.ui
