#pragma once
#include "gameNode.h"


class selectScene : public gameNode
{
private:


public:
	selectScene();
	~selectScene();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	//�Լ������Ͱ� ����� ���� ���������̶� static �ٿ������
	static void cbSceneChange();
};

