#pragma once
#include "gameNode.h"

#define TILESIZE 32

#define TILEX 200	//���� Ÿ�� ����
#define TILEY 100	//���� Ÿ�� ����

class tile : public gameNode
{
private:
	int _idX;
	int _idY;

	POINT _center;
	RECT _rc;

	D2D1_RECT_F rc;

	//F = G + H 
	//F == �� �Ÿ� ��� (TotalCost)
	//G == ���������κ��� ���� ������ ��κ��(CostFromStart)
	//H == ������κ��� ���������� ��κ��(CostToGoal)

	float _totalCost;
	float _costFromStart;
	float _costToGoal;

	bool _isOpen;//�����ִ� Ÿ������ ����

	tile* _parentNode; //���� ���� Ÿ�� (��� ���ŵǴ� Ÿ��)

	ID2D1SolidColorBrush* _mybrush;

	COLORREF	_color;
	HBRUSH		_brush;
	HPEN		_pen;

	string _attribute;

public:
	tile();
	~tile();

	HRESULT init(int idX, int idY, D2D1_RECT_F rc);
	void release();
	void update();
	void render();

	int getIdX() { return _idX; }
	int getIdY() { return _idY; }

	inline void setIdX(int val) { _idX = val; }
	inline void setIdY(int val) { _idY = val; }

	void setColor(COLORREF color)
	{
		DeleteObject(_mybrush);
		_color = color;

		float r = (float)GetRValue(_color) / 255;
		float g = (float)GetGValue(_color) / 255;
		float b = (float)GetBValue(_color) / 255;

		D2DMANAGER->pRenderTarget->CreateSolidColorBrush(ColorF(r,g,b, 1.0f), &_mybrush);
	}

	RECT getRect() { return _rc; }
	D2D1_RECT_F getRectangle() { return rc; }

	//============ ���� ���� ������ & ������ ===============
	void setCenter(POINT center) { _center = center; }
	POINT getCenter() { return _center; }

	void setAttribute(string str) { _attribute = str; }
	string getAttribute() { return _attribute; }

	void setTotalCost(float totalCost) { _totalCost = totalCost; }
	float getTotalCost() { return _totalCost; }

	void setCostFromStart(float costFromStart) { _costFromStart = costFromStart; }
	float getCostFromStart() { return _costFromStart; }

	void setCostToGoal(float costToGoal) { _costToGoal = costToGoal; }
	float getCostToGoal() { return _costToGoal; }

	void setParentNode(tile* t) { _parentNode = t; }
	tile* getParentNode() { return _parentNode; }

	void setIsOpen(bool isOpen) { _isOpen = isOpen; }
	bool getIsOpen() { return _isOpen; }
};

