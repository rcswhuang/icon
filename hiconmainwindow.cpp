﻿#include "hiconmainwindow.h"
#include <QKeySequence>
#include <QRectF>
#include <QRect>
#include <QDockWidget>
#include <QStatusBar>
#include <QInputDialog>
#include <QIntValidator>
#include <QActionGroup>
#include <QMessageBox>
#include <QVariant>
#include <qmath.h>
#include "habout.h"
#include "H5IconGui/hgroupobj.h"
#include "H5IconGui/hiconitemgroup.h"
HIconMainWindow::HIconMainWindow(HIconMgr *parent) : pIconMgr(parent)
{
    createActions();
    createMenuBars();
    createToolBars();
    createDockWindows();

    pIconWidget = new HIconWidget();

    setCentralWidget(pIconWidget);
    setWindowTitle(QStringLiteral("图元编辑器"));
    //setWindowModified(true);

    //pIconDocument = new HIconDocument;
    statusBar()->showMessage("Reday");
    //resize(800,600);
    setWindowState(Qt::WindowMaximized);

    init();
    setUnifiedTitleAndToolBarOnMac(true);
}

HIconMainWindow::~HIconMainWindow()
{

}

void HIconMainWindow::init()
{
    pIconFrame = pIconMgr->getIconFrame();
    connect(pIconFrame,SIGNAL(mousePosChanged(const QPoint&,const QPointF&)),this,SLOT(viewMousePosChanged(const QPoint&,const QPointF&)));
    connect(pIconFrame->getIconScene(),SIGNAL(itemInserted(int)),this,SLOT(itemInserted(int)));
    showGridAct->setChecked(pIconMgr->getShowGrid());
    showCLineAct->setChecked(pIconMgr->getShowCenterLine());
    //改用函数来实现
    pIconMgr->getIconFrame()->scaleChangedTo(0.6);
    QString strScale = QString("%1%").arg(pIconMgr->getIconFrame()->scale()*100);
    scaleComboBox->setCurrentText(strScale);
}

void HIconMainWindow::createActions()
{

    setIconSize(QSize(32,32));
    //文件项
    //newAct = new QAction(QIcon(":/images/new.png"), QStringLiteral("新建(&N)"), this);
    //newAct->setShortcuts(QKeySequence::New);

    openAct = new QAction(QIcon(":/images/open.png"), QStringLiteral("打开(&O)"), this);
    openAct->setShortcuts(QKeySequence::Open);

    saveAct = new QAction(QIcon(":/images/save.png"), QStringLiteral("保存(&S)"), this);
    saveAct->setShortcuts(QKeySequence::Save);
    connect(saveAct,SIGNAL(triggered(bool)),this,SLOT(save()));

    quitAct = new QAction(QIcon(":/images/close.png"),QStringLiteral("退出(&E)"),this);
    quitAct->setShortcut(QKeySequence::Quit);
    connect(quitAct, &QAction::triggered,this,&QWidget::close);
    // QAction *exitAct = fileMenu->addAction(exitIcon, tr("E&xit"), this, &QWidget::close);

    //编辑项
    undoAct = new QAction(QIcon(":/images/undo.png"),QStringLiteral("撤销(&U)"),this);
    undoAct->setShortcut(QKeySequence(QKeySequence::Undo));
    connect(undoAct,SIGNAL(triggered(bool)),this,SLOT(undo()));

    redoAct = new QAction(QIcon(":/images/redo.png"),QStringLiteral("重做(&R)"),this);
    redoAct->setShortcut(QKeySequence(QKeySequence::Redo));
    connect(redoAct,SIGNAL(triggered(bool)),this,SLOT(redo()));

    cutAct = new QAction(QIcon(":/images/cut.png"), QStringLiteral("剪切(&X)"), this);
    cutAct->setShortcuts(QKeySequence::Cut);
    connect(cutAct,SIGNAL(triggered(bool)),this,SLOT(cut()));

    copyAct = new QAction(QIcon(":/images/copy.png"), QStringLiteral("复制(&C)"), this);
    copyAct->setShortcuts(QKeySequence::Copy);
    connect(copyAct,SIGNAL(triggered(bool)),this,SLOT(copy()));

    pasteAct = new QAction(QIcon(":/images/paste.png"), QStringLiteral("粘贴(&P)"), this);
    pasteAct->setShortcuts(QKeySequence::Paste);
    connect(pasteAct,SIGNAL(triggered(bool)),this,SLOT(paste()));

    deleteAct = new QAction(QIcon(":/images/del.png"),QStringLiteral("删除(&D)"),this);
    deleteAct->setShortcut(QKeySequence::Delete);
    connect(deleteAct,SIGNAL(triggered(bool)),this,SLOT(del()));

    //视图项
    showRulerAct = new QAction(QIcon(":/images/ruler.png"), QStringLiteral("标尺(&R)"), this);
    showRulerAct->setCheckable(true);
    showRulerAct->setChecked(true);

    showGridAct = new QAction(QIcon(":/images/grid.png"), QStringLiteral("网格(&G)"), this);
    showGridAct->setCheckable(true);
    showGridAct->setChecked(true);
    connect(showGridAct,SIGNAL(triggered(bool)),this,SLOT(showGrid()));

    showCLineAct = new QAction(QIcon(":/images/center.png"), QStringLiteral("中心线(&C)"), this);
    showCLineAct->setCheckable(true);
    showCLineAct->setChecked(true);
    connect(showCLineAct,SIGNAL(triggered(bool)),this,SLOT(showCenterLine()));

    //缩放项
    fitWidthAct = new QAction(QIcon(":/images/zoom_fit_width.png"), QStringLiteral("合适宽度"), this);
    connect(fitWidthAct,SIGNAL(triggered(bool)),this,SLOT(fitWidth()));
    fitHeightAct = new QAction(QIcon(":/images/zoom_fit_height.png"), QStringLiteral("合适高度"), this);
    connect(fitHeightAct,SIGNAL(triggered(bool)),this,SLOT(fitHeight()));
    zoomInAct = new QAction(QIcon(":/images/zoom_in.png"), QStringLiteral("放大"), this);
    //zoomInAct->setCheckable(true);
    connect(zoomInAct,SIGNAL(triggered(bool)),this,SLOT(zoomIn()));
    zoomOutAct = new QAction(QIcon(":/images/zoom_out.png"), QStringLiteral("缩小"), this);
    //zoomOutAct->setCheckable(true);
    connect(zoomOutAct,SIGNAL(triggered(bool)),this,SLOT(zoomOut()));
    zoomOriAct = new QAction(QIcon(":/images/zoom_original.png"), QStringLiteral("自由缩放"), this);
    //zoomOriAct->setCheckable(true);

    scaleComboBox = new QComboBox(this);
    QIntValidator *validator = new QIntValidator(10,500);
    scaleComboBox->setValidator(validator);
    scaleComboBox->setEditable(true);
    scaleComboBox->addItem(tr("50%"),0.5);
    scaleComboBox->addItem(tr("70%"),0.7);
    scaleComboBox->addItem(tr("100%"),1);
    scaleComboBox->addItem(tr("150%"),1.5);
    connect(scaleComboBox,SIGNAL(currentIndexChanged(QString)),this,SLOT(scaleChanged(QString)));
    connect(scaleComboBox->lineEdit(),SIGNAL(editingFinished()),this,SLOT(scaleChanged()));

    toTopAct = new QAction(QIcon(":/images/move_forward.png"),QStringLiteral("置顶"),this);
    connect(toTopAct,SIGNAL(triggered(bool)),this,SLOT(bringToTop()));

    toBottomAct = new QAction(QIcon(":/images/move_backward.png"),QStringLiteral("置底"),this);
    connect(toBottomAct,SIGNAL(triggered(bool)),this,SLOT(bringToBottom()));


    alignLeftAct = new QAction(QIcon(":/images/shape_align_left.png"),QStringLiteral("左对齐"),this);
    connect(alignLeftAct,SIGNAL(triggered(bool)),this,SLOT(alignLeft()));
    alignLeftAct->setEnabled(false);
    alignVCenterAct = new QAction(QIcon(":/images/shape_align_middle.png"),QStringLiteral("纵向居中对齐"),this);
    connect(alignVCenterAct,SIGNAL(triggered(bool)),this,SLOT(alignVCenter()));
    alignRightAct = new QAction(QIcon(":/images/shape_align_right.png"),QStringLiteral("右对齐"),this);
    connect(alignRightAct,SIGNAL(triggered(bool)),this,SLOT(alignRight()));

    alignTopAct = new QAction(QIcon(":/images/shape_align_top.png"),QStringLiteral("上对齐"),this);
    connect(alignTopAct,SIGNAL(triggered(bool)),this,SLOT(alignTop()));
    alignHCenterAct = new QAction(QIcon(":/images/shape_align_center.png"),QStringLiteral("横向居中对齐"),this);
    connect(alignHCenterAct,SIGNAL(triggered(bool)),this,SLOT(alignHCenter()));
    alignBottomAct = new QAction(QIcon(":/images/shape_align_bottom.png"),QStringLiteral("下对齐"),this);;
    connect(alignBottomAct,SIGNAL(triggered(bool)),this,SLOT(alignBottom()));

    //同等单元
   /* QAction *equlHSpaceAct;
    QAction *equlVSpaceAct;
    QAction *equlWidthAct;
    QAction *equlHeightAct;
    QAction *equlSizeAct;
*/
    //组合单元
    groupObjAct = new QAction(QIcon(":/images/group.png"),QStringLiteral("组合"),this);;
    connect(groupObjAct,SIGNAL(triggered(bool)),this,SLOT(groupObj()));
    ungroupObjAct = new QAction(QIcon(":/images/ungroup.png"),QStringLiteral("解除组合"),this);;
    connect(ungroupObjAct,SIGNAL(triggered(bool)),this,SLOT(ungroupObj()));;


    //绘制项
    lineAct = new QAction(QIcon(":/images/line.png"), QStringLiteral("直线"), this);
    lineAct->setCheckable(true);
    connect(lineAct,SIGNAL(triggered()),this,SLOT(drawLine()));

    rectAct = new QAction(QIcon(":/images/rectangle.png"), QStringLiteral("矩形"), this);
    rectAct->setCheckable(true);
    connect(rectAct,SIGNAL(triggered()),this,SLOT(drawRectangle()));

    ellipseAct = new QAction(QIcon(":/images/ellipse.png"), QStringLiteral("椭圆"), this);
    ellipseAct->setCheckable(true);
    connect(ellipseAct,SIGNAL(triggered()),this,SLOT(drawEllipse()));

    circleAct = new QAction(QIcon(":/images/circle.png"),QStringLiteral("圆"),this);
    circleAct->setCheckable(true);
    connect(circleAct,SIGNAL(triggered()),this,SLOT(drawCircle()));

    hexagonAct = new QAction(QIcon(":/images/polygon.png"),QStringLiteral("多边形"),this);
    hexagonAct->setCheckable(true);
    connect(hexagonAct,SIGNAL(triggered()),this,SLOT(drawHexagon()));

    polylineAct = new QAction(QIcon(":/images/polyline.png"),QStringLiteral("折线"),this);
    polylineAct->setCheckable(true);
    connect(polylineAct,SIGNAL(triggered()),this,SLOT(drawPolyline()));

    arcAct = new QAction(QIcon(":/images/arc.png"), QStringLiteral("弧线"), this);
    arcAct->setCheckable(true);
    connect(arcAct,SIGNAL(triggered()),this,SLOT(drawArc()));

    fanAct = new QAction(QIcon(":/images/pie.png"),QStringLiteral("饼型"),this);
    fanAct->setCheckable(true);
    connect(fanAct,SIGNAL(triggered()),this,SLOT(drawFan()));

    textAct = new QAction(QIcon(":/images/text.png"),QStringLiteral("文字"),this);
    textAct->setCheckable(true);
    connect(textAct,SIGNAL(triggered()),this,SLOT(drawText()));

    selectAct = new QAction(QIcon(":/images/select.png"), QStringLiteral("选择"), this);
    connect(selectAct,SIGNAL(triggered(bool)),this,SLOT(drawSelection()));
    selectAct->setCheckable(true);
    selectAct->setChecked(true);

    QActionGroup * actionGroup = new QActionGroup(this);
    actionGroup->addAction(lineAct);
    actionGroup->addAction(polylineAct);
    actionGroup->addAction(rectAct);
    actionGroup->addAction(ellipseAct);
    actionGroup->addAction(circleAct);
    actionGroup->addAction(hexagonAct);
    actionGroup->addAction(arcAct);
    actionGroup->addAction(fanAct);
    actionGroup->addAction(textAct);
    actionGroup->addAction(selectAct);


    tileAct = new QAction(tr("&Tile"), this);
    tileAct->setStatusTip(tr("Tile the windows"));


    cascadeAct = new QAction(tr("&Cascade"), this);
    cascadeAct->setStatusTip(tr("Cascade the windows"));


    nextAct = new QAction(tr("Ne&xt"), this);
    nextAct->setShortcuts(QKeySequence::NextChild);
    nextAct->setStatusTip(tr("Move the focus to the next window"));


    previousAct = new QAction(tr("Pre&vious"), this);
    previousAct->setShortcuts(QKeySequence::PreviousChild);
    previousAct->setStatusTip(tr("Move the focus to the previous "
                                 "window"));


    //windowMenuSeparatorAct = new QAction(this);
    //windowMenuSeparatorAct->setSeparator(true);


   // menuBar()->addSeparator();

    //QMenu *helpMenu = menuBar()->addMenu(tr("&Help"));

    aboutAct = new QAction(QStringLiteral("关于"), this);
    connect(aboutAct,SIGNAL(triggered()),this,SLOT(about()));
    aboutAct->setStatusTip(tr("Show the application's About box"));

    //QAction *aboutQtAct = helpMenu->addAction(tr("About &Qt"), qApp, &QApplication::aboutQt);
    //aboutQtAct->setStatusTip(tr("Show the Qt library's About box"));

 //////////draw Toool/////////////////////
}


void HIconMainWindow::createToolBars()
{
    fileToolBar = addToolBar(tr("fileBar"));
    fileToolBar->setIconSize(QSize(32,32));
    //fileToolBar->addAction(newAct);
    fileToolBar->addAction(openAct);
    fileToolBar->addAction(saveAct);
    fileToolBar->addAction(quitAct);


    editToolBar = addToolBar(tr("editBar"));
    editToolBar->setIconSize(QSize(32,32));
    editToolBar->addAction(undoAct);
    editToolBar->addAction(redoAct);
    editToolBar->addAction(cutAct);
    editToolBar->addAction(copyAct);
    editToolBar->addAction(pasteAct);
    editToolBar->addAction(deleteAct);

    shapeToolBar = addToolBar(tr("shapeToolBar"));
    shapeToolBar->addAction(toTopAct);
    shapeToolBar->addAction(toBottomAct);

    zoomToolBar = addToolBar(tr("zoomBar"));
    zoomToolBar->setIconSize(QSize(32,32));
    zoomToolBar->addAction(fitWidthAct);
    zoomToolBar->addAction(fitHeightAct);
    zoomToolBar->addAction(zoomInAct);
    zoomToolBar->addAction(zoomOutAct);
    zoomToolBar->addAction(zoomOriAct);
    zoomToolBar->addWidget(scaleComboBox);

    drawToolBar = addToolBar(tr("drawToolBar"));
    drawToolBar->setIconSize(QSize(32,32));
    drawToolBar->addAction(lineAct);
    drawToolBar->addAction(polylineAct);
    drawToolBar->addAction(rectAct);
    drawToolBar->addAction(ellipseAct);
    drawToolBar->addAction(circleAct);
    drawToolBar->addAction(hexagonAct);
    drawToolBar->addAction(arcAct);
    drawToolBar->addAction(fanAct);
    drawToolBar->addAction(textAct);
/*
    shapeToolBar = new QToolBar(tr("shapeToolBar"),this);
    shapeToolBar->setIconSize(QSize(32,32));
    shapeToolBar->addAction(groupObjAct);
    shapeToolBar->addAction(ungroupObjAct);
    shapeToolBar->addAction(alignLeftAct);
    shapeToolBar->addAction(alignVCenterAct);
    shapeToolBar->addAction(alignRightAct);
    shapeToolBar->addAction(alignTopAct);
    shapeToolBar->addAction(alignHCenterAct);
    shapeToolBar->addAction(alignBottomAct);
    shapeToolBar->addAction(toTopAct);
    shapeToolBar->addAction(toBottomAct);
    addToolBar(Qt::BottomToolBarArea,shapeToolBar);
*/



    otherBar = addToolBar(tr("other"));
    otherBar->addAction(selectAct);
    otherBar->addAction(groupObjAct);
    otherBar->addAction(ungroupObjAct);
    //otherBar->addAction(rotateAct);
}

void HIconMainWindow::createMenuBars()
{
    fileMenu = menuBar()->addMenu(QStringLiteral("文件(&F)"));
    //fileMenu->addAction(newAct);
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);
    fileMenu->addSeparator();
    fileMenu->addAction(quitAct);

    editMenu = menuBar()->addMenu(QStringLiteral("编辑(&E)"));
    editMenu->addAction(undoAct);
    editMenu->addAction(redoAct);
    editMenu->addSeparator();
    editMenu->addAction(cutAct);
    editMenu->addAction(copyAct);
    editMenu->addAction(pasteAct);


    viewMenu = menuBar()->addMenu(QStringLiteral("视图(&V)"));
    viewMenu->addAction(showRulerAct);
    viewMenu->addAction(showGridAct);
    viewMenu->addAction(showCLineAct);

    toolMenu = menuBar()->addMenu(QStringLiteral("绘制(&W)"));
    toolMenu->addAction(lineAct);
    toolMenu->addAction(polylineAct);
    toolMenu->addAction(rectAct);
    toolMenu->addAction(ellipseAct);
    toolMenu->addAction(hexagonAct);
    toolMenu->addAction(arcAct);
    toolMenu->addAction(fanAct);
    toolMenu->addAction(textAct);

    helpMenu = menuBar()->addMenu(QStringLiteral("帮助(&H)"));
    helpMenu->addAction(aboutAct);
}

void HIconMainWindow::createDockWindows()
{
    QDockWidget* browserIconDock = new QDockWidget(QStringLiteral("图元浏览框"),this);
    browserIconDock->setAllowedAreas(Qt::LeftDockWidgetArea|Qt::RightDockWidgetArea);
    pIconTreeWidget = new HIconTreeWidget(pIconMgr);
    pIconTreeWidget->setRootIsDecorated(true);
    pIconTreeWidget->setSortingEnabled(false);
    browserIconDock->setWidget(pIconTreeWidget);
    addDockWidget(Qt::LeftDockWidgetArea,browserIconDock);
    pIconTreeWidget->init();

    connect(pIconTreeWidget,SIGNAL(IconNew(const QString&,const QString&,const int&)),this,SLOT(New(const QString&,const QString&,const int&)));
    connect(pIconTreeWidget,SIGNAL(IconDel(const QString&,const int&,const QString&)),this,SLOT(Del(const QString&,const int&,const QString&)));
    connect(pIconTreeWidget,SIGNAL(IconOpen(const QString&,const int&,const QString&)),this,SLOT(Open(const QString&,const int&,const QString&)));

    QDockWidget* iconPreviewDock = new QDockWidget(QStringLiteral("图元预览框"),this);
    iconPreviewDock->setAllowedAreas(Qt::LeftDockWidgetArea|Qt::RightDockWidgetArea);
    pIconPreview = new HIconPreview(pIconMgr);
    iconPreviewDock->setWidget(pIconPreview);
    addDockWidget(Qt::RightDockWidgetArea,iconPreviewDock);
}

void HIconMainWindow::newFile()
{
    //New(strName);

}

void HIconMainWindow::open()
{

}

void HIconMainWindow::save()
{
    pIconMgr->Save(true);
}

void HIconMainWindow::saveAs()
{

}

//关闭
bool HIconMainWindow::close()
{
    QMessageBox mb(QStringLiteral("警告"),QStringLiteral("退出前需要保存所有图符模板吗？"),
            QMessageBox::Information,QMessageBox::Yes | QMessageBox::Default,
            QMessageBox::No,QMessageBox::Cancel | QMessageBox::Escape );
    mb.setButtonText( QMessageBox::Yes, QStringLiteral("是") );
    mb.setButtonText( QMessageBox::No, QStringLiteral("否") );
    mb.setButtonText(QMessageBox::Cancel,QStringLiteral("取消"));
    switch( mb.exec() ) {
        case QMessageBox::Yes:
            Save();
            return true;
        case QMessageBox::Cancel:
            return false;
    default:
        break;

    }
    return true;
}

//退出
void HIconMainWindow::quit()
{

}


void HIconMainWindow::New(const QString& strTemplateName,const QString& strCatalogName,const int& nCatalogType)
{
    if(!pIconMgr && !pIconMgr->getIconTemplate())
        return;

    HIconTemplate* pTemplate = pIconMgr->getIconDocument()->findIconTemplateByTemplateName(strTemplateName);
    if(pTemplate)
    {
        QMessageBox::information(this,QStringLiteral("提醒"),QStringLiteral("已经存在相同名字的模板文件，请修改名称"),QMessageBox::Ok);
        return;
    }

    if(pIconMgr->getIconTemplate()->getModify())
    {
        if(QMessageBox::Ok == QMessageBox::information(NULL,QStringLiteral("提醒"),QStringLiteral("需要保存当前的模板文件吗？"),QMessageBox::Yes|QMessageBox::No))
        {

             Save();
        }
    }

    pIconWidget->delIconWidget();//先删除目前
    pIconMgr->New(strTemplateName,strCatalogName,nCatalogType);
    pIconWidget->setIconMgr(pIconMgr);
    pIconWidget->newIconWidget();
    pIconTreeWidget->addIconTreeWigetItem();
    pIconPreview->init();
}


void HIconMainWindow::Open(const QString &strTemplateName, int nTemplateType, const QString &strUuid)
{
    if(!pIconMgr && !pIconMgr->getIconTemplate())
        return;
    if(pIconMgr->getIconTemplate()->getModify())
    {
        if(QMessageBox::Ok == QMessageBox::information(NULL,QStringLiteral("提醒"),QStringLiteral("需要保存当前的模板文件吗？"),QMessageBox::Ok|QMessageBox::Cancel))
        {
            Save();
        }
    }

    pIconWidget->delIconWidget();
    pIconMgr->Open(strTemplateName,nTemplateType,strUuid);
    pIconWidget->setIconMgr(pIconMgr);
    pIconWidget->openIconWidget();
    pIconPreview->init();
    HIconTemplate *pIconTemplate = pIconMgr->getIconTemplate();
    QString strTitle = pIconTemplate->getCatalogName() + "/" + pIconTemplate->getSymbol()->getSymolName() + pIconTemplate->getUuid().toString();
    strTitle = QString("%1[*] - %2").arg(strTitle).arg(QStringLiteral("图元编辑器"));
    setWindowTitle(strTitle);
}

void HIconMainWindow::Save()
{
    pIconMgr->Save();
}

//
void HIconMainWindow::Del(const QString &strTemplateName, int nTemplateType, const QString &strUuid)
{
    if(!pIconTreeWidget || !pIconWidget || !pIconMgr)
        return;
    pIconTreeWidget->delIconTreeWidgetItem();
    pIconWidget->delIconWidget();
    pIconMgr->Del(strTemplateName,nTemplateType,strUuid);
    pIconPreview->init();
}


void HIconMainWindow::about()
{
    HAbout about;
    about.exec();
}

void HIconMainWindow::resizeEvent(QResizeEvent *event)
{
}

void HIconMainWindow::closeEvent(QCloseEvent *event)
{
    if (close()) {
            Save();
            event->accept();
        } else {
            event->ignore();
        }
}

void HIconMainWindow::viewMousePosChanged(const QPoint& pos,const QPointF &logPos)
{

    QString strViewPos = QString("x=%1,y=%2").arg((int)pos.x()).arg((int)pos.y());
    QString strLogicPos =  QString("log:x=%1,y=%2").arg(logPos.x(),0,'f',1).arg(logPos.y(),0,'f',1);
    statusBar()->showMessage(strLogicPos + " " + strViewPos);
}

void HIconMainWindow::scaleChanged(QString strScale)
{
    if(strScale.isEmpty())
        return;
    if(strScale.endsWith("%"))
        strScale = strScale.mid(0,strScale.lastIndexOf("%"));
    bool bOk;
    double newscale = strScale.toDouble(&bOk)/100;
    if(!bOk)
        return;
    pIconMgr->getIconFrame()->scaleChangedTo(newscale);
    strScale = QString("%1%").arg(pIconMgr->getIconFrame()->scale()*100);
    scaleComboBox->blockSignals(true);
    scaleComboBox->lineEdit()->setText(strScale);
    scaleComboBox->blockSignals(false);
}

void HIconMainWindow::scaleChanged()
{
    QString strScale = scaleComboBox->lineEdit()->text();
    if(strScale.isEmpty())
        return;
    scaleChanged(strScale);

}

void HIconMainWindow::itemInserted(int type)
{
    selectAct->setChecked(true);
    emit selectAct->triggered();
    //setCursor(Qt::ArrowCursor);
}



