#include "stdafx.h"
#include "CameraManager.h"

CameraManager::CameraManager()
{
}

CameraManager::~CameraManager()
{
}

HRESULT CameraManager::init(int width, int height)
{
	mapsize_x = width;
	mapsize_y = height;

	camera_x = WINSIZEX;
	camera_y = WINSIZEY;

	return S_OK;
}

void CameraManager::updateScreen(float x, float y, float ratioX, float ratioY)
{
	if (x - camera_x * ratioX < 0)
	{
		x = 0;
	}
	else if (x + camera_x * (1 - ratioX) > mapsize_x)
	{
		x = mapsize_x - camera_x;
	}
	else
		x -= camera_x * ratioX;

	//Y축 (상, 하)

	if (y - camera_y * ratioY < 0)
	{
		y = 0;
	}
	else if (y + camera_y * (1 - ratioY) > mapsize_y)
	{
		y = mapsize_y - camera_y;
	}
	else
		y -= camera_y * ratioY;

	//갱신
	_x = x;
	_y = y;


}

void CameraManager::release()
{

}
