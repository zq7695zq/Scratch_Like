#include "ComponentSlot.h"


ComponentSlot::~ComponentSlot()
{
}

QDebug operator<<(QDebug debug, const ComponentSlot &slot) {
	debug << "ComponentSlot(";
	debug << "rect��" << slot.m_rect;
	debug << "top��" << slot.m_pTop;
	debug << "bottom��" << slot.m_pBottom;
	debug << "target��" << slot.m_pTarget;
	debug << ")";
	return debug;
}