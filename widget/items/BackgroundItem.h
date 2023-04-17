#pragma once
#include <QGraphicsSvgItem>
#include <QSvgRenderer>
#include <QString>
#include <QDebug>

#include "../../../const/RobotConst.h"
#include "../../../util/RobotUtil.h"

class BackgroundItem :
	public QGraphicsSvgItem
{
public:
	Q_OBJECT
public:
	BackgroundItem(QString svg, QSizeF defaultSize, QString colorHex, QString strokeColorHex, float opacity, QGraphicsItem *parent);
	~BackgroundItem();
	void setSize(QSizeF size, bool reset);
	inline QSizeF getSize() 
	{
		return this->m_rect.size();
	}
	void mousePressEvent(QGraphicsSceneMouseEvent *event) override;        //µ¥»÷

private:
	QSvgRenderer *m_pRenderer = nullptr;
	QString m_svg = "";
	QRectF m_rect;
	QRectF m_lastRect;
	QString m_colorHex;
	QString m_strokeColorHex;
	QString m_opacity;
public slots:
	void contentsChanged(QSizeF changeSize);
	void updateSize(QSizeF changeSize);
	void setRealSize(QSizeF size);
};

