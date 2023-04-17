#pragma once

#include <QtWidgets/QMainWindow>
#include <QGraphicsView.h>
#include <QLayout>
#include <QStackedLayout>
#include <QTransform>
#include <QPoint>
#include <QWidget>
#include <QMenuBar>
#include <QDesktopWidget>
#include <QApplication>

//�Զ���
#include "scene/ComponentScene.h"
#include "scene/ActionScene.h"

//�Զ����view
#include "view/ComponentView.h"
#include "view/ActionsView.h"
#include "view/DragView.h"

#include "../const/RobotConst.h"

#include "../component/ComponentFactory.h"

#include "../enum/ComponentCategory.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = Q_NULLPTR);
	ComponentScene *m_pComponentScene = nullptr;
	ActionScene *m_pActionScene = nullptr;
	QGraphicsScene *m_pDragScene = nullptr;
	QGraphicsScene *m_pCentralScene = nullptr;

	ComponentView *m_pComponentView = nullptr;
	ActionsView *m_pActionView = nullptr;
	DragView *m_pDragView = nullptr;
	QGraphicsView *m_pCentralView = nullptr;

private:
	bool m_onClick = false;
	QGraphicsItem * m_pFocusItem = nullptr;
	QMenuBar *m_pComponentMenuBar;
private:
	ComponentFactory * m_pComponentFactory = ComponentFactory::getInstance();
	QGraphicsItem * m_pMouseItem = nullptr;
protected:
	void mousePressEvent(QMouseEvent *event) override;        //����
	void mouseReleaseEvent(QMouseEvent *event) override;      //�ͷ�
	void mouseMoveEvent(QMouseEvent *event) override;         //�ƶ�
	void resizeEvent(QResizeEvent * event) override; //�ߴ�ı�
};