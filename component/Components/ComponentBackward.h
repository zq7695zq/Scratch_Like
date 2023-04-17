#pragma once
#include "../ComponentNorm.h"
class ComponentBackward :
	public ComponentNorm
{
public:
	ComponentBackward(QPointF startPos, bool isVirtual = false, QGraphicsItem *parent = Q_NULLPTR) : ComponentNorm(startPos, isVirtual, ROBOT::COLOR_BLUE, ROBOT::COLOR_BLUE_STROKE, "ºóÍË(s)", parent) {};
	~ComponentBackward() {}
};

