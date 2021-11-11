#include "stdafx.h"
#include "ship.h"


ship::ship()
{
}


ship::~ship()
{
}

HRESULT ship::init(const char* imageName, int x, int y)
{
	_image = IMAGEMANAGER->findImage(imageName);

	_x = x;
	_y = y;

	_angle = 0.0f;

	_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());

	_speed = 0;
	_radius = _image->getFrameWidth() / 2;


	return S_OK;
}

void ship::release()
{
}

void ship::update()
{
	keyControl();
	move();
}

void ship::render()
{
	draw();
}

void ship::draw()
{
	//_image->frameRender(getMemDC(), _rc.left, _rc.top);

	char str[128];
	sprintf_s(str, "%d도, %3.2f", int(_angle * 180 / PI), _speed);
	TextOut(getMemDC(), _rc.left, _rc.top - 15, str, strlen(str));

}

void ship::keyControl()
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		
		_angle += 0.04f;
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
	
		_angle -= 0.04f;
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		_speed += 0.04f;
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		_speed -= 0.04f;
	}

}

void ship::move()
{
	int frame;		//이미지 프레임 번호
	float angle;	//각도 계산용

	angle = _angle + PI16;
	
	//특정 각도별로 보여져야할 프레임 번호를 계산해주자
	frame = int(angle / PI8);
	_image->setFrameX(frame);

	float elapsedTime = TIMEMANAGER->getElapsedTime();
	float moveSpeed = elapsedTime * 100;

	if (_angle >= PI2) _angle -= PI2;
	if (_angle <= 0) _angle += PI2;

	_x += cosf(_angle) * _speed;
	_y += -sinf(_angle) * _speed;

	_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());


}
