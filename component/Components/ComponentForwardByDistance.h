#pragma once
#include "../ComponentNorm.h"
#pragma execution_character_set("utf-8")

class ComponentForwardByDistance :
	public ComponentNorm
{
public:
	ComponentForwardByDistance(QPointF startPos, bool isVirtual = false, QGraphicsItem *parent = Q_NULLPTR) : ComponentNorm(startPos, isVirtual, ROBOT::COLOR_BLUE, ROBOT::COLOR_BLUE_STROKE, "Ç°½ø(¾àÀë)", parent)
	{

	}
	~ComponentForwardByDistance() {}
};

