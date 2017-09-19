QT += widgets

HEADERS       = \
    hiconmainwindow.h \
    hframe.h \
    hiconframe.h \
    hiconwidget.h \
    hicontreewidget.h \
    hiconsymbol.h \
    hbaseobj.h \
    hicontemplate.h \
    hicondocument.h \
    #hdrawtool.h \
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
    hiconlineitem.h \
    hicongraphicsitem.h \
    hiconapi.h \
    hiconselectionitem.h \
    hiconcommand.h \
    hiconpolylineitem.h \
    hiconcircleitem.h
    #hlineobj.h \
    #hellipseobj.h
SOURCES       = main.cpp \
    hiconmainwindow.cpp \
    hframe.cpp \
    hiconframe.cpp \
    hiconwidget.cpp \
    hicontreewidget.cpp \
    hiconsymbol.cpp \
    hbaseobj.cpp \
    hicontemplate.cpp \
    hicondocument.cpp \
    #hdrawtool.cpp \
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
    hiconlineitem.cpp \
    hicongraphicsitem.cpp \
    hiconselectionitem.cpp \
    hiconcommand.cpp \
    hiconpolylineitem.cpp \
    hiconcircleitem.cpp
    #hlineobj.cpp \
    #hellipseobj.cpp
RESOURCES     = \
    icon.qrc \
    qmres.qrc \
    qss.qrc
QT += xml

FORMS += \
    UI/propertydlg.ui \
    UI/iconpreview.ui
