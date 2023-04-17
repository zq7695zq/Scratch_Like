#include "ComponentNorm.h"

ComponentNorm::ComponentNorm(QPointF startPos, bool isVirtual = false, QString color = ROBOT::COLOR_BLUE, QString colorStroke = ROBOT::COLOR_BLUE_STROKE, QString labelText = "����", QGraphicsItem *parent = Q_NULLPTR) : Component(startPos, isVirtual, parent)
{
	//���ɱ���item
	this->m_background = new BackgroundItem(ROBOT::SVG_COM_BACKGROUND_NORM, QSizeF(0, 0), isVirtual ? ROBOT::COLOR_WHITE : color, isVirtual ? ROBOT::COLOR_WHITE : colorStroke, isVirtual ? 0.8 : 1, this);
	this->m_form = new QGraphicsWidget(this);
	this->m_form->setPos(0, 5);
	//�������ֱ�ǩitem
	this->m_nameLabel = new LabelItem(labelText, this->m_form);
	//���������item
	this->m_input = new InputItem("", colorStroke, this->m_form);
	this->m_background->setSize(this->m_nameLabel->boundingRect().size() + this->m_input->boundingRect().size(), true);
	//�����ֱ�ǩ����������LinerLayout�У������Բ���
	this->m_layout->addItem(this->m_nameLabel);
	this->m_layout->addItem(this->m_input);
	//��Ч����
	this->m_form->setLayout(this->m_layout);
	//�ؼ�֮�����Ŀ��
	this->m_layout->setSpacing(0);
	this->adjustSize();
	//���������� ������������ֻ��ʾ������
	if (isVirtual)
	{
		this->m_nameLabel->hide();
		this->m_input->hide();
	}
	//���Ӳ�ۣ�Ϊ��ʵ�����ݳ��ȸı䣬�����򳤶�Ҳ�ı�
	connect(this->m_input, SIGNAL(textContentsChanged(QSizeF)), this->m_background, SLOT(contentsChanged(QSizeF)));
}
