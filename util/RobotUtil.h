#pragma once
#include <QByteArray>
#include <QString>
#include <QPointF>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <QScrollBar>
#include <qdebug.h>
#include <QTime>

#include "../const/RobotConst.h"
#include "../enum/ComponentType.h"
#include "../enum/ComponentCategory.h"
#pragma execution_character_set("utf-8")

class RobotUtil
{
public:
	RobotUtil();
	~RobotUtil();

	static QByteArray svgFormat(QString svg, int format) 
	{
		return svg.arg(QString::number(format)).toUtf8();
	}

	static QByteArray svgFormat(QString svg, int format1, QString format2)
	{
		return svg.arg(QString::number(format1), format2).toUtf8();
	}

	static QByteArray svgFormat(QString svg, int format1, int format2)
	{
		return svg.arg(QString::number(format1), QString::number(format2)).toUtf8();
	}

	static QByteArray svgFormat(QString svg, int format1, QString format2, QString format3)
	{
		return svg.arg(QString::number(format1), format2, format3).toUtf8();
	}

	static QByteArray svgFormat(QString svg, int format1, int format2, QString format3, QString format4)
	{
		return svg.arg(QString::number(format1), QString::number(format2), format3, format4).toUtf8();
	}

	static QByteArray svgFormat(QString svg, int format1, int format2, QString format3, QString format4, QString format5)
	{
		return svg.arg(QString::number(format1), QString::number(format2), format3, format4, format5).toUtf8();
	}

	inline static QString getPosString(QPointF pos) 
	{
		return QString::number(pos.x()) + "," + QString::number(pos.y());
	}

	inline static void setItemName(QGraphicsItem *item, QString name)
	{
		return item->setData(ROBOT::OBJ_KEY_COMPONENT_NAME, name);
	}

	inline static QString getItemName(QGraphicsItem *item) 
	{
		return item->data(ROBOT::OBJ_KEY_COMPONENT_NAME).toString();
	}

	static void scaleView(QPointF cursorPoint, int wheelDeltaValue, QGraphicsView * view)
	{
		// 获取当前鼠标相对于scene的位置;
		QPointF scenePos = view->mapToScene(QPoint(cursorPoint.x(), cursorPoint.y()));

		// 获取view的宽高;
		qreal viewWidth = view->viewport()->width();
		qreal viewHeight = view->viewport()->height();

		QPointF viewCenter = view->mapToScene(viewWidth/2, viewHeight/2);

		// 获取当前鼠标位置相当于view大小的横纵比例;
		qreal hScale = cursorPoint.x() / viewWidth;
		qreal vScale = cursorPoint.y() / viewHeight;

		// 当前放缩倍数;
		qreal scaleFactor = view->matrix().m11();
		if ((scaleFactor < ROBOT::SCALE_FACTOR_MIN && wheelDeltaValue < 0)|| (scaleFactor > ROBOT::SCALE_FACTOR_MAX && wheelDeltaValue > 0))return;
		// 向上滚动，放大;
		if (wheelDeltaValue > 0)
		{
			view->scale(1.2, 1.2);
		}
		// 向下滚动，缩小;
		else
		{
			view->scale(1.0 / 1.2, 1.0 / 1.2);
		}
		// 将scene坐标转换为放大缩小后的坐标;
		QPointF viewPoint = view->matrix().map(scenePos);
		// 通过滚动条控制view放大缩小后的展示scene的位置;
		view->horizontalScrollBar()->setValue(int(viewPoint.x() - viewWidth * hScale));
		view->verticalScrollBar()->setValue(int(viewPoint.y() - viewHeight * vScale));
	}

	inline static bool isComponent(QGraphicsItem * item) { return item && item->data(ROBOT::OBJ_KEY_COMPONENT_TYPE).isValid();  }


	inline static QString getCategoryName(COM_CATEGORY type)
	{
		switch (type)
		{
		case COM_CATEGORY_MOVE:
			return "运动";
		case COM_CATEGORY_FUNCTION:
			return "功能";
		case COM_CATEGORY_LED:
			return "LED";
		case COM_CATEGORY_OPERATION:
			return "操作";
		case COM_CATEGORY_VARIBALE:
			return "变量";
		case COM_CATEGORY_CYCLE:
			return "循环";
		case COM_CATEGORY_SENSOR:
			return "传感器";
		default:
			return "未知";
			break;
		}
	}
	inline static COM_CATEGORY getCategoryByType(COM_TYPE type)
	{
		for (int i = 0; i < COM_CATEGORY_END; i++)
		{
			for (int j = 0; COM_CATEGORY_TO_COM_TYPE[i][j] != COM_TYPE_END; j++)
				if (type == COM_CATEGORY_TO_COM_TYPE[i][j]) return (COM_CATEGORY)i;
		}
		return COM_CATEGORY_END;
	}
	inline static bool isInNest(QGraphicsItem * item) { return item->data(ROBOT::OBJ_KEY_COMPONENT_INNEST).isValid() && item->data(ROBOT::OBJ_KEY_COMPONENT_INNEST).toBool(); }

	inline static unsigned int generateId() {
		QTime time = QTime::currentTime();
		qsrand(time.msec()*qrand()*qrand()*qrand()*qrand()*qrand()*qrand()*qrand()*qrand()*qrand());
		return qrand() % ROBOT::DEFALUT_MAX_ID;
	}

	inline static bool isNestCategory(COM_CATEGORY type) { return type == COM_CATEGORY_CYCLE || type == COM_CATEGORY_SENSOR; }
};
