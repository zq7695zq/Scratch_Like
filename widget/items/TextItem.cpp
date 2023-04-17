#include "TextItem.h"
#include <QFontDatabase>

TextItem::TextItem(QString text, QGraphicsItem *parent = Q_NULLPTR) : QGraphicsTextItem(parent)
{
	if (text.length() < 1)
		setPlainText(QString(text + " ").left(1));
	setPos(5, 6);
	//设置可编辑
	setTextInteractionFlags(Qt::TextEditable);
	setFlag(QGraphicsItem::ItemAcceptsInputMethod, false);
	connect(this->document(), &QTextDocument::contentsChanged, this, &TextItem::contentsChanged);
	QColor color;
	color.setRgb(164, 171, 197);
	setDefaultTextColor(color);
	QFont font;
	font.setPixelSize(16);
	font.setWeight(80);
	font.setLetterSpacing(QFont::AbsoluteSpacing, 0.1);
	font.setFamily(QString::fromUtf8("Helvetica"));
	setFont(font);

}

TextItem::~TextItem()
{

}

void TextItem::contentsChanged() 
{
	//qDebug() << "contentsChanged";
	if (toPlainText().length() < 1) 
	{
		setPlainText(QString(toPlainText() + " ").left(1));
	}
	emit textContentsChanged();
}

void TextItem::keyPressEvent(QKeyEvent *event) 
{
	//过滤字符，仅允许数字输入
	bool succ;
	event->text().toDouble(&succ);
	qDebug() << __FUNCTION__ << event->key();
	if (succ || event->key() == Qt::Key_Backspace || event->key() == Qt::Key_Period)
		QGraphicsTextItem::keyPressEvent(event);
}

void TextItem::mousePressEvent(QGraphicsSceneMouseEvent *event) 
{
	//this->setFocus();
	QGraphicsTextItem::mousePressEvent(event);
}