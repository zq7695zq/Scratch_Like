#include "ComponentNorm.h"

ComponentNorm::ComponentNorm(QPointF startPos, bool isVirtual = false, QString color = ROBOT::COLOR_BLUE, QString colorStroke = ROBOT::COLOR_BLUE_STROKE, QString labelText = "错误", QGraphicsItem *parent = Q_NULLPTR) : Component(startPos, isVirtual, parent)
{
	//生成背景item
	this->m_background = new BackgroundItem(ROBOT::SVG_COM_BACKGROUND_NORM, QSizeF(0, 0), isVirtual ? ROBOT::COLOR_WHITE : color, isVirtual ? ROBOT::COLOR_WHITE : colorStroke, isVirtual ? 0.8 : 1, this);
	this->m_form = new QGraphicsWidget(this);
	this->m_form->setPos(0, 5);
	//生成名字标签item
	this->m_nameLabel = new LabelItem(labelText, this->m_form);
	//生成输入框item
	this->m_input = new InputItem("", colorStroke, this->m_form);
	this->m_background->setSize(this->m_nameLabel->boundingRect().size() + this->m_input->boundingRect().size(), true);
	//把名字标签和输入框放入LinerLayout中，以线性布局
	this->m_layout->addItem(this->m_nameLabel);
	this->m_layout->addItem(this->m_input);
	//生效布局
	this->m_form->setLayout(this->m_layout);
	//控件之间间隔的宽度
	this->m_layout->setSpacing(0);
	this->adjustSize();
	//如果是虚拟的 就隐藏起来，只显示个外形
	if (isVirtual)
	{
		this->m_nameLabel->hide();
		this->m_input->hide();
	}
	//连接插槽，为了实现内容长度改变，背景框长度也改变
	connect(this->m_input, SIGNAL(textContentsChanged(QSizeF)), this->m_background, SLOT(contentsChanged(QSizeF)));
}
