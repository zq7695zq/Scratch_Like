#pragma once
#include "../ComponentNorm.h"
class ComponentLed4 :
	public ComponentNorm
{
public:
	ComponentLed4(QPointF startPos, bool isVirtual = false, QGraphicsItem *parent = Q_NULLPTR) : ComponentNorm(startPos, isVirtual, ROBOT::COLOR_PURPLE, ROBOT::COLOR_PURPLE_STROKE, "LED4(s)", parent)
	{
	}
	~ComponentLed4() {}
};

