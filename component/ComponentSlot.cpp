#include "ComponentSlot.h"


ComponentSlot::~ComponentSlot()
{
}

QDebug operator<<(QDebug debug, const ComponentSlot &slot) {
	debug << "ComponentSlot(";
	debug << "rect£º" << slot.m_rect;
	debug << "top£º" << slot.m_pTop;
	debug << "bottom£º" << slot.m_pBottom;
	debug << "target£º" << slot.m_pTarget;
	debug << ")";
	return debug;
}