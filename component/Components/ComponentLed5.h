#pragma once
#include "../ComponentNorm.h"
class ComponentLed5 :
	public ComponentNorm
{
public:
	ComponentLed5(QPointF startPos, bool isVirtual = false, QGraphicsItem *parent = Q_NULLPTR) : ComponentNorm(startPos, isVirtual, ROBOT::COLOR_PURPLE, ROBOT::COLOR_PURPLE_STROKE, "LED5(s)", parent)
	{
	}
	~ComponentLed5() {}
};

