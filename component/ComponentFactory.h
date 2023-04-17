#pragma once
#include "Component.h"
//运动
#include "Components/ComponentForward.h"
#include "Components/ComponentBackward.h"
#include "Components/ComponentLeft.h"
#include "Components/ComponentLeftAngle.h"
#include "Components/ComponentRight.h"
#include "Components/ComponentRightAngle.h"
#include "Components/ComponentForwardByDistance.h"
#include "Components/ComponentBackwardByDistance.h"
//功能
#include "Components/ComponentBeep.h"
#include "Components/ComponentDelay.h"
//LED
#include "Components/ComponentLight.h"
#include "Components/ComponentLight2.h"
#include "Components/ComponentLed1.h"
#include "Components/ComponentLed2.h"
#include "Components/ComponentLed3.h"
#include "Components/ComponentLed4.h"
#include "Components/ComponentLed5.h"
//操作
//变量
//循环
#include "Components/ComponentCycleByCount.h"
#include "Components/ComponentCycleByCollision.h"
//传感器
#include "Components/ComponentInfared.h"
#include "Components/ComponentCollisionDection.h"
#include "Components/ComponentAltitude.h"
#include "Components/ComponentTemperature.h"
//
#include "../enum/ComponentType.h"
#include "../enum/ComponentCategory.h"
#include <QDebug>

class ComponentFactory
{
private:
	static ComponentFactory * m_pInstance;
	ComponentFactory();
	~ComponentFactory();
	int size = 0;
public:
	static ComponentFactory * getInstance() {
		if (m_pInstance == NULL)
			m_pInstance = new ComponentFactory();
		return m_pInstance;
	}
	Component * create(COM_TYPE type, QPointF pos, bool isVirtual = false, bool isMoveable = false, QGraphicsItem * parent = Q_NULLPTR);
	QString getComponentNameByType(COM_TYPE type);
	QString getCategoryName(COM_CATEGORY type);
	COM_CATEGORY getCategoryByType(COM_TYPE type);
	void init();
	int getSize() {
		return this->size;
	}
};

