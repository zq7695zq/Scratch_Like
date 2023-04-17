#pragma once
#include "../ComponentNorm.h"
class ComponentRight :
	public ComponentNorm
{
public:
	ComponentRight(QPointF startPos, bool isVirtual = false, QGraphicsItem *parent = Q_NULLPTR) : ComponentNorm(startPos, isVirtual, ROBOT::COLOR_BLUE, ROBOT::COLOR_BLUE_STROKE, "��ת(s)", parent)
	{
	}
	~ComponentRight() {}
};

