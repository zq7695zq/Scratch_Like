#pragma once
#include <QGraphicsScene.h>
#include <QGraphicsSvgItem.h>

#include "../../component/ComponentFactory.h"
#include "../../enum/ComponentCategory.h"
#include "../../enum/ComponentType.h"
#include "../../util/RobotUtil.h"

class ComponentScene: public QGraphicsScene
{
public:
	ComponentScene();
	~ComponentScene();
private:
	ComponentFactory * m_pComponentFactory = ComponentFactory::getInstance();;
};

