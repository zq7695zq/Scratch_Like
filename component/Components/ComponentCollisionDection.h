#pragma once
#include "../ComponentNest.h"
class ComponentCollisionDection :
	public ComponentNest
{
public:
	ComponentCollisionDection(QPointF startPos, bool isVirtual = false, QGraphicsItem *parent = Q_NULLPTR) : ComponentNest(startPos, isVirtual, "ÅÐ¶Ï(Åö×²)", ROBOT::COLOR_ROYAL_BLUE, ROBOT::COLOR_ROYAL_BLUE_STROKE, true, parent)
	{
	}
	~ComponentCollisionDection()
	{

	}
	inline COM_TYPE getType()
	{
		return COM_TYPE_COLLISION_DETECTION_HEAD;
	}
};

