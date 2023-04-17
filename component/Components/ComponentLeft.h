#pragma once
#include "../ComponentNorm.h"
class ComponentLeft :
	public ComponentNorm
{
public:
	ComponentLeft(QPointF startPos, bool isVirtual = false, QGraphicsItem *parent = Q_NULLPTR) : ComponentNorm(startPos, isVirtual, ROBOT::COLOR_BLUE, ROBOT::COLOR_BLUE_STROKE, "×ó×ª(s)", parent)
	{
	}
	~ComponentLeft() {}
};

