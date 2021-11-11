#include "stdafx.h"
#include "MouseCursor.h"

HRESULT MouseCursor::init()
{
	//============================
	//        MOUSE CURSOR
	//============================
	ShowCursor(false);
	{
		IMAGEMANAGER->addImage("cursorAim", L"image/ui/PLAYING_CURSOR.png", 28, 28);
		IMAGEMANAGER->addImage("cursorLance", L"image/ui/PAUSE_CURSOR.png", 20, 20);
	}

	_cursor = IMAGEMANAGER->findImage("cursorLance");

	return S_OK;
}

void MouseCursor::release()
{
}

void MouseCursor::update()
{
	if (SCENEMANAGER->currentScene("Ÿ��Ʋ")) 
	{
		_cursor = IMAGEMANAGER->findImage("cursorLance");
	}
	else if (SCENEMANAGER->currentScene("����"))
	{
		if(_ui->getIsInfo() || _ui->getIsPause() ) _cursor = IMAGEMANAGER->findImage("cursorLance");
		else _cursor = IMAGEMANAGER->findImage("cursorAim");
	}
	else if (SCENEMANAGER->currentScene("����"))
	{
		if (_ui->getIsInfo() || _ui->getIsPause()) _cursor = IMAGEMANAGER->findImage("cursorLance");
		else _cursor = IMAGEMANAGER->findImage("cursorAim");
	}

	cam_x = CAMERAMANAGER->get_camera_x();
	cam_y = CAMERAMANAGER->get_camera_y();
}

void MouseCursor::render()
{
	//CURSOR RENDER(���콺Ŀ�� ����)
	if (_cursor == IMAGEMANAGER->currentImage("cursorAim")) { _cursor->render(_ptMouse2.x + cam_x - _cursor->getWidth() / 2
 															, _ptMouse2.y + cam_y - _cursor->getHeight() / 2);
	}
	
	else _cursor->render(_ptMouse2.x + cam_x, _ptMouse2.y + cam_y);
}
