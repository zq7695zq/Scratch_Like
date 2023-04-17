#pragma once
#include "Component.h"
#include "../widget/items/InputItem.h"
#include "../widget/items/LabelItem.h"
#pragma execution_character_set("utf-8")

class ComponentNorm :
	public Component
{
public:
	ComponentNorm(QPointF startPos, bool isVirtual, QString color, QString colorStroke, QString labelText, QGraphicsItem *parent);
	~ComponentNorm()
	{
		disconnect(this->m_input, SIGNAL(textContentsChanged(QSizeF)), this->m_background, SLOT(contentsChanged(QSizeF)));
		m_input->setParent(nullptr);
		m_nameLabel->setParent(nullptr);
		m_form->setLayout(nullptr);

		delete m_input;
		delete m_nameLabel;
		delete m_backGroundSvg;
	}
	//设置距离
	void setDistance(double distance) { this->m_input->setText(QString::number(distance)); }
	//获取类型
	inline COM_TYPE getType()
	{
		return COM_TYPE_FORWARD_DISTENCE;
	}
	//获取Data
	int getData() 
	{
		return this->m_input->getText().replace(" ", "").toDouble();
	}
private:
	InputItem *m_input = nullptr;
	LabelItem *m_nameLabel = nullptr;
	QString *m_backGroundSvg = new QString(ROBOT::SVG_COM_BACKGROUND_NORM);
	QGraphicsLinearLayout *m_layout = new QGraphicsLinearLayout();
};

