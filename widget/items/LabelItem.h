#pragma once
#include <QGraphicsTextItem>
#include <QGraphicsItem>
#include <QGraphicsLayoutItem>
#include <QFont>

class LabelItem : public QGraphicsTextItem, public QGraphicsLayoutItem
{
public:
	LabelItem(QString text, QGraphicsItem *parent);
	~LabelItem();
//QGraphicsLayoutItem ¼Ì³ÐÐèÒª
protected:
	virtual QSizeF sizeHint(Qt::SizeHint which, const QSizeF & constraint = QSizeF()) const;
	virtual void setGeometry(const QRectF & rect);
};

