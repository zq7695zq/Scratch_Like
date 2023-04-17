#include "ActionScene.h"

ActionScene::ActionScene()
{
	QPointF startPos = QPointF(0, 0);
	this->m_pComponentFactory = ComponentFactory::getInstance();
	Component * com = this->m_pComponentFactory->create(COM_TYPE_FORWARD_DISTENCE, startPos, false, true);
	
	startPos = QPointF(0, 50);
	RobotUtil::setItemName(com, "COM_1");
	addItem(com);
	Component * com2 = this->m_pComponentFactory->create(COM_TYPE_FORWARD_DISTENCE, startPos, false, true, com);
	RobotUtil::setItemName(com2, "COM_2");
	Component * com3 = this->m_pComponentFactory->create(COM_TYPE_FORWARD_DISTENCE, startPos, false, true, com2);
	RobotUtil::setItemName(com3, "COM_3");

	//±³¾°ÑÕÉ«
	//this->setBackgroundBrush(QColor::fromRgb(32, 32, 32));
	m_rect = QRectF(-4096, -2440, 8192, 4680);
	setSceneRect(m_rect);

	QPixmap pixmap(8192, 4680);
	QPen pen;
	QPainter painter(&pixmap);
	pixmap.fill(QColor::fromRgb(32, 32, 32));
	pen.setColor(QColor(131, 131, 131));
	pen.setWidth(1);
	painter.setPen(pen);
	for (int x = m_rect.x(); x < m_rect.width(); x += 30)
		for (int y = m_rect.y(); y < m_rect.height(); y += 30)
			painter.drawEllipse(QPointF(x, y), 1, 1);
	this->setBackgroundBrush(pixmap);
}

ActionScene::~ActionScene()
{
}

void ActionScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	//qDebug() << __FUNCTION__;
	QGraphicsScene::mousePressEvent(event);
}

void ActionScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
	//qDebug() << __FUNCTION__;
	QGraphicsScene::mouseReleaseEvent(event);
}

void ActionScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
	//qDebug() << __FUNCTION__;
	QGraphicsScene::mouseMoveEvent(event);
}
