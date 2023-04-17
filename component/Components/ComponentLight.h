#pragma once
#include "../ComponentNorm.h"
class ComponentLight :
	public ComponentNorm
{
public:
	ComponentLight(QPointF startPos, bool isVirtual = false, QGraphicsItem *parent = Q_NULLPTR) : ComponentNorm(startPos, isVirtual, ROBOT::COLOR_PURPLE, ROBOT::COLOR_PURPLE_STROKE, "≈‹¬Ìµ∆1(s)", parent)
	{
	}
	~ComponentLight() {}
};

