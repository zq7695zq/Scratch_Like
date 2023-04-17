#pragma once
#include <QGraphicsScene.h>
#include <QGraphicsSceneDragDropEvent>
#include <QPainter>

#include "../../component/ComponentFactory.h"
#include "../../const/RobotConst.h"

class ActionScene :
	public QGraphicsScene
{
public:
	ActionScene();
	~ActionScene();
private:
	ComponentFactory * m_pComponentFactory = nullptr;
	QRectF m_rect;
protected:
	void mousePressEvent(QGraphicsSceneMouseEvent *event) override;        //µ¥»÷
	void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;      //ÊÍ·Å
	void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;         //ÒÆ¶¯
};

