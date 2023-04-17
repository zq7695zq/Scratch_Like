#include "ActionsView.h"

ActionsView::ActionsView(QGraphicsScene *scene) : QGraphicsView(scene)
{
	//setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//隐藏水平条
	//setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//隐藏竖条
	//setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
	//setResizeAnchor(QGraphicsView::AnchorUnderMouse);
	setAlignment(Qt::AlignLeft | Qt::AlignTop);
}

ActionsView::~ActionsView()
{
}

void ActionsView::wheelEvent(QWheelEvent *event)
{
	if ((event->modifiers() & Qt::ControlModifier) != 0)
	{
		RobotUtil::scaleView(event->pos(), event->delta(), this);
		RobotUtil::scaleView(event->pos(), event->delta(), this->m_pDragView);
	}
	else 
	{
		QGraphicsView::wheelEvent(event);
	}

}

void ActionsView::mousePressEvent(QMouseEvent *event)
{
	qDebug() << __FUNCTION__ << " pos :" << event->pos();
	QPointF pos = mapToScene(event->pos());
	// 如果是鼠标左键按下
	if (event->button() == Qt::LeftButton)
	{
		//判断是否在焦点的Scene中点击，并且获取对应的FocusItems
		for (QGraphicsItem * item : this->scene()->items(pos))
		{
			if (RobotUtil::isComponent(item->parentItem()))
				item = item->parentItem();
			if (RobotUtil::isComponent(item))
			{
				qDebug() << "currentItem：" << item << "parentItem:" << item->parentItem() << "scenePos：" << item->scenePos() << "childrenBoundingRect：" << item->childrenBoundingRect();
				this->m_onClick = true;
				this->m_pFocusItem = item;
				if (this->m_pFocusItem->parentItem() && RobotUtil::isComponent(this->m_pFocusItem->parentItem()))
				{
					//作为子节点
					((Component *)this->m_pFocusItem)->setAbsScenePos(this->m_pFocusItem->scenePos());
					this->m_pFocusItemParent = this->m_pFocusItem->parentItem();
					this->m_pFocusItem->setParentItem(nullptr);
				}
				break;
			}
		}
	}
	else if (event->button() == Qt::RightButton)
	{
		QMenu menu(this);
		menu.addAction("输出结果", this, &ActionsView::actionClickOutPut);
		menu.addAction("保存文件");
		menu.addAction("读取文件");
		menu.addAction("删除Item");
		menu.exec(mapToGlobal(event->pos()));
	}
	QGraphicsView::mousePressEvent(event);
}

void ActionsView::mouseReleaseEvent(QMouseEvent *event)
{
	qDebug() << __FUNCTION__;
	if (this->m_onClick)
		this->moveEnd(event);
	//this->clearFocus();
	QGraphicsView::mouseReleaseEvent(event);
}

void ActionsView::mouseMoveEvent(QMouseEvent *event)
{
	//qDebug() << __FUNCTION__;
	if (this->m_onClick)
		this->componentMove(this->m_pFocusItem, mapToParent(event->pos()));
	//重绘制背景
	viewport()->update();

	QGraphicsView::mouseMoveEvent(event);
}

void ActionsView::componentMove(QGraphicsItem *movingItem, QPointF posParent)
{
	this->setFocus();
	//qDebug() << __FUNCTION__ << item << mapFromParent(pos.toPoint());
	//转换为ActionsScene内的坐标
	QPointF mousePos = mapToScene(mapFromParent(posParent.toPoint()));
	QPointF itemPos = mapToScene(mapFromParent(movingItem->pos().toPoint()));
	//qDebug() << itemPos;
	if (this->m_pVirtualItem != nullptr)
	{
		QRectF rect = this->m_pVirtualItem->childrenBoundingRect();
		rect.moveTopLeft(this->m_pVirtualItem->scenePos());

		//鼠标移动到别处了，虚拟item需要销毁
		if (rect.contains(mousePos))
		{
			return;
		}
		else
		{
			qDebug() << "move out" << rect;
			this->finishVirtualItem(false, nullptr);
			return;
		}
	}
	/*
		有三种插入情况：
		1、从组件上方插入，如果该组件是最上级组件，即取代他成为父组件
		2、从组件下方插入，成为改组件的子组件
		3、从两组件中间插入，成为下面组件的父组件，上面组件的子组件

		要寻找距离鼠标最近的item，如果在其下方，则创建一个虚拟的Component令他成为子组件，其原本子组件成为该虚拟Componet的子组件（没有子组件则跳过这一步）
		如果在其上方，则先查看该组件是否存在父组件，如果存在则指向父组件执行在下方的操作，如果没有则在上方创建虚拟Component作为父组件。
	*/

	//第一步  寻找距离鼠标最近的item
	QList<QGraphicsItem *> items = this->items();

	if (items.length() == 0)return;

	Component *minDistanceItem = nullptr;
	for (QGraphicsItem * item : items)
	{
		//过滤:虚拟item、正在移动的item、当前item的上级没有itemMoving
		if (RobotUtil::isComponent(item) && item != this->m_pVirtualItem && item != movingItem && !((Component *)item)->isLineage(movingItem))
		{
			QList<ComponentSlot> _slots = ((Component *)item)->updateSlotsByComponent((Component *)movingItem);
			foreach(ComponentSlot i, _slots)
			{
				if (i.contains(mousePos))
				{
					if (item->parentItem() && i == _slots.at(0))
						continue;
					if(!minDistanceItem || (item->boundingRect().center() - mousePos).manhattanLength() < (minDistanceItem->boundingRect().center() - mousePos).manhattanLength())
						minDistanceItem = (Component *)item;
				}
			}
		}
	}
	//找不到合适的 就返回
	if (minDistanceItem == nullptr)
		return;
	this->m_moved = true;
	qDebug() << "-----------start-----------";
	//第二步  判断鼠标的item与最近的item的相对位置（上方矩形内/下方矩形内）
	bool isOnTop = getPointFromItemCenter(minDistanceItem).y() >= mousePos.y();
	//计算新item的相对坐标，也作为新item的坐标用
	QPointF virtualItemRelativePos;
	if (isOnTop && minDistanceItem->parentItem())
	{
		minDistanceItem = (Component *)minDistanceItem->parentWidget();
		isOnTop = getPointFromItemCenter(minDistanceItem).y() >= mousePos.y();
		if (minDistanceItem->parentItem() == this->m_pVirtualItem)
			qDebug() << "is virtualItem";
	}
	else
	{
		qDebug() << "minDistanceItem->parentItem():" << minDistanceItem->parentItem() << "isOnTop:" << isOnTop << "minDistanceItem：" << minDistanceItem;
	}
	//判断插槽 获得新item的相对坐标
	QList<ComponentSlot> _slots = minDistanceItem->updateSlotsByComponent((Component *)movingItem);
	ComponentSlot virtualItemSlot;
	int slotNum = 0;
	foreach(ComponentSlot i, _slots)
	{
		if (i.contains(mousePos))
		{
			if (minDistanceItem->parentItem() && slotNum == 0)
				continue;
			virtualItemSlot = i;
			break;
		}

		slotNum++;
	}
	//在上面 整块插入是不允许的
	if (isOnTop && virtualItemSlot == _slots.at(0) && (((Component *)movingItem)->getChildItem(false) || ((Component *)movingItem)->getChildItem(true)))return;

	if (isOnTop)
	{
		virtualItemRelativePos = virtualItemSlot.getPos();
	}
	else
	{
		//转换为相对坐标
		virtualItemRelativePos = QPointF(virtualItemSlot.getPos().x() - minDistanceItem->scenePos().x(), virtualItemSlot.getPos().y() - minDistanceItem->scenePos().y());
	}

	//第三步 插入virtualItem到对应的位置
	//qDebug() << "isOnTop：" << isOnTop
	//	<< "virtualItemRelativePos：" << virtualItemRelativePos;
		//<< "virtualItemCenterAbsolutePos：" << virtualItemCenterAbsolutePos
		//<< "virtualItemRect" << virtualItemSlot;
	if (virtualItemSlot.contains(mousePos))
	{
		qDebug() << " virtualItemRect.contains" << mousePos << "slotNum：" << slotNum << "slot：" << virtualItemSlot << "minDistanceItem ：" << minDistanceItem;
		this->m_pVirtualItem = this->m_pComponentFactory->create((COM_TYPE)movingItem->data(ROBOT::OBJ_KEY_COMPONENT_TYPE).toInt(), virtualItemRelativePos, true, false, nullptr);
		minDistanceItem->insertItem((Component *)this->m_pVirtualItem, virtualItemSlot);
		this->scene()->addItem(this->m_pVirtualItem);
	}

	qDebug() << "-----------end-----------";
}

void ActionsView::moveEnd(QMouseEvent *event)
{
	//虚拟item
	this->finishVirtualItem(true, event);
	this->update();
	//延长、缩短嵌套结构尺寸
	for (QGraphicsItem * item : this->items())
	{
		Component * pParent = (Component *)item;
		if (pParent && RobotUtil::isComponent(pParent) && RobotUtil::isNestCategory(RobotUtil::getCategoryByType(pParent->getType())))
			((ComponentNest *)pParent)->updateSize();
	}

	this->m_pFocusItemParent = nullptr;
	this->m_pFocusItem = nullptr;
	this->m_onClick = false;
	this->m_moved = false;

}

void ActionsView::finishVirtualItem(bool insert, QMouseEvent *event)
{
	if (this->m_pVirtualItem != nullptr)
	{
		Component * pVirtualParent = (Component *)this->m_pVirtualItem->parentItem();
		ComponentSlot slot = ((Component *)m_pVirtualItem)->getSlot();
		//插入新节点到对应的位置
		if (insert)
		{
			//需要插入
			Component * targetItem = nullptr;
			if (this->m_onClick)
				targetItem = (Component *)this->m_pFocusItem;
			else
			{
				targetItem = this->m_pComponentFactory->create((COM_TYPE)this->m_pVirtualItem->data(ROBOT::OBJ_KEY_COMPONENT_TYPE).toInt(), this->m_pVirtualItem->scenePos(), false, true, nullptr);
				this->scene()->addItem(targetItem);
			}
			qDebug() << "insert Slot:" << slot;
			if (pVirtualParent)
			{
				pVirtualParent->insertItem(targetItem, slot);
			}
			else
			{
				Component * pChild = slot.getBottom();
				if (pChild)
				{
					QList<ComponentSlot> _slots = targetItem->updateSlotsByComponent(pChild);
					if (_slots.length() > 1)
						targetItem->insertItem(pChild, _slots.length() > 2 ? _slots.at(2) : _slots.at(1));
				}
			}
		}
		else
		{
			if (slot.getTop())
			{
				if (slot.getBottom())
				{
					qDebug() << "top & bottom";
					if (slot.getTop()->isNest())
					{
						QList<ComponentSlot> _slots = slot.getTop()->updateSlotsByComponent(slot.getTop());
						if (_slots.length() > 2)
						{
							if (slot.getTop()->getChildInNestItem() == this->m_pVirtualItem) 
								slot.getBottom()->setAbsScenePos(_slots.at(1).getPos());
							if (slot.getTop()->getChildOutOfNestItem() == this->m_pVirtualItem)
								slot.getBottom()->setAbsScenePos(_slots.at(2).getPos());
							slot.getBottom()->setData(ROBOT::OBJ_KEY_COMPONENT_INNEST, slot.isInNest());
						}
					}
					slot.getBottom()->setParentItem(slot.getTop());
				}
				else
				{
					qDebug() << "top & !bottom";
				}
			}
			else
			{
				if (slot.getBottom())
				{
					qDebug() << "!top & bottom";
					slot.getBottom()->setAbsScenePos(slot.getBottom()->scenePos());
					slot.getBottom()->setParentItem(nullptr);
				}
				else
				{
					qDebug() << "!top & !bottom";
				}
			}
		}
		//删除虚拟节点
		this->scene()->removeItem(this->m_pVirtualItem);
		delete this->m_pVirtualItem;
		this->m_pVirtualItem = nullptr;
	}
	else
	{
		//往空区域放置的情况
		if (!this->hasFocus())return;
		if (this->m_pDragView->m_pMouseItem)
		{
			if (this->m_onClick || !this->m_pDragView->m_focusOnComponentView)return;
			QGraphicsItem * targetItem = this->m_pComponentFactory->create((COM_TYPE)this->m_pDragView->m_pMouseItem->data(ROBOT::OBJ_KEY_COMPONENT_TYPE).toInt(), QPoint(), false, true, nullptr);
			this->scene()->addItem(targetItem);
			targetItem->setPos(this->mapToScene(this->mapFromParent(event->pos())));
		}
		else
		{
			if (this->m_onClick && this->m_pFocusItemParent && !this->m_moved && this->m_pFocusItem != this->m_pFocusItemParent)
			{
				((Component *)this->m_pFocusItem)->setAbsScenePos(this->m_pFocusItem->scenePos());
				this->m_pFocusItem->setParentItem(this->m_pFocusItemParent);
			}
		}
	}
}

QString itq(int i) {
	return QString::number(i);
}


QString appendNode(QString ret, int index, int type, int data, int next, int pre, int spare) {
	ret.append(itq(index)
		.append(" type ").append(itq(type))
		.append(" data ").append(itq(data))
		.append(" next ").append(itq(next))
		.append(" pre ").append(itq(pre))
		.append(" spare ").append(itq(spare))
	);
	ret.append("*\r\n");
	return ret;
}

QString getRealOutPut(QString str) {
	return str
		.replace(" type ", "+")
		.replace(" data ", "+")
		.replace(" next ", "+")
		.replace(" pre ", "+")
		.replace(" spare ", "+");
}

QString getComponentOutPut(Component * component, int &index)
{
	QString ret;
	//int index = startIndex;
	Component * pCom = (Component *)component;
	if (pCom->isNest())
	{
		ret = appendNode(ret, index, component->getType(), component->getData(), index + 1, index - 1, component->getData());
		int startIndex = index;
		index++;
		if (pCom->getChildInNestItem())
			ret.append(getComponentOutPut(pCom->getChildInNestItem(), index));
		ret = appendNode(ret, index, component->getType() + 1, startIndex, index + 1, index - 1, 0);
		index++;
		if (pCom->getChildOutOfNestItem())
			ret.append(getComponentOutPut(pCom->getChildOutOfNestItem(), index));
	}
	else
	{
		ret = appendNode(ret, index, component->getType(), component->getData(), index + 1, index - 1, 0);
		index++;
		if (pCom->getChildItem())
			ret.append(getComponentOutPut(pCom->getChildItem(), index));
	}
	return ret;
}

void ActionsView::actionClickOutPut()
{
	qDebug() << __FUNCTION__;
	int startIndex = 1;
	QString ret = "0 type 0 data 0 next 1 pre 0 spare -3*\r\n";
	foreach(QGraphicsItem *item, this->items())
	{
		//只遍历无父节点的itme
		if (item->parentItem() || !RobotUtil::isComponent(item)) continue;
		ret = ret.append(getComponentOutPut((Component *)item, startIndex));
		qDebug() << ret;
		qDebug() << getRealOutPut(ret);
		
	}
}
