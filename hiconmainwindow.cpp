#include "hiconmainwindow.h"
#include <QKeySequence>
#include <QRectF>
#include <QRect>
#include <QDockWidget>
#include <QStatusBar>
#include <QInputDialog>


HIconMainWindow::HIconMainWindow(HIconMgr *parent) : pIconMgr(parent)
{
    createActions();
    createMenuBars();
    createToolBars();
    createDockWindows();

    pIconWidget = new HIconWidget(pIconMgr);
    setCentralWidget(pIconWidget);
    setWindowTitle("test");

    //pIconDocument = new HIconDocument;
    statusBar()->showMessage("Reday");
    resize(800,600);
    setWindowState(Qt::WindowMaximized);

    init();
}

HIconMainWindow::~HIconMainWindow()
{

}

void HIconMainWindow::init()
{
    pIconFrame = pIconMgr->getIconFrame();
    connect(pIconFrame,SIGNAL(mousePosChanged(const QPoint&,const QPointF&)),this,SLOT(viewMousePosChanged(const QPoint&,const QPointF&)));
    connect(pIconFrame->iconScene(),SIGNAL(itemInserted(int)),this,SLOT(itemInserted(int)));

    showGridAct->setChecked(pIconMgr->getShowGrid());
    showCLineAct->setChecked(pIconMgr->getShowCenterLine());

}

void HIconMainWindow::createActions()
{

    setIconSize(QSize(32,32));
    //文件项
    newAct = new QAction(QIcon(":/images/new.png"), QStringLiteral("新建(&N)"), this);
    newAct->setShortcuts(QKeySequence::New);

    openAct = new QAction(QIcon(":/images/open.png"), QStringLiteral("打开(&O)"), this);
    openAct->setShortcuts(QKeySequence::Open);

    saveAct = new QAction(QIcon(":/images/save.png"), QStringLiteral("保存(&S)"), this);
    saveAct->setShortcuts(QKeySequence::Save);

    closeAct = new QAction(QIcon(":/images/close.png"),QStringLiteral("退出(&E)"),this);
    closeAct->setShortcut(QKeySequence::Quit);


    //编辑项
    undoAct = new QAction(QIcon(":/images/undo.png"),QStringLiteral("撤销(&U)"),this);
    undoAct->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Z));

    redoAct = new QAction(QIcon(":/images/redo.png"),QStringLiteral("重做(&R)"),this);
    redoAct->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Y));

    cutAct = new QAction(QIcon(":/images/cut.png"), QStringLiteral("剪切(&X)"), this);
    cutAct->setShortcuts(QKeySequence::Cut);

    copyAct = new QAction(QIcon(":/images/copy.png"), QStringLiteral("复制(&C)"), this);
    copyAct->setShortcuts(QKeySequence::Copy);


    pasteAct = new QAction(QIcon(":/images/paste.png"), QStringLiteral("粘贴(&P)"), this);
    pasteAct->setShortcuts(QKeySequence::Paste);


    //视图项
    showRulerAct = new QAction(QIcon(":/images/ruler.png"), QStringLiteral("标尺(&R)"), this);
    showRulerAct->setCheckable(true);
    showRulerAct->setChecked(true);

    showGridAct = new QAction(QIcon(":/images/grid.png"), QStringLiteral("网格(&G)"), this);
    connect(showGridAct,SIGNAL(triggered(bool)),this,SLOT(showGrid()));

    showCLineAct = new QAction(QIcon(":/images/center.png"), QStringLiteral("中心线(&C)"), this);
    showCLineAct->setCheckable(true);
    showCLineAct->setChecked(true);

    //缩放项
    fitWidthAct = new QAction(QIcon(":/images/zoom_fit_width.png"), QStringLiteral("合适宽度"), this);
    fitHeightAct = new QAction(QIcon(":/images/zoom_fit_height.png"), QStringLiteral("合适高度"), this);
    zoomInAct = new QAction(QIcon(":/images/zoom_in.png"), QStringLiteral("放大"), this);
    zoomInAct->setCheckable(true);
    zoomOutAct = new QAction(QIcon(":/images/zoom_out.png"), QStringLiteral("缩小"), this);
    zoomOutAct->setCheckable(true);
    zoomOriAct = new QAction(QIcon(":/images/zoom_original.png"), QStringLiteral("自由缩放"), this);
    zoomOriAct->setCheckable(true);
    scaleComboBox = new QComboBox(this);
    scaleComboBox->setEditable(true);
    scaleComboBox->addItem(tr("50%"),0.5);
    scaleComboBox->addItem(tr("70%"),0.75);
    scaleComboBox->addItem(tr("100%"),1);
    scaleComboBox->addItem(tr("150%"),1.5);
    scaleComboBox->addItem(tr("200%"),2);
    scaleComboBox->addItem(tr("300%"),3);
    scaleComboBox->addItem(tr("400%"),4);

    //其他项
    selectAct = new QAction(QIcon(":/images/select.png"), QStringLiteral("选择"), this);
    rotateAct = new QAction(QIcon(":/images/rotate.png"), QStringLiteral("旋转"), this);

    //绘制项
    lineAct = new QAction(QIcon(":/images/line.png"), tr("L&ine"), this);

    lineAct->setCheckable(true);
    connect(lineAct,SIGNAL(triggered(bool)),this,SLOT(drawLine()));

    rectAct = new QAction(QIcon(":/images/rectangle.png"), tr("Rectangle"), this);
    rectAct->setCheckable(true);
    connect(rectAct,SIGNAL(triggered(bool)),this,SLOT(drawRectangle()));

    ellipseAct = new QAction(QIcon(":/images/ellipse.png"), tr("L&ine"), this);
    ellipseAct->setCheckable(true);
    connect(ellipseAct,SIGNAL(triggered(bool)),this,SLOT(drawEllipse()));

    circleAct = new QAction(QIcon(":/images/circle.png"),tr("&Circle"),this);
    circleAct->setCheckable(true);
    connect(circleAct,SIGNAL(triggered(bool)),this,SLOT(drawCircle()));

    hexagonAct = new QAction(QIcon(":/images/hexagon.png"),tr("&Hexagon"),this);
    hexagonAct->setCheckable(true);
    connect(hexagonAct,SIGNAL(triggered(bool)),this,SLOT(drawHexagon()));

    arcAct = new QAction(QIcon(":/images/arc.png"), tr("Arc"), this);
    arcAct->setCheckable(true);
    connect(arcAct,SIGNAL(triggered(bool)),this,SLOT(drawArc()));

    fanAct = new QAction(QIcon(":/images/fan.png"),tr("&Fan"),this);
    fanAct->setCheckable(true);
    connect(fanAct,SIGNAL(triggered(bool)),this,SLOT(drawFan()));

    textAct = new QAction(QIcon(":/images/text.png"),tr("&Text"),this);
    textAct->setCheckable(true);
    connect(textAct,SIGNAL(triggered(bool)),this,SLOT(drawText()));

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

    //QAction *aboutAct = helpMenu->addAction(tr("&About"), this, &HIconMainWindow::about);
    //aboutAct->setStatusTip(tr("Show the application's About box"));

    //QAction *aboutQtAct = helpMenu->addAction(tr("About &Qt"), qApp, &QApplication::aboutQt);
    //aboutQtAct->setStatusTip(tr("Show the Qt library's About box"));

 //////////draw Toool/////////////////////




}


void HIconMainWindow::createToolBars()
{
    fileToolBar = addToolBar(tr("fileBar"));
    fileToolBar->setIconSize(QSize(32,32));
    fileToolBar->addAction(newAct);
    fileToolBar->addAction(openAct);
    fileToolBar->addAction(saveAct);
    fileToolBar->addAction(closeAct);

    editToolBar = addToolBar(tr("editBar"));
    editToolBar->setIconSize(QSize(32,32));
    editToolBar->addAction(undoAct);
    editToolBar->addAction(redoAct);
    editToolBar->addAction(cutAct);
    editToolBar->addAction(copyAct);
    editToolBar->addAction(pasteAct);

    zoomToolBar = addToolBar(tr("zoomBar"));
    zoomToolBar->setIconSize(QSize(32,32));
    zoomToolBar->addAction(fitWidthAct);
    zoomToolBar->addAction(fitHeightAct);
    zoomToolBar->addAction(zoomInAct);
    zoomToolBar->addAction(zoomOutAct);
    zoomToolBar->addAction(zoomOriAct);
    zoomToolBar->addWidget(scaleComboBox);

    drawToolBar = addToolBar(tr("drawToolBar"));
    drawToolBar->addAction(lineAct);
    drawToolBar->addAction(circleAct);
    drawToolBar->addAction(rectAct);
    drawToolBar->addAction(ellipseAct);
    drawToolBar->addAction(hexagonAct);
    drawToolBar->addAction(arcAct);
    drawToolBar->addAction(fanAct);
    drawToolBar->addAction(textAct);

    otherBar = addToolBar(tr("other"));
    otherBar->addAction(selectAct);
    otherBar->addAction(rotateAct);
}

void HIconMainWindow::createMenuBars()
{
    fileMenu = new QMenu(QStringLiteral("文件(&F)"));

    fileMenu->addAction(newAct);
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);
    fileMenu->addSeparator();
    fileMenu->addAction(closeAct);

    editMenu = new QMenu(QStringLiteral("编辑(&E)"),this);
    editMenu->addAction(undoAct);
    editMenu->addAction(redoAct);
    editMenu->addSeparator();
    editMenu->addAction(cutAct);
    editMenu->addAction(copyAct);
    editMenu->addAction(pasteAct);


    viewMenu = new QMenu(QStringLiteral("视图(&V)"),this);
    viewMenu->addAction(showRulerAct);
    viewMenu->addAction(showGridAct);
    viewMenu->addAction(showCLineAct);

    toolMenu = new QMenu(QStringLiteral("绘制(&W)"),this);
    toolMenu->addAction(lineAct);
    toolMenu->addAction(rectAct);
    toolMenu->addAction(ellipseAct);
    toolMenu->addAction(arcAct);
    toolMenu->addAction(fanAct);
    toolMenu->addAction(textAct);

    menuBar()->addMenu(fileMenu);
    menuBar()->addMenu(editMenu);
    menuBar()->addMenu(viewMenu);
    menuBar()->addMenu(toolMenu);
}

void HIconMainWindow::createDockWindows()
{
    QDockWidget* browserIconDock = new QDockWidget(QStringLiteral("图元浏览框"),this);
    browserIconDock->setAllowedAreas(Qt::LeftDockWidgetArea|Qt::RightDockWidgetArea);
    pIconTreeWidget = new HIconTreeWidget(pIconMgr);
    pIconTreeWidget->setRootIsDecorated(true);
    browserIconDock->setWidget(pIconTreeWidget);
    addDockWidget(Qt::LeftDockWidgetArea,browserIconDock);
    pIconTreeWidget->init();
    connect(pIconTreeWidget,SIGNAL(IconNew(const QString&,const int&)),this,SLOT(New(const QString&,const int&)));
    connect(pIconTreeWidget,SIGNAL(IconDel(const QString&,const int&,const QString&)),this,SLOT(Del(const QString&,const int&,const QString&)));

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

}

void HIconMainWindow::saveAs()
{

}

void HIconMainWindow::showGrid()
{
    pIconMgr->setShowGrid(false);
    pIconFrame->iconScene()->update(pIconFrame->getLogicRect());
}

void HIconMainWindow::showCenterLine()
{

}

//draw tool
void HIconMainWindow::drawLine()
{
    pIconMgr->getIconState()->setDrawShape(enumLine);
}

void HIconMainWindow::drawEllipse()
{
    pIconMgr->getIconState()->setDrawShape(enumEllipse);
}

void HIconMainWindow::drawRectangle()
{
    pIconMgr->getIconState()->setDrawShape(enumRectangle);
}

void HIconMainWindow::drawCircle()
{

}

void HIconMainWindow::drawHexagon()
{
    pIconMgr->getIconState()->setDrawShape(enumPolygon);
}

void HIconMainWindow::drawArc()
{
    pIconMgr->getIconState()->setDrawShape(enumArc);
}

void HIconMainWindow::drawFan()
{
    pIconMgr->getIconState()->setDrawShape(enumPie);
}

void HIconMainWindow::drawText()
{
    pIconMgr->getIconState()->setDrawShape(enumText);
}

//关闭
void HIconMainWindow::close()
{

}

//退出
void HIconMainWindow::quit()
{

}

//保存 true 文件 false 库
//void save();

//新建对象
void HIconMainWindow::New(const QString& catalogName,const int& nIconType)//"开关",遥信
{
    pIconMgr->New(catalogName,nIconType);
    pIconWidget->newIconWidget();
    pIconTreeWidget->addIconTreeWigetItem();
   // pIconWidget->getIconFrame()->setSceneRect(QRectF(-500,500,1000,1000));
}

//打开 save falg = true
void HIconMainWindow::open(const QString& catalogName,const QString& uuid)
{

}

//

void HIconMainWindow::Del(const QString& catalogName,const int& nIconType,const QString& uuid)
{
    pIconMgr->Del(catalogName,nIconType,uuid);
    pIconTreeWidget->delIconTreeWidgetItem();
    pIconWidget->delIconWidget();
}

//撤销
void HIconMainWindow::undo()
{

}

//重做
void HIconMainWindow::redo()
{

}

//剪切
void HIconMainWindow::cut()
{

}

//复制
void HIconMainWindow::copy()
{

}

//粘贴
void HIconMainWindow::paste()
{

}

//删除
void HIconMainWindow::Delete()
{

}

//对齐方式--左对齐
void HIconMainWindow::alignLeft()
{

}

//右对齐
void HIconMainWindow::alignRight()
{

}

//水平中间对齐
void HIconMainWindow::alignHCenter()
{

}

//垂直中间对齐
void HIconMainWindow::alignVCenter()
{

}

//上对齐
void HIconMainWindow::alignTop()
{

}

//下对齐
void HIconMainWindow::alignBottom()
{

}

//同等方式--水平同等间隔
void HIconMainWindow::equivalentHSpace()
{

}

//垂直同等间隔
void HIconMainWindow::equivalentVSpace()
{

}

//同等宽度
void HIconMainWindow::equivalentWidth()
{

}

//同等高度
void HIconMainWindow::equivalentHeight()
{

}

//同等大小
void HIconMainWindow::equivalentSize()
{

}

//组合
void HIconMainWindow::groupObj()
{

}

//解除组合
void HIconMainWindow::ungroupObj()
{

}

//翻转--水平翻转
void HIconMainWindow::horizontalTurn()
{

}

//垂直翻转
void HIconMainWindow::verticalTurn()
{

}

//左旋转
void HIconMainWindow::rotateLeft()
{

}

//右旋转
void HIconMainWindow::rotateRight()
{

}

//移动到顶层
void HIconMainWindow::bringToTop()
{

}

//移动到底层
void HIconMainWindow::bringToBottom()
{

}

//上移一层
void HIconMainWindow::bringToUp()
{

}

//下移一层
void HIconMainWindow::bringToDown()
{

}

void HIconMainWindow::about()
{

}

void HIconMainWindow::resizeEvent(QResizeEvent *event)
{
}

void HIconMainWindow::viewMousePosChanged(const QPoint& pos,const QPointF &logPos)
{

    QString strViewPos = QString("x=%1,y=%2").arg((int)pos.x()).arg((int)pos.y());
    QString strLogicPos =  QString("log:x=%1,y=%2").arg(logPos.x(),0,'f',1).arg(logPos.y(),0,'f',1);
    statusBar()->showMessage(strLogicPos + " " + strViewPos);
}

void HIconMainWindow::itemInserted(int type)
{
    if(type == enumLine)
        lineAct->setChecked(false);
    else if(type == enumRectangle)
        rectAct->setChecked(false);
    else if(type == enumEllipse)
    {
        ellipseAct->setChecked(false);
    }
    else if(type == enumArc)
        arcAct->setChecked(false);
    else if(type == enumPie)
        fanAct->setChecked(false);
    else if(type == enumText)
        textAct->setChecked(false);

    //selectAct->setChecked(true);
}



