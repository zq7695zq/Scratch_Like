#pragma once
#include "../ComponentNest.h"
class ComponentInfared :
	public ComponentNest
{
public:
	ComponentInfared(QPointF startPos, bool isVirtual = false, QGraphicsItem *parent = Q_NULLPTR) : ComponentNest(startPos, isVirtual, "ÅÐ¶Ï(ºìÍâ)", ROBOT::COLOR_ROYAL_BLUE, ROBOT::COLOR_ROYAL_BLUE_STROKE, true, parent)
	{

	}
	~ComponentInfared()
	{
	}
	inline COM_TYPE getType()
	{
		return COM_TYPE_INFRARED_HEAD;
	}
	inline int getData()
	{
		return this->m_input->getText().toInt();
	}
};

