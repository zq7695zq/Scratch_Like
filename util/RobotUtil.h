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
		// ��ȡ��ǰ��������scene��λ��;
		QPointF scenePos = view->mapToScene(QPoint(cursorPoint.x(), cursorPoint.y()));

		// ��ȡview�Ŀ��;
		qreal viewWidth = view->viewport()->width();
		qreal viewHeight = view->viewport()->height();

		QPointF viewCenter = view->mapToScene(viewWidth/2, viewHeight/2);

		// ��ȡ��ǰ���λ���൱��view��С�ĺ��ݱ���;
		qreal hScale = cursorPoint.x() / viewWidth;
		qreal vScale = cursorPoint.y() / viewHeight;

		// ��ǰ��������;
		qreal scaleFactor = view->matrix().m11();
		if ((scaleFactor < ROBOT::SCALE_FACTOR_MIN && wheelDeltaValue < 0)|| (scaleFactor > ROBOT::SCALE_FACTOR_MAX && wheelDeltaValue > 0))return;
		// ���Ϲ������Ŵ�;
		if (wheelDeltaValue > 0)
		{
			view->scale(1.2, 1.2);
		}
		// ���¹�������С;
		else
		{
			view->scale(1.0 / 1.2, 1.0 / 1.2);
		}
		// ��scene����ת��Ϊ�Ŵ���С�������;
		QPointF viewPoint = view->matrix().map(scenePos);
		// ͨ������������view�Ŵ���С���չʾscene��λ��;
		view->horizontalScrollBar()->setValue(int(viewPoint.x() - viewWidth * hScale));
		view->verticalScrollBar()->setValue(int(viewPoint.y() - viewHeight * vScale));
	}

	inline static bool isComponent(QGraphicsItem * item) { return item && item->data(ROBOT::OBJ_KEY_COMPONENT_TYPE).isValid();  }


	inline static QString getCategoryName(COM_CATEGORY type)
	{
		switch (type)
		{
		case COM_CATEGORY_MOVE:
			return "�˶�";
		case COM_CATEGORY_FUNCTION:
			return "����";
		case COM_CATEGORY_LED:
			return "LED";
		case COM_CATEGORY_OPERATION:
			return "����";
		case COM_CATEGORY_VARIBALE:
			return "����";
		case COM_CATEGORY_CYCLE:
			return "ѭ��";
		case COM_CATEGORY_SENSOR:
			return "������";
		default:
			return "δ֪";
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
