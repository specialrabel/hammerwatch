#pragma once
#include "stdafx.h"
#include "singletonBase.h"

class D2Dmanager : public singletonBase<D2Dmanager>
{
public:

	ID2D1Factory* pD2DFactory;
	ID2D1HwndRenderTarget* pRenderTarget;
	IDWriteFactory* pWriteFactory;				// ���忡�� �Ʒ��� �����ϴ�.
	IDWriteTextFormat* pDefaultTextFormat;		//�⺻ �ؽ�Ʈ ����
	IDWriteTextFormat* pCustomTextFormat;		//Ŀ���� �ؽ�Ʈ ����
	ID2D1SolidColorBrush* defaultBrush;			//�⺻ ������ �귯��

	ID2D1BitmapRenderTarget* RenderTarget;
	ID2D1Bitmap* bitmap;

	D2Dmanager();
	~D2Dmanager();

	HRESULT Init();
	void release();
	void Update();
	void Render();
	void BeginDraw();
	void EndDraw();

	ID2D1SolidColorBrush* CreateBrush(COLORREF rgb, float opacity = 1.0f);

	// �簢�� ���� �Լ�
	void Rectangle(D2D1_RECT_F rect);
	void Rectangle(ID2D1SolidColorBrush* brush, D2D1_RECT_F rect);
	void Rectangle(ID2D1SolidColorBrush* brush, ID2D1SolidColorBrush* fillbrush, D2D1_RECT_F rect);

	// �簢�� ����� �Լ�
	D2D1_RECT_F RectMake(float startX, float startY, float endX, float endY);
	D2D1_RECT_F RectMakeCenter(float startX, float startY, float width, float height);

	void ElipseMakeCenter(ID2D1SolidColorBrush* brush, float startX, float startY, float endX, float endY, float strokeWidth = 1.0f);

	//����� ���ڿ�, ���ڿ��� �׸� Rect�� Left, Top, Right, Bottom, �׸� �귯��
	void TEXTOUT(ID2D1SolidColorBrush* brush, LPCWSTR string, float startX, float startY, float endX, float endY);
	//����� ���ڿ�, ���ڿ��� �׸� Rect�� Left, Top, Right, Bottom, �׸� �귯��, ��Ʈ��, ��Ʈ ũ��
	void DrawLine(ID2D1SolidColorBrush* brush, float startX, float startY, float endX, float endY, float strokeWidth = 1.0f);
	void DrawTextD2D(ID2D1SolidColorBrush* brush, LPCWSTR fontName, float fontSize, LPCWSTR string, float startX, float startY, float endX, float endY);
	//���ڿ� ����� ���� ����
	void DrawTextD2DCenter(ID2D1SolidColorBrush* brush, LPCWSTR fontName, float fontSize, LPCWSTR string, float startX, float startY, float endX, float endY);
	//���ڿ� ������ ���� ����
	void DrawTextD2DRight(ID2D1SolidColorBrush* brush, LPCWSTR fontName, float fontSize, LPCWSTR string, float startX, float startY, float endX, float endY);


};

