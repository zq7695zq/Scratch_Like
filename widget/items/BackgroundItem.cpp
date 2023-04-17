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
	//������Ⱦ������֮ǰ������
	if (this->m_pRenderer != nullptr)
	{
		this->m_pRenderer->destroyed();
		delete this->m_pRenderer;
	}
	//�ӳ�/���̸߶�/���
	this->m_rect.setHeight(this->m_rect.height() + changeSize.height());
	this->m_rect.setWidth(this->m_rect.width() + changeSize.width());
	//���³ߴ�
	this->setSize(this->m_rect.size(), false);
}

void BackgroundItem::setSize(QSizeF size, bool reset) 
{
	//��������򱳾�SVG��ʽ
	this->m_pRenderer = new QSvgRenderer();
	//ռ�ĸ߶ȸ�ʵ�ʸ߶���20px�Ĳ�ֵ
	if(reset)
		size.setHeight(size.height() - 10);
	//���Ƴߴ�
	size.setWidth(size.width() > 150 ? size.width() : 150);
	size.setHeight(size.height() > 30 ? size.height() : 30);
	//ʹ����Ⱦ�� ��ȾsvgͼƬ
	QByteArray svg = RobotUtil::svgFormat(this->m_svg, size.width(), size.height(), this->m_colorHex, this->m_opacity, this->m_strokeColorHex);
	this->m_pRenderer->load(svg);
	//qDebug() << __FUNCTION__ << " BackGroundItem SVG: " << svg;
	this->setSharedRenderer(this->m_pRenderer);
	//���������/��ʼ�������������ԭʼ�ߴ�
	if (reset) this->m_rect = QRectF(QPointF(0,0), size);
}

void BackgroundItem::setRealSize(QSizeF size) 
{
	//������Ⱦ������֮ǰ������
	if (this->m_pRenderer != nullptr)
	{
		this->m_pRenderer->destroyed();
		delete this->m_pRenderer;
	}
	this->m_rect.setSize(size);
	//���³ߴ�
	this->setSize(this->m_rect.size(), false);
}

void BackgroundItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	//this->setFocus();
	QGraphicsSvgItem::mousePressEvent(event);
}
