#pragma once
#include <QGraphicsView.h>
#include <QWheelEvent>
#include <QScrollBar.h>
#include <QDebug>
#include <QGraphicsWidget>
#include <QMenu>

#include "../../const/RobotConst.h"
#include "DragView.h"

#include "../../component/ComponentFactory.h"

class DragView;

class ActionsView :
	public QGraphicsView
{
public:
	ActionsView(QGraphicsScene *scene);
	~ActionsView();
	void componentMove(QGraphicsItem *item, QPointF posParent);
	void moveEnd(QMouseEvent *event);
	inline void setDragView(DragView * view) { this->m_pDragView = view; }
private:
	inline QPointF getPointFromItemCenter(QGraphicsItem *item)
	{
		return item->sceneBoundingRect().center();
	}
	void finishVirtualItem(bool insert, QMouseEvent *event);
	void insertActionByVirtualItem(QGraphicsItem * childItem);
private:

	DragView * m_pDragView = nullptr;

	QGraphicsItem *m_pVirtualItem = nullptr;

	ComponentFactory * m_pComponentFactory = ComponentFactory::getInstance();

	bool m_onClick = false;
	bool m_moved = false;
	QGraphicsItem * m_pFocusItem = nullptr;
	QGraphicsItem * m_pFocusItemParent = nullptr;


	//debug 使用
	QGraphicsRectItem *debugItem = nullptr;
	QGraphicsEllipseItem *debugItem2 = nullptr;
protected:
	void wheelEvent(QWheelEvent *event);
public:
	void mousePressEvent(QMouseEvent *event) override;        //单击
	void mouseReleaseEvent(QMouseEvent *event) override;      //释放
	void mouseMoveEvent(QMouseEvent *event) override;         //移动
public:
	void actionClickOutPut();
	void actionClickSave();
	void actionClickOpen();
};

