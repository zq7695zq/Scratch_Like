#pragma once
#include "../ComponentNorm.h"
class ComponentLeftAngle :
	public ComponentNorm
{
public:
	ComponentLeftAngle(QPointF startPos, bool isVirtual = false, QGraphicsItem *parent = Q_NULLPTR) : ComponentNorm(startPos, isVirtual, ROBOT::COLOR_BLUE, ROBOT::COLOR_BLUE_STROKE, "×ó×ª(½Ç¶È)", parent)
	{
	}
	~ComponentLeftAngle() {}
};

