#pragma once
#include <QGraphicsItem>
#include <QGraphicsSvgItem>
#include <QSvgRenderer>
#include <QDebug>
#include <QGraphicsLayoutItem>

#include "../../../const/RobotConst.h"
#include "../../../util/RobotUtil.h"
#include "TextItem.h"

class InputItem : public QGraphicsSvgItem, public QGraphicsLayoutItem
{
public:
	Q_OBJECT
private:
	QGraphicsSvgItem *m_svgItem = nullptr;
	TextItem *m_input = nullptr;
	QSvgRenderer *m_pRenderer = nullptr;
	QString m_strokeColor;
	void updateWidth();
	QSizeF m_lastSize = QSizeF();
public:
	InputItem(QString defalutText, QString strokeColor, QGraphicsItem *parent);
	~InputItem();
	//��ȡ������ı�
	QString getText();
	//�����ı�
	void setText(QString text);
//QGraphicsLayoutItem �̳���Ҫ
protected:
	virtual QSizeF sizeHint(Qt::SizeHint which, const QSizeF & constraint = QSizeF()) const;
	virtual void setGeometry(const QRectF & rect);
signals:
	void textContentsChanged(QSizeF changeSize);
public slots:
	void contentsChanged();
};

