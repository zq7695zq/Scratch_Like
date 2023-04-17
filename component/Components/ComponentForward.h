#pragma once
#include "../ComponentNorm.h"
class ComponentForward :
	public ComponentNorm
{
public:
	ComponentForward(QPointF startPos, bool isVirtual = false, QGraphicsItem *parent = Q_NULLPTR) : ComponentNorm(startPos, isVirtual, ROBOT::COLOR_BLUE, ROBOT::COLOR_BLUE_STROKE, "Ç°½ø(s)", parent)
	{
	}
	~ComponentForward() {}
};

