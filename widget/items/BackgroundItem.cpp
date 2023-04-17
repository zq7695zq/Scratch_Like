#include "BackgroundItem.h"

BackgroundItem::BackgroundItem(QString svg, QSizeF defaultSize, QString colorHex, QString strokeColorHex, float opacity, QGraphicsItem *parent = Q_NULLPTR) : QGraphicsSvgItem(parent)
{
	this->m_svg = svg;
	this->m_colorHex = colorHex;
	this->m_strokeColorHex = strokeColorHex;
	this->m_opacity = QString::number(opacity);
	this->setSize(defaultSize, true);
}

BackgroundItem::~BackgroundItem()
{
	delete this->m_pRenderer;
}

void BackgroundItem::contentsChanged(QSizeF changeSize)
{
	//qDebug() << "BackgroundItem::contentsChanged";
	this->updateSize(changeSize);
}

void BackgroundItem::updateSize(QSizeF changeSize)
{
	//更新渲染器，把之前的销毁
	if (this->m_pRenderer != nullptr)
	{
		this->m_pRenderer->destroyed();
		delete this->m_pRenderer;
	}
	//延长/缩短高度/宽度
	this->m_rect.setHeight(this->m_rect.height() + changeSize.height());
	this->m_rect.setWidth(this->m_rect.width() + changeSize.width());
	//更新尺寸
	this->setSize(this->m_rect.size(), false);
}

void BackgroundItem::setSize(QSizeF size, bool reset) 
{
	//设置输入框背景SVG样式
	this->m_pRenderer = new QSvgRenderer();
	//占的高度跟实际高度有20px的差值
	if(reset)
		size.setHeight(size.height() - 10);
	//限制尺寸
	size.setWidth(size.width() > 150 ? size.width() : 150);
	size.setHeight(size.height() > 30 ? size.height() : 30);
	//使用渲染器 渲染svg图片
	QByteArray svg = RobotUtil::svgFormat(this->m_svg, size.width(), size.height(), this->m_colorHex, this->m_opacity, this->m_strokeColorHex);
	this->m_pRenderer->load(svg);
	//qDebug() << __FUNCTION__ << " BackGroundItem SVG: " << svg;
	this->setSharedRenderer(this->m_pRenderer);
	//如果是重置/初始化的情况，保存原始尺寸
	if (reset) this->m_rect = QRectF(QPointF(0,0), size);
}

void BackgroundItem::setRealSize(QSizeF size) 
{
	//更新渲染器，把之前的销毁
	if (this->m_pRenderer != nullptr)
	{
		this->m_pRenderer->destroyed();
		delete this->m_pRenderer;
	}
	this->m_rect.setSize(size);
	//更新尺寸
	this->setSize(this->m_rect.size(), false);
}

void BackgroundItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	//this->setFocus();
	QGraphicsSvgItem::mousePressEvent(event);
}
