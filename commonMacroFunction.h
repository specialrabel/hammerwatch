#pragma once

//============================================
// ## 21.04.23 ## commonMacroFunction ##
//============================================

//Point
inline POINT PointMake(int x, int y)
{
	POINT pt = { x, y };

	return pt;
}

//          ���߱��Լ�(�׷���DC, ������ǥX, ������ǥY, ����ǥ X, ����ǥY)
inline void LineMake(HDC hdc, int x1, int y1, int x2, int y2)
{
	MoveToEx(hdc, x1, y1, NULL);
	LineTo(hdc, x2, y2);
}

//RECT
inline RECT RectMake(int x, int y, int width, int height)
{
	RECT rc = { x, y, x + width, y + height };

	return rc;
}

inline RECT RectMakeCenter(int x, int y, int width, int height)
{
	RECT rc = { x - (width / 2), y - (height / 2), x + (width / 2), y + (height/ 2) };

	return rc;
}


//�簢�� 
inline void Rectangle(HDC hdc, RECT& rc)
{
	Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
}

//x, y���� �������� �ϴ� �簢���� ������
inline void RectangleMake(HDC hdc, int x, int y, int width, int height)
{
	Rectangle(hdc, x, y, x + width, y + height);
}

//x, y ��ǥ�� �������� ũ�⸸ŭ�� �簢���� ������
inline void RectangleMakeCenter(HDC hdc, int x, int y, int width, int height)
{
	Rectangle(hdc, x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2));
}

//��
inline void Ellipse(HDC hdc, RECT& rc)
{
	Ellipse(hdc, rc.left, rc.top, rc.right, rc.bottom);
}
//x, y���� �������� �ϴ� ���� ������
inline void EllipseMake(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x, y, x + width, y + height);
}

//x, y ��ǥ�� �������� ũ�⸸ŭ�� ���� ������
inline void EllipseMakeCenter(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2));
}

inline bool INTERSECTION_RECT(D2D1_RECT_F& temp, D2D1_RECT_F& _rc, D2D1_RECT_F& _rc2)
{
	if (_rc.right > _rc2.left && _rc.left < _rc2.right &&
		_rc.top    < _rc2.bottom && _rc.bottom > _rc2.top)
	{
		//�»� �浹 _rc2�� ��
		if (_rc.top > _rc2.top && _rc.right > _rc2.right)
		{
			temp = D2D1::RectF(_rc.left, _rc.top, (_rc2.right - _rc.left), _rc2.bottom);
		}
		//���� �浹 -> _rc2�� �� �Ʒ�
		if (_rc.top <= _rc2.top && _rc.right > _rc2.right)
		{
			temp = D2D1::RectF(_rc.left, _rc2.top, _rc.left + (_rc2.right - _rc.left), _rc.bottom);
		}
		//��� �浹 
		if (_rc.top > _rc2.top && _rc.left < _rc2.left)
		{
			temp = D2D1::RectF(_rc2.left, _rc.top, _rc.right, _rc2.bottom);
		}
		//���� �浹 -> _rc2�� �� �Ʒ�
		if (_rc.top <= _rc2.top && _rc.left < _rc2.left)
		{
			temp = D2D1::RectF(_rc2.left, _rc2.top, _rc2.left + (_rc.right - _rc2.left), _rc.bottom);
		}

		return true;
	}
	else
		return false;

}

inline bool PTIN_RECT(D2D1_RECT_F* temp, POINT pt)
{
	if (temp->right > pt.x && temp->left < pt.x &&
		temp->top    < pt.y && temp->bottom > pt.y)
	{

		return true;
	}
	else
		return false;
}