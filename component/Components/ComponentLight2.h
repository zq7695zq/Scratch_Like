#pragma once
#include "../ComponentNorm.h"
class ComponentLight2 :
	public ComponentNorm
{
public:
	ComponentLight2(QPointF startPos, bool isVirtual = false, QGraphicsItem *parent = Q_NULLPTR) : ComponentNorm(startPos, isVirtual, ROBOT::COLOR_PURPLE, ROBOT::COLOR_PURPLE_STROKE, "≈‹¬Ìµ∆2(s)", parent)
	{
	}
	~ComponentLight2() {}
};

