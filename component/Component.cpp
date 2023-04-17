#include "Component.h"

Component::Component(QPointF pos, bool isVirtual, QGraphicsItem *parent = Q_NULLPTR) : QGraphicsWidget(parent)
{
	//设置坐标
	setPos(pos);
	//if(parent == Q_NULLPTR)
	//setFlag(QGraphicsItem::ItemIsMovable, true);
	//this->setLayout(m_layout);
	this->m_isVirtual = isVirtual;

	setFlag(QGraphicsItem::ItemSendsScenePositionChanges, true);
	setFlag(QGraphicsItem::ItemIsFocusable, true);
	this->m_id = RobotUtil::generateId();
}


bool Component::isLineage(QGraphicsItem *item)
{
	QGraphicsItem *parent = (QGraphicsItem *)this;
	while (QGraphicsItem *grandPa = parent->parentItem())
	{
		if (grandPa == item) return true;
		parent = grandPa;
	}
	return false;

}
QGraphicsItem * Component::getNestLineage()
{
	QGraphicsItem *parent = (QGraphicsItem *)this;
	while (QGraphicsItem *grandPa = parent->parentItem())
	{
		
		if (RobotUtil::isComponent(grandPa) && RobotUtil::isNestCategory(RobotUtil::getCategoryByType(((Component *)grandPa)->getType()))) return grandPa;
		parent = grandPa;
	}
	return nullptr;
}

Component * Component::getChildItem()
{
	QGraphicsItem *pChild = nullptr;

	for (QGraphicsItem *item : this->childItems())
	{
		if (RobotUtil::isComponent(item))
		{
			pChild = item;
			break;
		}
	}
	return (Component *)pChild;
}

Component * Component::getChildItem(bool inNest)
{
	QGraphicsItem *pChild = nullptr;

	for (QGraphicsItem *item : this->childItems())
	{
		if (RobotUtil::isComponent(item) && ( (inNest && RobotUtil::isInNest(item)) || (!inNest && !RobotUtil::isInNest(item))))
		{
			pChild = item;
			break;
		}
	}
	return (Component *)pChild;
}

Component * Component::getChildOutOfNestItem()
{
	return getChildItem(false);
}

Component * Component::getChildInNestItem()
{
	return getChildItem(true);
}

Component * Component::getGrandChild()
{
	Component * pGrandChild = this;
	while (pGrandChild = pGrandChild->isNest() ? pGrandChild->getChildOutOfNestItem(): pGrandChild->getChildItem())
	{
		if ((pGrandChild->isNest() ? pGrandChild->getChildOutOfNestItem() : pGrandChild->getChildItem()) == nullptr)
			return pGrandChild;
	}
	return pGrandChild;
}

int Component::getChildsHeight()
{
	Component *pChild = this->getChildInNestItem();
	int totalHeight = 0;
	if (!pChild)return totalHeight;
	do
	{
		if (pChild->isNest()) 
		{
			totalHeight += pChild->getChildsHeight() == 0 ? 120 : pChild->getChildsHeight() + 85;
		}
		else 
		{
			totalHeight += pChild->getBackGroundItem()->getSize().height();
		}
	} while (pChild = pChild->getChildOutOfNestItem());
	return totalHeight;
}

QList<ComponentSlot> Component::updateSlotsByComponent(Component * newCom)
{
	m_slots.clear();
	//设置插槽的尺寸(根据新插入的item样式)
	QSizeF slotSize = newCom->boundingRect().size();
	slotSize.setHeight(this->boundingRect().height() / 2 + slotSize.height());
	slotSize.setWidth(slotSize.width());
	//循环结构有三个插槽
	//if (!this->parentItem())
	//{
		//上方的只有没有父节点才会判断 
		m_slots.append(ComponentSlot(QRectF(QPointF(this->scenePos().x(), this->scenePos().y() - newCom->boundingRect().size().height()), slotSize), nullptr, this, false));
	//}
	if (RobotUtil::isNestCategory(RobotUtil::getCategoryByType(this->getType())))
	{
		//包含的插槽
		m_slots.append(ComponentSlot(QRectF(QPointF(this->scenePos().x() + 16, this->scenePos().y() + this->boundingRect().height() - 3), slotSize), this, this->getChildInNestItem(), true));
		//末尾的插槽
		m_slots.append(ComponentSlot(QRectF(QPointF(this->scenePos().x(), this->scenePos().y() + (this->getChildsHeight() == 0 ? 30 : this->getChildsHeight()) + 85), slotSize), this, this->getChildOutOfNestItem(), false));
	}
	else 
	{
		//末尾的插槽
		m_slots.append(ComponentSlot(QRectF(QPointF(this->scenePos().x(), this->scenePos().y() + this->boundingRect().height() + 5), slotSize), this, this->getChildItem(), false));
	}
	return m_slots;
}

QVariant Component::itemChange(GraphicsItemChange change, const QVariant &value)
{
	if (RobotUtil::isComponent(this) && !((Component *)this)->isVirtual())
	{
		if (change == GraphicsItemChange::ItemParentHasChanged)
		{
			//qDebug() << "GraphicsItemChange::ItemParentHasChanged" << this;
			QGraphicsItem * pParent = value.value<QGraphicsItem*>();
			if (m_absScenePos != ROBOT::OBJ_DEF_ABS_POS)
			{
				QPointF finalPos = this->m_absScenePos;
				if (pParent && RobotUtil::isComponent(pParent))
				{
					finalPos = this->m_absScenePos - pParent->scenePos();
					qDebug() << "parent：" << pParent << "currentPos：" << this->pos() << "m_absScenePos：" << this->m_absScenePos << "relativePos：" << finalPos;
					this->setPos(finalPos);
				}
				else
				{
					this->setPos(finalPos);
				}
				m_absScenePos = ROBOT::OBJ_DEF_ABS_POS;
			}
		}
		else if (change == GraphicsItemChange::ItemScenePositionHasChanged)
		{
			//qDebug() << "GraphicsItemChange::ItemScenePositionHasChanged";
			this->setFocus();
		}
		else if (change == QGraphicsItem::ItemChildAddedChange || change == QGraphicsItem::ItemChildRemovedChange)
		{
		}
		else if (change == QGraphicsItem::ItemPositionHasChanged)
		{
		}
	}
	return QGraphicsItem::itemChange(change, value);
}

void Component::insertItem(Component * pComponent, ComponentSlot slot)
{
	if (!pComponent)return;
	slot.setTarget(pComponent);
	pComponent->setSlot(slot);
	if (this->m_isNest)
	{
		if(slot.getTop() == this)
			pComponent->setParentId(this->getId());
	}
	else 
	{
		pComponent->setParentId(this->getParentId());
	}
	pComponent->setAbsScenePos(slot.getPos());
	pComponent->setParentItem(slot.getTop());
	if (slot.getBottom()) 
	{
		QList<ComponentSlot> _slots = slot.getTarget()->updateSlotsByComponent(slot.getBottom());
		if (slot.getTarget()->isNest())
		{
			slot.getTarget()->insertItem(slot.getBottom(), _slots.at(2));
		}
		else 
		{
			if (slot.getTarget()->getGrandChild()) 
			{
				_slots = slot.getTarget()->getGrandChild()->updateSlotsByComponent(slot.getBottom());
				slot.getTarget()->getGrandChild()->insertItem(slot.getBottom(), _slots.at(1));
			}	
			else
				slot.getTarget()->insertItem(slot.getBottom(), _slots.at(1));
		}
	}
	else 
	{
		//qDebug() << "error";
	}
	pComponent->setData(ROBOT::OBJ_KEY_COMPONENT_INNEST, slot.isInNest());
}

void Component::setSlot(ComponentSlot slot) { this->setData(ROBOT::OBJ_KEY_COMPONENT_SLOT, QVariant::fromValue(slot)); }

bool Component::hasSlot() { return this->data(ROBOT::OBJ_KEY_COMPONENT_SLOT).isValid(); }

ComponentSlot Component::getSlot() { return this->data(ROBOT::OBJ_KEY_COMPONENT_SLOT).value<ComponentSlot>(); }