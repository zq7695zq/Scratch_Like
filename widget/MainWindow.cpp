#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	setObjectName("RobotMainWindow");
	setWindowTitle("RobotMainWindow");
	resize(1024, 768);

	//设置Layout
	QHBoxLayout *pTopLayout = new QHBoxLayout;

	//初始化centralWidget
	this->m_pCentralScene = new QGraphicsScene(this);
	this->m_pCentralView = new QGraphicsView(this->m_pCentralScene, this);
	setCentralWidget(m_pCentralView);
	this->m_pCentralView->setAcceptDrops(true);
	this->m_pCentralView->setLayout(pTopLayout);

	//菜单栏初始化
	//this->m_pComponentMenuBar = new QMenuBar();


	//for (int i = 0; i < 7; i++)
	//{
	//	QMenu * pMenu = m_pComponentMenuBar->addMenu(RobotUtil::getCategoryName((COM_CATEGORY)i));
	//	this->m_pComponentMenuBar->addMenu(pMenu);
	//}
	/*
		COM_CATEGORY_MOVE = 0,
		COM_CATEGORY_FUNCTION = 1,
		COM_CATEGORY_LED = 2,
		COM_CATEGORY_OPERATION = 3,
		COM_CATEGORY_VARIBALE = 4,
		COM_CATEGORY_CYCLE = 5,
		COM_CATEGORY_SENSOR = 6,
		COM_CATEGORY_END = 7
	*/


	//中心区域
	this->m_pComponentScene = new ComponentScene();
	this->m_pActionScene = new ActionScene();

	//组件viewQGraphics
	m_pComponentView = new ComponentView(this->m_pComponentScene);
	m_pComponentView->setObjectName(ROBOT::OBJ_DEF_NAME_COMPONENT);
	m_pComponentView->setMinimumWidth(200);
	m_pActionView = new ActionsView(this->m_pActionScene);
	m_pActionView->setObjectName(ROBOT::OBJ_DEF_NAME_ACTION);
	m_pActionView->setContextMenuPolicy(Qt::CustomContextMenu);

	//Layout中加入组件view
	//pTopLayout->addWidget(m_pComponentMenuBar);
	pTopLayout->addWidget(m_pComponentView);
	pTopLayout->addWidget(m_pActionView);

	//设置布局比例
	//pTopLayout->setStretchFactor(m_pComponentMenuBar, 1);
	pTopLayout->setStretchFactor(m_pComponentView, 0);
	pTopLayout->setStretchFactor(m_pActionView, 6);
	
	//DragView是用来在最顶端显示item的
	m_pDragScene = new QGraphicsScene(this);
	m_pDragView = new DragView(m_pDragScene, this);
	m_pDragView->m_pActionScene = m_pActionScene;
	m_pDragView->m_pActionView = m_pActionView;
	m_pDragView->m_pComponentScene = m_pComponentScene;
	m_pDragView->m_pComponentView = m_pComponentView;
	m_pDragView->m_pDragScene = m_pDragScene;
	

	m_pActionView->setDragView(m_pDragView);
	QDesktopWidget* desktopWidget = QApplication::desktop();
	QRect screenRect = desktopWidget->availableGeometry();  //获取设备屏幕大小
	int width = screenRect.size().width();
	int height = screenRect.size().height() - 40;
	resize(width, height);
	m_pDragView->resize(width, height);
	move(-10, 0);
}


void MainWindow::mousePressEvent(QMouseEvent *event)
{
	//qDebug() << __FUNCTION__;
	m_pDragView->pressEvent(event, this);
	if (event->button() == Qt::RightButton) 
	{
	}
	grabMouse();
};

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
	//qDebug() << __FUNCTION__;
	m_pDragView->releaseEvent(event, this);
	if (this->m_pActionScene->hasFocus()) 
	{
		this->m_pActionView->mouseReleaseEvent(event);
	}
	releaseMouse();
};

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
	//qDebug() << __FUNCTION__;
	//Debug用
	QString debugTitle = "RobotMainWindow";
	debugTitle.append("|MainWindowPos:" + RobotUtil::getPosString(event->pos()))
	.append("|DragViewPos:" + RobotUtil::getPosString(m_pDragView->mapToScene(m_pDragView->mapFromParent(event->pos()))))
	.append("|ComponentViewPos:" + RobotUtil::getPosString(m_pComponentView->mapToScene(m_pComponentView->mapFromParent(event->pos()))))
	.append("|ActionViewPos:" + RobotUtil::getPosString(m_pActionView->mapToScene(m_pActionView->mapFromParent(event->pos()))));
	setWindowTitle(debugTitle);
	//Debug用
	m_pDragView->moveEvent(event, this);
	QMainWindow::mouseMoveEvent(event);
};

void MainWindow::resizeEvent(QResizeEvent * event)
{
	m_pDragView->resize(this->size());
};
