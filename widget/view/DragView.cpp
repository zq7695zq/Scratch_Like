#include "DragView.h"

DragView::DragView(QGraphicsScene *scene, QWidget *parent = Q_NULLPTR) : QGraphicsView (scene, parent)
{
	setStyleSheet("background: transparent;border:0px");
	hide();
	//设置item排序方式与关闭滚动条
	setAlignment(Qt::AlignLeft | Qt::AlignTop);
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

DragView::~DragView()
{
}


void DragView::pressEvent(QMouseEvent *event, QWidget *from)
{
	//qDebug() << __FUNCTION__;
	QPointF DragPos = mapFromGlobal(from->mapToGlobal(event->pos()));
	// 如果是鼠标左键按下
	if (event->button() == Qt::LeftButton)
	{
		//qDebug() << __FUNCTION__ << "CLICKED" << " pos :" << event->pos();
		m_focusOnComponentView = this->m_pComponentView->hasFocus();
		m_focusOnActionView = this->m_pActionView->hasFocus();

		//暂时只处理ComponentView的
		if (m_focusOnActionView)return;

		if (!m_focusOnComponentView && !m_focusOnActionView)return;

		QGraphicsScene * pFocusScene;
		if (m_focusOnComponentView)
			pFocusScene = this->m_pComponentScene;
		else
			pFocusScene = this->m_pActionScene;
		//判断是否在焦点的Scene中点击，并且获取对应的FocusItems
		qDebug() << "pos: " << m_pComponentView->mapFromParent(event->pos());
		for (QGraphicsItem * item : pFocusScene->items(m_pComponentView->mapToScene(m_pComponentView->mapFromParent(event->pos()))))
		{
			if (item->parentWidget() != 0 && RobotUtil::isComponent(item->parentWidget()))
			{
				this->m_onClick = true;
				this->m_pFocusItem = item->parentWidget();
				break;
			}
		}
	}
};

void DragView::releaseEvent(QMouseEvent *event, QWidget *from)
{
	//qDebug() << __FUNCTION__;
	if (!this->m_onClick)return;
	this->m_onClick = false;
	//移动结束把DragView隐藏掉
	this->hide();
	//给ActionView
	this->m_pActionView->moveEnd(event);
	//从dragScene中移除
	this->m_pDragScene->removeItem(this->m_pMouseItem);
	//只有组件库会创建新的item，需要delete掉
	if(m_focusOnComponentView)
		delete this->m_pMouseItem;
	this->m_pMouseItem = nullptr;
};

void DragView::moveEvent(QMouseEvent *event, QWidget *from)
{
	//qDebug() << __FUNCTION__;
	QPointF DragPos = mapFromGlobal(from->mapToGlobal(event->pos()));
	if (!this->m_onClick) return;
	//qDebug() << __FUNCTION__;
	if (this->m_pFocusItem == nullptr || this->m_pFocusItem->hasFocus() || !RobotUtil::isComponent(this->m_pFocusItem))return;
	//qDebug() << "item_" << this->m_pFocusItem << "is moving, type:" << this->m_pFocusItem->data(ROBOT::OBJ_KEY_COMPONENT_TYPE);
	QPointF pos = DragPos;
	if (this->m_pMouseItem == nullptr)
	{
		this->m_pMouseItem = this->m_pComponentFactory->create((COM_TYPE)this->m_pFocusItem->data(ROBOT::OBJ_KEY_COMPONENT_TYPE).toInt(), pos);
		this->show();
		this->m_pDragScene->addItem(this->m_pMouseItem);
	}
	else
	{
		if (this->m_pActionView->geometry().contains(pos.toPoint()))
		{
			this->m_pActionView->componentMove(this->m_pMouseItem, pos);
		}
		pos = this->mapToScene(DragPos.toPoint()) - this->m_pMouseItem->boundingRect().center();
		this->m_pMouseItem->setPos(pos);
	}
	m_pComponentView->viewport()->update();
	m_pActionView->viewport()->update();
};