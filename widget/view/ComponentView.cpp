#include "ComponentView.h"

ComponentView::ComponentView(QGraphicsScene *scene) : QGraphicsView(scene)
{
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//����ˮƽ��
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//��������
	setAlignment(Qt::AlignLeft | Qt::AlignTop);
}

ComponentView::~ComponentView()
{
}