#pragma once
#include "../ComponentNest.h"
class ComponentCycleByCollision :
	public ComponentNest
{
public:
	ComponentCycleByCollision(QPointF startPos, bool isVirtual = false, QGraphicsItem *parent = Q_NULLPTR) : ComponentNest(startPos, isVirtual, "Åö×²¼ì²âÑ­»·", ROBOT::COLOR_ORANGE, ROBOT::COLOR_ORANGE_STROKE, false, parent)
	{
	}
	~ComponentCycleByCollision()
	{

	}
	inline COM_TYPE getType()
	{
		return COM_TYPE_COLLISION_CYCLE_HEAD;
	}
};

