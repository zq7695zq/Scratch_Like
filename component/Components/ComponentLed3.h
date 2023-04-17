#pragma once
#include "../ComponentNorm.h"
class ComponentLed3 :
	public ComponentNorm
{
public:
	ComponentLed3(QPointF startPos, bool isVirtual = false, QGraphicsItem *parent = Q_NULLPTR) : ComponentNorm(startPos, isVirtual, ROBOT::COLOR_PURPLE, ROBOT::COLOR_PURPLE_STROKE, "LED3(s)", parent)
	{
	}
	~ComponentLed3() {}
};

