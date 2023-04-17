#include "ComponentView.h"

ComponentView::ComponentView(QGraphicsScene *scene) : QGraphicsView(scene)
{
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//隐藏水平条
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//隐藏竖条
	setAlignment(Qt::AlignLeft | Qt::AlignTop);
}

ComponentView::~ComponentView()
{
}