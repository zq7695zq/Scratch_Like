#include "ComponentNest.h"

ComponentNest::ComponentNest(QPointF startPos, bool isVirtual = false, QString labelText = "����", QString color = ROBOT::COLOR_ORANGE, QString colorStroke = ROBOT::COLOR_ORANGE_STROKE, bool hasInput = true, QGraphicsItem *parent = Q_NULLPTR) : Component(startPos, isVirtual, parent)
{
	//���ɱ���item
	this->m_background = new BackgroundItem(ROBOT::SVG_COM_BACKGROUND_NEST, QSizeF(0, 0), isVirtual ? ROBOT::COLOR_WHITE : color, isVirtual ? ROBOT::COLOR_WHITE : colorStroke, isVirtual ? 0.8 : 1, this);
	//�������ֱ�ǩitem
	this->m_nameLabel = new LabelItem(labelText, this);
	//���������item
	this->m_input = new InputItem("", colorStroke, this);
	//qDebug() << this->m_nameLabel->boundingRect().size() + this->m_input->boundingRect().size();
	this->m_background->setSize(this->m_nameLabel->boundingRect().size() + this->m_input->boundingRect().size(), true);
	//�����ֱ�ǩ����������LinerLayout�У������Բ���
	this->m_layout->addItem(this->m_nameLabel);
	this->m_layout->addItem(this->m_input);
	//��Ч����
	this->setLayout(m_layout);
	//�ؼ�֮�����Ŀ��
	this->m_layout->setSpacing(0);
	this->adjustSize();
	//���������� ������������ֻ��ʾ������
	if (isVirtual)
	{
		this->m_nameLabel->hide();
		this->m_input->hide();
	}
	if (!hasInput) 
	{
		this->m_input->hide();
	}
	//���Ӳ�ۣ�Ϊ��ʵ�����ݳ��ȸı䣬�����򳤶�Ҳ�ı�
	connect(this->m_input, SIGNAL(textContentsChanged(QSizeF)), this->m_background, SLOT(contentsChanged(QSizeF)));
	this->m_background->updateSize(QSizeF(0, 0));
	this->m_isNest = true;
}

void ComponentNest::updateSize()
{
	this->getBackGroundItem()->setRealSize(QSizeF(this->getBackGroundItem()->getSize().width(), this->getChildsHeight()));
	Component * pChild = this->getChildOutOfNestItem();
	if (pChild)
	{
		QList<ComponentSlot> _slots = this->updateSlotsByComponent(pChild);
		pChild->setPos(_slots.at(2).getPos() - this->scenePos());
	}
}

void ComponentNest::insertItem(Component * pComponent, ComponentSlot slot) 
{
	Component::insertItem(pComponent, slot);
	//this->updateSize();
}
