#pragma once
#include <QTextOption>
#include <QTextDocument>
#include <QGraphicsTextItem>
#include <QGraphicsSvgItem>
#include <QSvgRenderer>
#include <QDebug>
#include <QKeyEvent>

class TextItem :
	public QGraphicsTextItem
{
public:
	Q_OBJECT
private:
	//QRectF m_forcedSize;
	QString m_lastText = "";
public:
	TextItem(QString text, QGraphicsItem *parent);
	~TextItem();
	void keyPressEvent(QKeyEvent *event);
	void mousePressEvent(QGraphicsSceneMouseEvent *event) override;        //µ¥»÷
signals:
	void textContentsChanged();
public slots:
	void contentsChanged();

};

