#pragma once
#include "../ComponentNest.h"
class ComponentTemperature :
	public ComponentNest
{
public:
	ComponentTemperature(QPointF startPos, bool isVirtual = false, QGraphicsItem *parent = Q_NULLPTR) : ComponentNest(startPos, isVirtual, "ÅÐ¶Ï(ÎÂ¶È)", ROBOT::COLOR_ROYAL_BLUE, ROBOT::COLOR_ROYAL_BLUE_STROKE, true, parent)
	{

	}
	~ComponentTemperature()
	{
	}
	inline COM_TYPE getType()
	{
		return COM_TYPE_TEMPERATURE_HEAD;
	}
};

