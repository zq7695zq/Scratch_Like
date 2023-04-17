#pragma once
#include <QRect>
#include <QDataStream>
#include "Component.h"
class Component;

class ComponentSlot
{
protected:
	friend QDebug operator<<(QDebug debug, const ComponentSlot &slot);
public:
	ComponentSlot() 
	{
	}
	ComponentSlot(QRectF rect, Component * pTop, Component * pBottom, bool isInNest) : m_rect(rect), m_pTop(pTop), m_pBottom(pBottom), m_isInNest(isInNest)
	{
	}
	~ComponentSlot();
private:
	QRectF m_rect;
	Component * m_pTop = nullptr;
	Component * m_pBottom = nullptr;
	Component * m_pTarget = nullptr;
	bool m_isInNest = false;
public:
	inline bool contains(QPointF pos) { return this->m_rect.contains(pos); }
	inline QPointF getPos() const { return this->m_rect.topLeft(); }
	inline Component * getTop() { return this->m_pTop; }
	inline Component * getBottom() { return this->m_pBottom; }
	inline Component * getTarget() { return this->m_pTarget; }
	inline QRectF getRect() { return this->m_rect; }
	inline bool isInNest() { return m_isInNest; }
	inline void setTarget(Component *target) { this->m_pTarget = target; }
	inline void setTop(Component *pTop){ this->m_pTop = pTop; }
	bool operator==(const ComponentSlot &p)
	{
		return(m_rect == p.m_rect && m_pTop == p.m_pTop && m_pBottom == p.m_pBottom);
	}


};



Q_DECLARE_METATYPE(ComponentSlot)
