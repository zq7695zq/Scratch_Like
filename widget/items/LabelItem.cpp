#include "LabelItem.h"

LabelItem::LabelItem(QString text, QGraphicsItem *parent = Q_NULLPTR) : QGraphicsTextItem(parent)
{
	setPlainText(text);
	QColor color;
	color.setRgb(255, 255, 255);
	setDefaultTextColor(color);
	QFont font;
	font.setPixelSize(16);
	font.setWeight(80);
	font.setLetterSpacing(QFont::AbsoluteSpacing, 0.1);
	font.setFamily(QString::fromUtf8("Helvetica"));
	setFont(font);
}

LabelItem::~LabelItem()
{
}

void LabelItem::setGeometry(const QRectF &rect)
{
	setPos(rect.topLeft() + QPointF(0, 5));
}

QSizeF LabelItem::sizeHint(Qt::SizeHint which, const QSizeF &constraint)const
{
	return this->boundingRect().size();
}