#pragma once
class npcNode
{


public:
	virtual HRESULT init();			//�ʱ�ȭ �Լ�
	virtual void release();			//�޸� ���� �Լ�
	virtual void update();			//���� �Լ�
	virtual void render();			//�׸��� �Լ�
	virtual void renderInteraction();		//��ȣ�ۿ�� ������

	virtual bool getInteraction();
	virtual void setInteraction(bool b);
	virtual int getNpcLevel();
	virtual void setChat(bool b);

};

