#pragma once
#include "../ComponentNorm.h"
class ComponentRightAngle :
	public ComponentNorm
{
public:
	ComponentRightAngle(QPointF startPos, bool isVirtual = false, QGraphicsItem *parent = Q_NULLPTR) : ComponentNorm(startPos, isVirtual, ROBOT::COLOR_BLUE, ROBOT::COLOR_BLUE_STROKE, "×ó×ª(½Ç¶È)", parent)
	{
	}
	~ComponentRightAngle() {}
};

