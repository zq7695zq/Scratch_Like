#include "ComponentScene.h"

ComponentScene::ComponentScene()
{
	//ComponentForwardByDistance *com = new ComponentForwardByDistance(startPos);

	int pos_y = 0;
	for (COM_CATEGORY cat = COM_CATEGORY_MOVE; cat < COM_CATEGORY_END; cat = COM_CATEGORY(cat + 1))
	{
		QGraphicsTextItem *pCategotyText = new QGraphicsTextItem(RobotUtil::getCategoryName(cat));
		pCategotyText->setPos(0, pos_y);
		//设置样式
		QColor color;
		color.setRgb(178, 174, 197);
		pCategotyText->setDefaultTextColor(color);
		QFont font;
		font.setPixelSize(14);
		font.setFamily("\"Helvetica Neue\", Helvetica, sans-serif");
		font.setBold(true);
		pCategotyText->setFont(font);
		//设置样式

		pos_y += 20;
		this->addItem(pCategotyText);
		for (int j = 0; COM_CATEGORY_TO_COM_TYPE[cat][j] != COM_TYPE_END; j++)
		{
			Component * newCom = this->m_pComponentFactory->create((COM_TYPE)COM_CATEGORY_TO_COM_TYPE[cat][j], QPointF(0, pos_y));
			if (newCom == nullptr)continue;
			addItem(newCom);
			pos_y += newCom->childrenBoundingRect().height() + 10;
		}
	}
	//背景颜色
	this->setBackgroundBrush(QColor::fromRgb(205, 205, 205));
}

ComponentScene::~ComponentScene()
{
}