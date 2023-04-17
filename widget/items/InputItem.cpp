#include "InputItem.h"

InputItem::InputItem(QString defalutText, QString strokeColor, QGraphicsItem *parent = Q_NULLPTR) : QGraphicsSvgItem(parent)
{
	//输入框
	this->m_input = new TextItem(defalutText, this);
	this->m_strokeColor = strokeColor;
	this->updateWidth();
	this->m_lastSize = this->boundingRect().size();
	this->connect(this->m_input, &TextItem::textContentsChanged, this, &InputItem::contentsChanged);
}

InputItem::~InputItem()
{

}

QString InputItem::getText() 
{
	return this->m_input->toPlainText().replace(" ", "");
}

void InputItem::setText(QString text)
{
	this->m_input->setPlainText(text);
}

void InputItem::setGeometry(const QRectF &rect)
{
	setPos(rect.topLeft());
}

QSizeF InputItem::sizeHint(Qt::SizeHint which, const QSizeF &constraint)const
{
	return this->boundingRect().size();
}

void InputItem::contentsChanged()
{
	qDebug() << "contentsChanged" << this->boundingRect().size();
	this->updateWidth();
	emit textContentsChanged(this->boundingRect().size() - this->m_lastSize);
	this->m_lastSize = this->boundingRect().size();
}

void InputItem::updateWidth() 
{
	if (this->m_pRenderer != nullptr) 
	{
		this->m_pRenderer->destroyed();
		delete this->m_pRenderer;
	}
	//设置输入框背景SVG样式
	this->m_pRenderer = new QSvgRenderer();
	this->m_pRenderer->load(RobotUtil::svgFormat(ROBOT::SVG_INPUT, this->m_input->boundingRect().width(), this->m_strokeColor));
	this->setSharedRenderer(this->m_pRenderer);
}
