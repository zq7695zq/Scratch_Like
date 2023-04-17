#pragma once
#include "../ComponentNorm.h"
class ComponentBeep :
	public ComponentNorm
{
public:
	ComponentBeep(QPointF startPos, bool isVirtual = false, QGraphicsItem *parent = Q_NULLPTR) : ComponentNorm(startPos, isVirtual, ROBOT::COLOR_PINK, ROBOT::COLOR_PINK_STROKE, "·äÃù(´ÎÊý)", parent)
	{
	}
	~ComponentBeep() {}
};

