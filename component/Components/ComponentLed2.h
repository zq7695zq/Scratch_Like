#pragma once
#include "../ComponentNorm.h"
class ComponentLed2 :
	public ComponentNorm
{
public:
	ComponentLed2(QPointF startPos, bool isVirtual = false, QGraphicsItem *parent = Q_NULLPTR) : ComponentNorm(startPos, isVirtual, ROBOT::COLOR_PURPLE, ROBOT::COLOR_PURPLE_STROKE, "LED2(s)", parent)
	{
	}
	~ComponentLed2() {}
};

