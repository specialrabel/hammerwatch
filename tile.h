#pragma once
#include "gameNode.h"

#define TILESIZE 32

#define TILEX 200	//가로 타일 갯수
#define TILEY 100	//세로 타일 갯수

class tile : public gameNode
{
private:
	int _idX;
	int _idY;

	POINT _center;
	RECT _rc;

	D2D1_RECT_F rc;

	//F = G + H 
	//F == 총 거리 비용 (TotalCost)
	//G == 시작점으로부터 현재 노드까지 경로비용(CostFromStart)
	//H == 현재노드로부터 도착점까지 경로비용(CostToGoal)

	float _totalCost;
	float _costFromStart;
	float _costToGoal;

	bool _isOpen;//갈수있는 타일인지 유무

	tile* _parentNode; //제일 상위 타일 (계속 갱신되는 타일)

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

	//============ 편리를 위한 접근자 & 설정자 ===============
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

