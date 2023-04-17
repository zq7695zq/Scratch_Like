#pragma once
#include <QGraphicsSvgItem.h>
#include <QGraphicsLinearLayout.h>
#include <QGraphicsWidget.h>
#include <QGraphicsSceneMouseEvent>

//
#include "../widget/items/BackgroundItem.h"
#include "../const/RobotConst.h"
#include "../enum/ComponentType.h"
#include "ComponentSlot.h"
#pragma execution_character_set("utf-8")
class ComponentSlot;

class Component :
	public QGraphicsWidget
{
protected:
	BackgroundItem *m_background = nullptr;
	QGraphicsWidget *m_form = nullptr;
	//基础属性
	QString name = "Component";
	QList<ComponentSlot> m_slots;
	bool m_isNest = false;
private:
	//鼠标event状态
	bool m_mouseOnClick = false;
	QPointF m_absScenePos = ROBOT::OBJ_DEF_ABS_POS;
	bool m_isVirtual = false;
	unsigned int m_id = -1;
	unsigned int m_parentId = -1;

public:
	Component(QPointF pos, bool isVirtual, QGraphicsItem *parent);

	~Component() {
		delete m_background;
		delete m_form;
	}

	void setDragAble(bool dragable)
	{
		//设置可以拖动
		setAcceptHoverEvents(dragable);
		if (dragable)
			setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
		else
			setFlags(flags()
				.setFlag(QGraphicsItem::ItemIsSelectable, false)
				.setFlag(QGraphicsItem::ItemIsMovable, false)
			);
	}

	virtual int getData() { return 0; }

	virtual int getSpare() { return 0; }

	inline unsigned int getId() { return this->m_id; }

	inline unsigned int getParentId() { return this->m_parentId; }

	inline void setParentId(unsigned int pId) { this->m_parentId = pId; }

	inline QPointF center()
	{
		return this->childrenBoundingRect().center();
	}

	inline qreal width()
	{
		return this->childrenBoundingRect().width();
	}

	inline qreal height()
	{
		return this->childrenBoundingRect().height();
	}

	inline BackgroundItem * getBackGroundItem() { return this->m_background; }

	virtual inline COM_TYPE getType()
	{
		return COM_TYPE_END;
	}

	inline void setAbsScenePos(QPointF absScenePos)
	{
		this->m_absScenePos = absScenePos;
	}

	inline bool isVirtual() { return this->m_isVirtual; }

	inline bool isNest() { return this->m_isNest; }

	bool isLineage(QGraphicsItem *item);

	QGraphicsItem * getNestLineage();

	Component * getChildItem();

	Component * getChildItem(bool inNest);

	Component * getChildOutOfNestItem();

	Component * getChildInNestItem();

	Component * getGrandChild();

	int getChildsHeight();

	QList<ComponentSlot> updateSlotsByComponent(Component * newCom);

	virtual void insertItem(Component * pComponent, ComponentSlot slot);

	void setSlot(ComponentSlot slot);

	bool hasSlot();

	ComponentSlot getSlot();

public:
	QVariant itemChange(GraphicsItemChange change, const QVariant &value);
};