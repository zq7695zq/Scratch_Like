#pragma once
#include "../ComponentNest.h"
class ComponentCycleByCount :
	public ComponentNest
{
public:
	ComponentCycleByCount(QPointF startPos, bool isVirtual = false, QGraphicsItem *parent = Q_NULLPTR) : ComponentNest(startPos, isVirtual, "Ñ­»·(´ÎÊı)", ROBOT::COLOR_ORANGE, ROBOT::COLOR_ORANGE_STROKE, true, parent)
	{
	}
	~ComponentCycleByCount()
	{
	}
	inline COM_TYPE getType()
	{
		return COM_TYPE_CYCLE_HEAD;
	}
	inline int getData()
	{
		return this->m_input->getText().toInt();
	}
	inline int getSpare() 
	{
		return this->getData();
	}
};

