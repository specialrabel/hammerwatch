#include "stdafx.h"
#include "tile.h"

//¸â¹ö ÀÌ´Ï¼È¶óÀÌÁî
tile::tile()
	: _totalCost(0), _costFromStart(0),
	_costToGoal(0), _parentNode(NULL),
	_idX(0), _idY(0), _isOpen(true)
{
}

tile::~tile()
{

}

HRESULT tile::init(int idX, int idY, D2D1_RECT_F _rc)
{
	_color = RGB(250, 150, 0);

	//_brush = CreateSolidBrush(_color);

	//D2D
	//D2DMANAGER->pRenderTarget->CreateSolidColorBrush(ColorF(1.0f, 0.58f, 0, 1.0f), &_mybrush);

	//_pen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));

	_center = PointMake(idX * TILESIZE + (TILESIZE / 2),
		idY * TILESIZE + (TILESIZE / 2));

	_idX = idX;
	_idY = idY;

	//_rc = RectMakeCenter(_center.x, _center.y, TILEWIDTH, TILEHEIGHT);

	//D2D
	//rc = D2DMANAGER->RectMakeCenter(_center.x, _center.y, TILESIZE, TILESIZE);

	rc = _rc;

	return S_OK;
}

void tile::release()
{
	DeleteObject(_brush);
	DeleteObject(_pen);
}

void tile::update()
{

}

void tile::render()
{
	//SelectObject(getMemDC(), (HBRUSH)_brush);
	//D2D
	//D2DMANAGER->pRenderTarget->FillRectangle(rc, _mybrush);
	//D2DMANAGER->Rectangle(rc);

}
