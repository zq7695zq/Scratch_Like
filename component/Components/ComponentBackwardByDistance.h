#pragma once
#include "../ComponentNorm.h"
class ComponentBackwardByDistance :
	public ComponentNorm
{
public:
	ComponentBackwardByDistance(QPointF startPos, bool isVirtual = false, QGraphicsItem *parent = Q_NULLPTR) : ComponentNorm(startPos, isVirtual, ROBOT::COLOR_BLUE, ROBOT::COLOR_BLUE_STROKE, "∫ÛÕÀ(æ‡¿Î)", parent)
	{

	}
	~ComponentBackwardByDistance() {}
};

