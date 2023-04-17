#pragma once
#include <QGraphicsView>

#include "ComponentView.h"
#include "ActionsView.h"

#include "../scene/ComponentScene.h"
#include "../scene/ActionScene.h"

#include "../../const/RobotConst.h"

#include "../../component/ComponentFactory.h"

class ActionsView;

class DragView :
	public QGraphicsView
{
private:
	bool m_onClick = false;
	QGraphicsItem * m_pFocusItem = nullptr;

public:
	ComponentFactory * m_pComponentFactory = ComponentFactory::getInstance();
	QGraphicsItem * m_pMouseItem = nullptr;
	bool m_focusOnComponentView = false;
	bool m_focusOnActionView = false;
public:
	DragView(QGraphicsScene *scene, QWidget *parent);
	~DragView();
	void pressEvent(QMouseEvent *event, QWidget *from);        //µ¥»÷
	void releaseEvent(QMouseEvent *event, QWidget *from);      //ÊÍ·Å
	void moveEvent(QMouseEvent *event, QWidget *from);         //ÒÆ¶¯
public:

	ComponentScene *m_pComponentScene = nullptr;
	ActionScene *m_pActionScene = nullptr;
	QGraphicsScene *m_pDragScene = nullptr;

	ComponentView *m_pComponentView = nullptr;
	ActionsView *m_pActionView = nullptr;
};

