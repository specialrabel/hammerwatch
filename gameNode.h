#pragma once
#include "image.h"

class gameNode
{
private:
	HDC _hdc;
	bool _managerInit;
	
public:
	gameNode();
	virtual ~gameNode();

	//HRESULT ���� ���� ��ȯ�����ε�
	//S_OK, E_FAIL, SUCCEDED
	virtual HRESULT init();			//�ʱ�ȭ �Լ�
	virtual HRESULT init(bool managerInit);
	virtual void release();			//�޸� ���� �Լ�
	virtual void update();			//���� �Լ�
	virtual void render();	//�׸��� �Լ�

	LRESULT MainProc(HWND, UINT, WPARAM, LPARAM);
};

