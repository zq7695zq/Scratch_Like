#pragma once
#include <QGraphicsView.h>
#include <QMouseEvent>
#include <QGraphicsItem>
#include <QDebug>

#include "../../const/RobotConst.h"

#include "../../component/ComponentFactory.h"

class ComponentView :
	public QGraphicsView
{
public:
	ComponentView(QGraphicsScene *scene);
	~ComponentView();
};

