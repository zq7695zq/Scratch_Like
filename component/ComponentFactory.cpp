#include "ComponentFactory.h"

ComponentFactory * ComponentFactory::m_pInstance = nullptr;

ComponentFactory::ComponentFactory()
{
}

ComponentFactory::~ComponentFactory()
{
}

Component * ComponentFactory::create(COM_TYPE type, QPointF pos, bool isVirtual, bool isMoveable, QGraphicsItem * parent)
{
	Component * ret = nullptr;
	switch (type) 
	{
	case COM_TYPE_FORWARD:
		ret = new ComponentForward(pos, isVirtual, parent);
		break;
	case COM_TYPE_BACKWARD:
		ret = new ComponentBackward(pos, isVirtual, parent);
		break;
	case COM_TYPE_LEFT:
		ret = new ComponentLeft(pos, isVirtual, parent);
		break;
	case COM_TYPE_RIGHT:
		ret = new ComponentRight(pos, isVirtual, parent);
		break;
	case COM_TYPE_FORWARD_DISTENCE:
		ret = new ComponentForwardByDistance(pos, isVirtual, parent);
		break;
	case COM_TYPE_BACKWARD_DISTENCE:
		ret = new ComponentBackwardByDistance(pos, isVirtual, parent);
		break;
	case COM_TYPE_LEFT_ANGLE:
		ret = new ComponentLeftAngle(pos, isVirtual, parent);
		break;
	case COM_TYPE_RIGHT_ANGLE:
		ret = new ComponentRightAngle(pos, isVirtual, parent);
		break;
	case COM_TYPE_BEEP:
		ret = new ComponentBeep(pos, isVirtual, parent);
		break;
	case COM_TYPE_DELAY:
		ret = new ComponentDelay(pos, isVirtual, parent);
		break;
	case COM_TYPE_LIGHT:
		ret = new ComponentLight(pos, isVirtual, parent);
		break;
	case COM_TYPE_LIGHT2:
		ret = new ComponentLight2(pos, isVirtual, parent);
		break;
	case COM_TYPE_LED1:
		ret = new ComponentLed1(pos, isVirtual, parent);
		break;
	case COM_TYPE_LED2:
		ret = new ComponentLed2(pos, isVirtual, parent);
		break;
	case COM_TYPE_LED3:
		ret = new ComponentLed3(pos, isVirtual, parent);
		break;
	case COM_TYPE_LED4:
		ret = new ComponentLed4(pos, isVirtual, parent);
		break;
	case COM_TYPE_LED5:
		ret = new ComponentLed5(pos, isVirtual, parent);
		break;
	case COM_TYPE_CYCLE_HEAD:
		ret = new ComponentCycleByCount(pos, isVirtual, parent);
		break;
	case COM_TYPE_COLLISION_CYCLE_HEAD:
		ret = new ComponentCycleByCollision(pos, isVirtual, parent);
		break;
	case COM_TYPE_INFRARED_HEAD:
		ret = new ComponentInfared(pos, isVirtual, parent);
		break;
	case COM_TYPE_COLLISION_DETECTION_HEAD:
		ret = new ComponentCollisionDection(pos, isVirtual, parent);
		break;
	case COM_TYPE_ALTITUDE_HEAD:
		ret = new ComponentAltitude(pos, isVirtual, parent);
		break;
	case COM_TYPE_TEMPERATURE_HEAD:
		ret = new ComponentTemperature(pos, isVirtual, parent);
		break;
	}
	if (ret != nullptr) { 
		ret->setData(ROBOT::OBJ_KEY_COMPONENT_TYPE, QVariant(type));
		if(isMoveable)	ret->setFlag(QGraphicsItem::ItemIsMovable, true);
		qDebug() << __FUNCTION__ << "create new component" << type;
	}
	return ret;

}

QString ComponentFactory::getComponentNameByType(COM_TYPE type)
{
	return "";
}
