#pragma once
#include "Component.h"
#include "../widget/items/InputItem.h"
#include "../widget/items/LabelItem.h"
#pragma execution_character_set("utf-8")
class ComponentNest :
	public Component
{
public:
	ComponentNest(QPointF startPos, bool isVirtual, QString labelText, QString color, QString colorStroke, bool hasInput, QGraphicsItem *parent);
	~ComponentNest()
	{
		delete m_input;
		delete m_nameLabel;
		delete m_backGroundSvg;
	}
	void updateSize();
	virtual void insertItem(Component * pComponent, ComponentSlot slot);
protected:
	InputItem *m_input = nullptr;
	LabelItem *m_nameLabel = nullptr;
	QString *m_backGroundSvg = new QString(ROBOT::SVG_COM_BACKGROUND_NORM);
	QGraphicsLinearLayout *m_layout = new QGraphicsLinearLayout();
};

