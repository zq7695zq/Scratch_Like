#pragma once
#include "../ComponentNorm.h"
class ComponentDelay :
	public ComponentNorm
{
public:
	ComponentDelay(QPointF startPos, bool isVirtual = false, QGraphicsItem *parent = Q_NULLPTR) : ComponentNorm(startPos, isVirtual, ROBOT::COLOR_PINK, ROBOT::COLOR_PINK_STROKE, "й╠яс(s)", parent)
	{
	}
	~ComponentDelay() {}
};

