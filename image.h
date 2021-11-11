#pragma once
#include "animation.h"

class image
{
public:
	//�̹����� �ҷ��ü� �ִ� ����
	enum IMAGE_LOAD_KIND
	{
		LOAD_RESOURCE,		//���ҽ� ���Ϸκ���
		LOAD_FILE,			//�̹��� ���Ϸκ���
		LOAD_EMPTY,			//�� ��Ʈ�� �̹����� �����߰ڴ�
		LOAD_END
	};

	typedef struct tagImageInfo
	{
		DWORD resID;	//���ҽ��� ���ؼ� �̹��� ó���Ҷ� �긦 ����
		IWICImagingFactory*		pWICImagingFactory;		//Windows Imaging Component�� ���� Factory �������̽�
		IWICFormatConverter*	pWICFormatConverter;	//Format Converter
		IWICBitmapDecoder*		pWICDecoder;			//Bitmap Decoder
		IWICBitmapFrameDecode*  pWICFrameDecoder;		//������ ������ ���ڵ��� Decoder �������̽�
		ID2D1Bitmap*			pBitmap;				//D2D�� ��Ʈ��
		IWICBitmap*				wBitmap;				//�ȼ�ó���� ��Ʈ��
		HDC hMemDC;
		HBITMAP hBit;
		HBITMAP hOBit;
		float x;			//�̹��� x��ǥ
		float y;			//�̹��� y��ǥ
		int width;			//�̹��� ��ü ����ũ��
		int height;			//�̹��� ��ü ����ũ��
		int currentFrameX;	//���� ������ ��ȣ(����)
		int currentFrameY;	//���� ������ ��ȣ(����)
		int maxFrameX;		//�ִ� ������ ��ȣ(����)
		int maxFrameY;		//�ִ� ������ ��ȣ(����)
		int frameWidth;		//1������ �� ����ũ��
		int frameHeight;	//1������ �� ����ũ��
		BYTE loadType;

		tagImageInfo()
		{
			resID		= 0;
			pWICImagingFactory = nullptr;
			pWICFormatConverter = nullptr;
			pWICDecoder = nullptr;
			pWICFrameDecoder = nullptr;
			pBitmap = nullptr;
			wBitmap = nullptr;
			hMemDC		= NULL;
			hBit		= NULL;
			hOBit		= NULL;
			x			= 0;
			y			= 0;
			width		= 0;
			height		= 0;
			currentFrameX = 0;
			currentFrameY = 0;
			maxFrameX = 0;
			maxFrameY = 0;
			frameWidth = 0;
			frameHeight = 0;
			loadType = LOAD_RESOURCE;
		}
	}IMAGE_INFO, *LPIMAGE_INFO;

private:
	LPIMAGE_INFO	_imageInfo;
	LPWSTR			_fileName;		//���� �̸�
	BOOL			_trans;			//Ư�� �ȼ����� �������� ����
	COLORREF		_transColor;	//������ �ȼ���

	BLENDFUNCTION	_blendFunc;		//���ĺ��� �Լ�
	LPIMAGE_INFO	_blendImage;	//���ĺ��� ���� �̹���

public:
	image();
	~image();


	// �Ϲ� �̹����� ���Ͽ��� ������ ��, ���ϸ�, ���� �ʺ�, ���� ����
	HRESULT D_Init(LPCWSTR pFileName, int width, int height);

	// ������ �̹����� ���Ͽ��� ������ ��, ���ϸ�, ���� �ʺ�, ���� ����, ���� ������ ��, ���� ������ ��
	HRESULT D_Init(LPCWSTR pFileName, int width, int height, int frameNumX, int frameNumY);

	void release();
	const HRESULT get_RGB(int x, int y);

	void rotation_start(float destX, float destY, float angle);
	void Framerotation_start(float destX, float destY, float angle);
	void rotation_end();
	D2D1_MATRIX_3X2_F rotation_matrix(float destX, float destY, float angle);
	D2D1_MATRIX_3X2_F Frame_rotation_matrix(float destX, float destY, float angle);

	void scale_start(float destX, float destY, float x, float y);
	void Frame_scale_start(float destX, float destY, float x, float y);
	void scale_end();
	D2D1_MATRIX_3X2_F scale_matrix(float destX, float destY, float x, float y);
	D2D1_MATRIX_3X2_F Frame_scale_matrix(float destX, float destY, float x, float y);

	//���� ũ�� ��� - �׷��� x��ǥ, y��ǥ, ����
	void render(float destX, float destY, float opacity = 1.0f);

	//���� ũ�⿡�� �������� �߶� �׸���(?) - �׷��� x��ǥ, y��ǥ, ����
	void renderUI(float destX, float destY, float sourX, float sourY, float tempX, float tempY, float opacity = 1.0f);

	//���� ũ��� �߶� �������� - �׷��� x��ǥ, y��ǥ -> ������ ���� left, top, ���� ũ��, ���� ũ��, ����
	void render(float destX, float destY, float sourX, float sourY,
		int sourWidth, int sourHeight, float opacity = 1.0f);

	//�簢�� ��ǥ -> �簢�� ��ǥ �׸���
	void render(float destX, float destY, float destWidth, float destHeight, float sourX, float sourY, float sourWidth, float sourHeight, float opacity = 1.0f);

	//���� ũ�� �����ӷ��� - �׷��� x, y ��ǥ, ���� ���� ������ �ε���, ���� ���� ������ �ε���, ����
	void FrameRender(float destX, float destY, int currentFrameX, int currentFrameY, float opacity = 1.0f);

	void aniRender(float destX, float destY, animation* ani, float opacity = 1.0f);

	//Ȥ�ó� ��Ÿ�� ���߿� ������ �ȼ����� �ٲ���Ѵٸ�
	void setTransColor(BOOL trans, COLORREF transColor);

	void loopRender(const D2D1_RECT_F drawArea, int offSetX, int offSetY);
	void loopRender(const D2D1_RECT_F drawArea, int offSetX, int offSetY, float opacity);
	//����ۿ� ���� ������
	inline HDC getMemDC() { return _imageInfo->hMemDC; }

	//===============================================
	// ## �̹��� ���� ������ ������ ##
	//=============================================

	inline void setX(float x) { _imageInfo->x = x; }
	inline float getX() { return _imageInfo->x; }

	inline void setY(float y) { _imageInfo->y = y; }
	inline float getY() { return _imageInfo->y; }

	inline void setCenter(float x, float y)
	{
		_imageInfo->x = x - (_imageInfo->width / 2);
		_imageInfo->y = y - (_imageInfo->height / 2);
	}

	inline float getCenterX()
	{
		return _imageInfo->maxFrameX <= 0 ?
			_imageInfo->x + (_imageInfo->width / 2) :
			_imageInfo->x + (_imageInfo->frameWidth / 2);
	}

	inline float getCenterY()
	{
		return _imageInfo->maxFrameY <= 0 ?
			_imageInfo->y + (_imageInfo->height / 2) :
			_imageInfo->y + (_imageInfo->frameHeight / 2);
	}

	inline int getWidth() { return _imageInfo->width; }
	inline int getHeight() { return _imageInfo->height; }

	inline void setFrameX(int frameX)
	{
		_imageInfo->currentFrameX = frameX;

		if (frameX > _imageInfo->maxFrameX)
		{
			_imageInfo->currentFrameX = _imageInfo->maxFrameX;
		}
	}

	inline void setFrameY(int frameY)
	{
		_imageInfo->currentFrameY = frameY;

		if (frameY > _imageInfo->maxFrameY)
		{
			_imageInfo->currentFrameY = _imageInfo->maxFrameY;
		}
	}


	inline int getMaxFrameX() { return _imageInfo->maxFrameX; }
	inline int getMaxFrameY() { return _imageInfo->maxFrameY; }

	inline int getFrameX() { return _imageInfo->currentFrameX; }
	inline int getFrameY() { return _imageInfo->currentFrameY; }

	inline int getFrameWidth() { return _imageInfo->frameWidth; }
	inline int getFrameHeight() { return _imageInfo->frameHeight; }
};

