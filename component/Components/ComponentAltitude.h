#pragma once
#include "../ComponentNest.h"
class ComponentAltitude :
	public ComponentNest
{
public:
	ComponentAltitude(QPointF startPos, bool isVirtual = false, QGraphicsItem *parent = Q_NULLPTR) : ComponentNest(startPos, isVirtual, "ÅÐ¶Ï(¸ß¶È)", ROBOT::COLOR_ROYAL_BLUE, ROBOT::COLOR_ROYAL_BLUE_STROKE, true, parent)
	{
	}
	~ComponentAltitude()
	{
	}
	inline COM_TYPE getType()
	{
		return COM_TYPE_ALTITUDE_HEAD;
	}
};

