#include "stdafx.h"
#include "image.h"

#pragma comment(lib, "msimg32.lib")

//��� �̴ϼȶ�����
image::image()
	: _imageInfo(NULL),
	_fileName(NULL),
	_trans(false),
	_transColor(RGB(0,0,0))
{
}


image::~image()
{
}

HRESULT image::D_Init(LPCWSTR pFileName, int width, int height)
{
	if (pFileName == NULL) return E_FAIL;

	// �̹��� ���� ����
	HRESULT hr = E_FAIL;
	_imageInfo = new IMAGE_INFO;
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->currentFrameX = 0;
	_imageInfo->currentFrameY = 0;
	_imageInfo->frameWidth = width;
	_imageInfo->frameHeight = height;

	// ���� ��� ����
	int len;
	len = lstrlenW(pFileName);
	_fileName = new WCHAR[len + 1];
	lstrcpyW(_fileName, pFileName);

	// WIC�� ����ϱ� ���� Factory ��ü ����
	hr = CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER,
		IID_PPV_ARGS(&_imageInfo->pWICImagingFactory));
	assert(hr == S_OK);

	// �̹����� �б� ����, "���ڴ�" ���� 
	hr = _imageInfo->pWICImagingFactory->CreateDecoderFromFilename(_fileName, NULL, GENERIC_READ, WICDecodeMetadataCacheOnDemand,
		&(_imageInfo->pWICDecoder));
	assert(hr == S_OK);

	// ù ��° �������� ����� �� �ִ� ��ü ����
	hr = _imageInfo->pWICDecoder->GetFrame(0, &_imageInfo->pWICFrameDecoder);
	assert(hr == S_OK);

	// ���� ������ ���� -> D2D �������� ��ȯ
	hr = _imageInfo->pWICImagingFactory->CreateFormatConverter(&_imageInfo->pWICFormatConverter);
	assert(hr == S_OK);

	// ��Ʈ������ ��ȯ
	hr = _imageInfo->pWICFormatConverter->Initialize(_imageInfo->pWICFrameDecoder, GUID_WICPixelFormat32bppPBGRA,
		WICBitmapDitherTypeNone, NULL, 0.0f, WICBitmapPaletteTypeCustom);

	// ��ȯ�� �̹��� ������ ����Ͽ� D2D�� ��Ʈ�� ����
	hr = D2DMANAGER->pRenderTarget->CreateBitmapFromWicBitmap(_imageInfo->pWICFormatConverter, NULL, &_imageInfo->pBitmap);

	
	return S_OK;
}

HRESULT image::D_Init(LPCWSTR pFileName, int width, int height, int frameNumX, int frameNumY)
{
	if (pFileName == NULL) return E_FAIL;

	// �̹��� ���� ����
	HRESULT hr = E_FAIL;
	_imageInfo = new IMAGE_INFO;
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->currentFrameX = 0;
	_imageInfo->currentFrameY = 0;
	_imageInfo->maxFrameX = frameNumX - 1;
	_imageInfo->maxFrameY = frameNumY - 1;
	_imageInfo->frameWidth = width / frameNumX;
	_imageInfo->frameHeight = height / frameNumY;

	// ���� ��� ����
	int len;
	len = lstrlenW(pFileName);
	_fileName = new WCHAR[len + 1];

	lstrcpyW(_fileName, pFileName);

	// WIC�� ����ϱ� ���� Factory ��ü ����
	hr = CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER,
		IID_PPV_ARGS(&_imageInfo->pWICImagingFactory));
	assert(hr == S_OK);

	// ���ڴ� ����
	hr = _imageInfo->pWICImagingFactory->CreateDecoderFromFilename(_fileName, NULL, GENERIC_READ, WICDecodeMetadataCacheOnDemand,
		&(_imageInfo->pWICDecoder));
	assert(hr == S_OK);

	// ù ��° �������� ����� �� �ִ� ��ü ����
	hr = _imageInfo->pWICDecoder->GetFrame(0, &_imageInfo->pWICFrameDecoder);
	assert(hr == S_OK);

	// ���� ������ ����
	hr = _imageInfo->pWICImagingFactory->CreateFormatConverter(&_imageInfo->pWICFormatConverter);
	assert(hr == S_OK);

	// ��Ʈ������ ��ȯ
	hr = _imageInfo->pWICFormatConverter->Initialize(_imageInfo->pWICFrameDecoder, GUID_WICPixelFormat32bppPBGRA,
		WICBitmapDitherTypeNone, NULL, 0.0f, WICBitmapPaletteTypeCustom);

	// ��ȯ�� �̹��� ������ ����Ͽ� D2D�� ��Ʈ�� ����
	hr = D2DMANAGER->pRenderTarget->CreateBitmapFromWicBitmap(_imageInfo->pWICFormatConverter, NULL, &_imageInfo->pBitmap);

	return S_OK;
}

void image::release()
{
	if (_imageInfo)
	{
		SelectObject(_imageInfo->hMemDC, _imageInfo->hOBit);
		DeleteObject(_imageInfo->hBit);
		DeleteDC(_imageInfo->hMemDC);

		SAFE_DELETE(_imageInfo);
		SAFE_DELETE(_fileName);

		_trans = false;
		_transColor = RGB(0, 0, 0);
	}
}

const HRESULT image::get_RGB(int x, int y)
{				//BITMAP
	/**********************************/
		//BITMAPFILEHEADER
		//��Ʈ�� ���� ��ü����
	/**********************************/
	;	// BITMAPINFOHEADER
		// ũ��, �������˿� ����������, ��Ÿ ��ġ �������� ���� ����
	/**********************************/
			//	RGBQUAD
		// Color Table�� ������ ����
	/**********************************/
			// PIXEL DATA
			// ���� �����ͳ���
	/**********************************/

	IWICBitmapSource* temp;
	temp = _imageInfo->pWICFormatConverter;
	
	UINT width = 0, height = 0;
	temp->GetSize(&width, &height);
	
	BITMAPINFO bit_info;
	ZeroMemory(&bit_info, sizeof(bit_info));
	bit_info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bit_info.bmiHeader.biWidth = width;
	bit_info.bmiHeader.biHeight = -(LONG)height;
	bit_info.bmiHeader.biPlanes = 1;
	bit_info.bmiHeader.biBitCount = 32;
	bit_info.bmiHeader.biCompression = BI_RGB;
	
	HDC MonitorDC = GetDC(NULL);
	void* buffer = NULL;

	_imageInfo->hMemDC = CreateCompatibleDC(MonitorDC);
	_imageInfo->hBit = CreateDIBSection(_imageInfo->hMemDC, &bit_info, DIB_PAL_COLORS, &buffer, NULL, 0);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->x = x;
	_imageInfo->y = y;

	ReleaseDC(NULL, MonitorDC);
	assert(_imageInfo->hMemDC != 0);
	assert(_imageInfo->hBit != 0);

	UINT stride = ((((width * 32) + 31) >> 5) << 2);

	return temp->CopyPixels(nullptr, stride, stride * height, static_cast<BYTE*>(buffer));
}

void image::rotation_start(float destX, float destY, float angle)
{
	D2D1_POINT_2F center_pos;

	center_pos.x = destX - CAMERAMANAGER->get_camera_x() + _imageInfo->width / 2;
	center_pos.y = destY - CAMERAMANAGER->get_camera_y() + _imageInfo->height / 2;

	D2DMANAGER->pRenderTarget->SetTransform(Matrix3x2F::Rotation(angle, center_pos));

}

void image::Framerotation_start(float destX, float destY, float angle)
{
	D2D1_POINT_2F center_pos;

	center_pos.x = destX - CAMERAMANAGER->get_camera_x() + _imageInfo->frameWidth / 2;
	center_pos.y = destY - CAMERAMANAGER->get_camera_y() + _imageInfo->frameHeight / 2;

	D2DMANAGER->pRenderTarget->SetTransform(Matrix3x2F::Rotation(angle, center_pos));
}

void image::rotation_end()
{
	D2DMANAGER->pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
}

D2D1_MATRIX_3X2_F image::rotation_matrix(float destX, float destY, float angle)
{
	D2D1_POINT_2F center_pos;
	D2D1_MATRIX_3X2_F mat;

	center_pos.x = destX - CAMERAMANAGER->get_camera_x() + _imageInfo->width / 2;
	center_pos.y = destY - CAMERAMANAGER->get_camera_y() + _imageInfo->height / 2;

	mat = D2D1::Matrix3x2F::Rotation(angle, center_pos);

	return mat;
}

D2D1_MATRIX_3X2_F image::Frame_rotation_matrix(float destX, float destY, float angle)
{
	D2D1_POINT_2F center_pos;
	D2D1_MATRIX_3X2_F mat;

	center_pos.x = destX - CAMERAMANAGER->get_camera_x() + _imageInfo->frameWidth / 2;
	center_pos.y = destY - CAMERAMANAGER->get_camera_y() + _imageInfo->frameHeight / 2;

	mat = D2D1::Matrix3x2F::Rotation(angle, center_pos);

	return mat;
}

void image::scale_start(float destX, float destY, float x = 1.0f, float y = 1.0f)
{
	D2D1_POINT_2F center_pos;

	center_pos.x = destX - CAMERAMANAGER->get_camera_x() + _imageInfo->width / 2;
	center_pos.y = destY - CAMERAMANAGER->get_camera_y() + _imageInfo->height / 2;

	D2DMANAGER->pRenderTarget->SetTransform(Matrix3x2F::Scale(D2D1::SizeF(x,y), center_pos));
}

void image::Frame_scale_start(float destX, float destY, float x = 1.0f, float y = 1.0f)
{
	D2D1_POINT_2F center_pos;

	center_pos.x = destX - CAMERAMANAGER->get_camera_x() + _imageInfo->frameWidth / 2;
	center_pos.y = destY - CAMERAMANAGER->get_camera_y() + _imageInfo->frameHeight / 2;

	D2DMANAGER->pRenderTarget->SetTransform(Matrix3x2F::Scale(D2D1::SizeF(x, y), center_pos));
}

void image::scale_end()
{
	D2DMANAGER->pRenderTarget->SetTransform(Matrix3x2F::Identity());
}

D2D1_MATRIX_3X2_F image::scale_matrix(float destX, float destY, float x, float y)
{
	D2D1_POINT_2F center_pos;
	D2D1_MATRIX_3X2_F mat;

	center_pos.x = destX - CAMERAMANAGER->get_camera_x() + _imageInfo->width / 2;
	center_pos.y = destY - CAMERAMANAGER->get_camera_y() + _imageInfo->height / 2;

	mat = D2D1::Matrix3x2F::Scale(D2D1::SizeF(x, y), center_pos);

	return mat;
}

D2D1_MATRIX_3X2_F image::Frame_scale_matrix(float destX, float destY, float x, float y)
{
	D2D1_POINT_2F center_pos;
	D2D1_MATRIX_3X2_F mat;

	center_pos.x = destX - CAMERAMANAGER->get_camera_x() + _imageInfo->frameWidth / 2;
	center_pos.y = destY - CAMERAMANAGER->get_camera_y() + _imageInfo->frameHeight / 2;

	mat = D2D1::Matrix3x2F::Scale(D2D1::SizeF(x, y), center_pos);

	return mat;
}

void image::render(float destX, float destY, float opacity)
{
	float x_pos = destX - CAMERAMANAGER->get_camera_x();
	float y_pos = destY - CAMERAMANAGER->get_camera_y();

	if (_imageInfo->pBitmap != NULL)
	{
		D2D1_RECT_F dxArea = RectF(x_pos, y_pos, x_pos + _imageInfo->width, y_pos + _imageInfo->height);
		D2D1_RECT_F dxArea2 = RectF(0, 0, _imageInfo->width, _imageInfo->height);

		D2DMANAGER->pRenderTarget->DrawBitmap(
		_imageInfo->pBitmap,					// ������ ��Ʈ��
		dxArea,									// �츮�� ���� ȭ�鿡 ������ ȭ��ũ�� ����
		opacity,								// ���� ���� ( 0.0 ~ 1.0f) ���� ��
		D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,  // ȸ���̳� ������������ �̹��� �ɼ� ������
		dxArea2									// �̹����� �����κи� �����ְ������ �ǵ帮�� ����. (SourX, SourY, SourWidth, SourHeight)
		);
	}

}

void image::renderUI(float destX, float destY, float sourX, float sourY, float tempX, float tempY, float opacity)
{
	float x_pos = destX - CAMERAMANAGER->get_camera_x();
	float y_pos = destY - CAMERAMANAGER->get_camera_y();

	if (_imageInfo->pBitmap != NULL)
	{
		D2D1_RECT_F dxArea = RectF(x_pos + tempX, y_pos + sourY, x_pos + _imageInfo->width - sourX, y_pos + _imageInfo->height - tempY);
		D2D1_RECT_F dxArea2 = RectF(0 + tempX, 0 + sourY, _imageInfo->width - sourX, _imageInfo->height - tempY);

		D2DMANAGER->pRenderTarget->DrawBitmap(
			_imageInfo->pBitmap,					// ������ ��Ʈ��
			dxArea,									// �츮�� ���� ȭ�鿡 ������ ȭ��ũ�� ����
			opacity,								// ���� ���� ( 0.0 ~ 1.0f) ���� ��
			D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,  // ȸ���̳� ������������ �̹��� �ɼ� ������
			dxArea2									// �̹����� �����κи� �����ְ������ �ǵ帮�� ����. (SourX, SourY, SourWidth, SourHeight)
		);

	}
}

void image::render(float destX, float destY, float sourX, float sourY, int sourWidth, int sourHeight, float opacity)
{
	float x_pos = destX - CAMERAMANAGER->get_camera_x();
	float y_pos = destY - CAMERAMANAGER->get_camera_y();

	D2D1_RECT_F dxArea = RectF(x_pos, y_pos, x_pos + _imageInfo->width, y_pos + _imageInfo->height);
	D2D1_RECT_F dxArea2 = RectF(sourX, sourY, sourX + sourWidth, sourY + sourHeight);

	D2DMANAGER->pRenderTarget->DrawBitmap(_imageInfo->pBitmap, dxArea, opacity,
		D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, dxArea2);
}

void image::render(float destX, float destY, float destWidth, float destHeight, float sourX, float sourY, float sourWidth, float sourHeight, float opacity)
{
	float x_pos = destX - CAMERAMANAGER->get_camera_x();
	float y_pos = destY - CAMERAMANAGER->get_camera_y();

	D2D1_RECT_F dxArea = RectF(x_pos, y_pos, x_pos + destWidth, y_pos + destHeight);
	D2D1_RECT_F dxArea2 = RectF(sourX, sourY, sourX + sourWidth, sourY + sourHeight);

	D2DMANAGER->pRenderTarget->DrawBitmap(_imageInfo->pBitmap, dxArea, opacity,
		D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, dxArea2);
}

void image::FrameRender(float destX, float destY, int currentFrameX, int currentFrameY, float opacity)
{
	float x_pos = destX - CAMERAMANAGER->get_camera_x();
	float y_pos = destY - CAMERAMANAGER->get_camera_y();

	if (_imageInfo->pBitmap != NULL)
	{
		D2D1_RECT_F dxArea = RectF(x_pos, y_pos, x_pos + _imageInfo->frameWidth, y_pos + _imageInfo->frameHeight);
		D2D1_RECT_F dxArea2 = RectF(currentFrameX * _imageInfo->frameWidth, currentFrameY * _imageInfo->frameHeight,
			(currentFrameX + 1) * _imageInfo->frameWidth, (currentFrameY + 1) * _imageInfo->frameHeight);

		D2DMANAGER->pRenderTarget->DrawBitmap(
			_imageInfo->pBitmap, 
			dxArea, 
			opacity,
			D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, 
			dxArea2
		);
	}
}

void image::aniRender(float destX, float destY, animation* ani, float opacity)
{
	float x_pos = destX - CAMERAMANAGER->get_camera_x();
	float y_pos = destY - CAMERAMANAGER->get_camera_y();
	
	float y = ani->getFramePos().y;

	if (y != 0)
	{
		y = ani->getFramePos().y + 1;
	}

	// ȭ�鿡 �׷��� �̹����� ��ǥ, �ʺ�, ����
	D2D1_RECT_F dxArea = RectF(x_pos, y_pos, x_pos + ani->getFrameWidth(), y_pos + ani->getFrameHeight());
	
	// ������ �̹����� ������ ��ǥ, �ʺ�, ���� -> �ǵ��� ������............................................
	D2D1_RECT_F dxArea2 = RectF(ani->getFramePos().x, y,
		ani->getFramePos().x + _imageInfo->frameWidth, ani->getFramePos().y + _imageInfo->frameHeight);

	D2DMANAGER->pRenderTarget->DrawBitmap(
		_imageInfo->pBitmap,
		dxArea,
		opacity,
		D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
		dxArea2
	);

}
void image::loopRender(const D2D1_RECT_F drawArea, int offSetX, int offSetY)
{
	//������ ������ ���������� % �����ڷ� �ϸ� ����ϴ�
	if (offSetX < 0) offSetX = _imageInfo->width + (offSetX % _imageInfo->width);
	if (offSetY < 0) offSetY = _imageInfo->height + (offSetY % _imageInfo->height);

	//�ʿ��� ������
	int sourWidth;
	int sourHeight;

	D2D1_RECT_F rcDest;
	D2D1_RECT_F rcSour;

	//�׷����� ������ ��������(���غ���)
	int drawAreaX = drawArea.left;
	int drawAreaY = drawArea.top;
	int drawAreaW = drawArea.right - drawAreaX;
	int drawAreaH = drawArea.bottom - drawAreaY;

	//Y�� �������� (������ �����ϴ�)

	for (int y = 0; y < drawAreaH; y += sourHeight)
	{
		rcSour.top = (y + offSetY) % _imageInfo->height;
		rcSour.bottom = _imageInfo->height;

		sourHeight = rcSour.bottom - rcSour.top;

		//ȭ�� ������ ���� ���� Ȯ�� (�����ؿ;��ϴ� ���� ����)
		if (y + sourHeight > drawAreaH)
		{
			rcSour.bottom -= (y + sourHeight) - drawAreaH;
			sourHeight = rcSour.bottom - rcSour.top;
		}

		rcDest.top = y + drawAreaY;
		rcDest.bottom = rcDest.top + sourHeight;

		//�����൵ �սô�
		for (int x = 0; x < drawAreaW; x += sourWidth)
		{
			rcSour.left = (x + offSetX) % _imageInfo->width;
			rcSour.right = _imageInfo->width;

			sourWidth = rcSour.right - rcSour.left;

			if (x + sourWidth > drawAreaW)
			{
				rcSour.right -= (x + sourWidth) - drawAreaW;
				sourWidth = rcSour.right - rcSour.left;
			}

			rcDest.left = x + drawAreaX;
			rcDest.right = rcDest.left + sourWidth;

			D2DMANAGER->pRenderTarget->DrawBitmap(
				_imageInfo->pBitmap,
				D2D1::RectF(rcDest.left - CAMERAMANAGER->get_camera_x(), rcDest.top - CAMERAMANAGER->get_camera_y(), rcDest.right - CAMERAMANAGER->get_camera_x(), rcDest.bottom - CAMERAMANAGER->get_camera_y()),
				1.0f,
				D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
				rcSour
			);
		}
	}

}

void image::loopRender(const D2D1_RECT_F drawArea, int offSetX, int offSetY, float opacity)
{
	//������ ������ ���������� % �����ڷ� �ϸ� ����ϴ�
	if (offSetX < 0) offSetX = _imageInfo->width + (offSetX % _imageInfo->width);
	if (offSetY < 0) offSetY = _imageInfo->height + (offSetY % _imageInfo->height);

	//�ʿ��� ������
	int sourWidth;
	int sourHeight;

	D2D1_RECT_F rcDest;
	D2D1_RECT_F rcSour;

	//�׷����� ������ ��������(���غ���)
	int drawAreaX = drawArea.left;
	int drawAreaY = drawArea.top;
	int drawAreaW = drawArea.right - drawAreaX;
	int drawAreaH = drawArea.bottom - drawAreaY;

	//Y�� �������� (������ �����ϴ�)

	for (int y = 0; y < drawAreaH; y += sourHeight)
	{
		rcSour.top = (y + offSetY) % _imageInfo->height;
		rcSour.bottom = _imageInfo->height;

		sourHeight = rcSour.bottom - rcSour.top;

		//ȭ�� ������ ���� ���� Ȯ�� (�����ؿ;��ϴ� ���� ����)
		if (y + sourHeight > drawAreaH)
		{
			rcSour.bottom -= (y + sourHeight) - drawAreaH;
			sourHeight = rcSour.bottom - rcSour.top;
		}

		rcDest.top = y + drawAreaY;
		rcDest.bottom = rcDest.top + sourHeight;

		//�����൵ �սô�
		for (int x = 0; x < drawAreaW; x += sourWidth)
		{
			rcSour.left = (x + offSetX) % _imageInfo->width;
			rcSour.right = _imageInfo->width;

			sourWidth = rcSour.right - rcSour.left;

			if (x + sourWidth > drawAreaW)
			{
				rcSour.right -= (x + sourWidth) - drawAreaW;
				sourWidth = rcSour.right - rcSour.left;
			}

			rcDest.left = x + drawAreaX;
			rcDest.right = rcDest.left + sourWidth;

			D2DMANAGER->pRenderTarget->DrawBitmap(
				_imageInfo->pBitmap,
				D2D1::RectF(rcDest.left - CAMERAMANAGER->get_camera_x(), rcDest.top - CAMERAMANAGER->get_camera_y(), rcDest.right - CAMERAMANAGER->get_camera_x(), rcDest.bottom - CAMERAMANAGER->get_camera_y()),
				opacity,
				D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
				rcSour
			);
		}
	}

}

void image::setTransColor(BOOL trans, COLORREF transColor)
{
	_trans = trans;
	_transColor = transColor;
}

