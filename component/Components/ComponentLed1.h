#pragma once
#include "../ComponentNorm.h"
class ComponentLed1 :
	public ComponentNorm
{
public:
	ComponentLed1(QPointF startPos, bool isVirtual = false, QGraphicsItem *parent = Q_NULLPTR) : ComponentNorm(startPos, isVirtual, ROBOT::COLOR_PURPLE, ROBOT::COLOR_PURPLE_STROKE, "LED1(s)", parent)
	{
	}
	~ComponentLed1() {}
};

