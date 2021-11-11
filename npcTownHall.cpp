#include "stdafx.h"
#include "npcTownHall.h"

HRESULT npcTownHall::init()
{
	_townHallImage = new image;
	_townHallImage->D_Init(L"image/npc/village/townHall/townHall.png", 8, 16, 1, 1);
	_shopUi1 = new image;
	_shopUi1->D_Init(L"image/npc/village/townHall/shopUi3.png", 116, 114, 2, 2);
	_shopUi2 = new image;
	_shopUi2->D_Init(L"image/npc/village/townHall/shopUi4.png", 969, 94);

	//초기 위치 지정
	_x = 620;
	_y = 1700;

	_rc = { _x - DF_widthHalf, _y - DF_widthHalf, _x + DF_widthHalf, _y + DF_widthHalf };

	_level = 1;
	_blackSmithLevel = 0;
	_skillLevel = 1;

	_upgradeOre = 5;

	return S_OK;
}

void npcTownHall::release()
{
}

void npcTownHall::update()
{
}

void npcTownHall::render()
{

	//이미지 위치 보정
	float x = 2;
	float y = 6;
	_townHallImage->Frame_scale_start(_x, _y, DF_scale, DF_scale);
	_townHallImage->FrameRender(_x - x, _y - y, 0, 0);
	_townHallImage->scale_end();


	//D2DMANAGER->Rectangle(_rc);
	//캐릭터 위치에 따라 보정 나중에 삭제
	/*float cam_x = CAMERAMANAGER->get_camera_x();
	float cam_y = CAMERAMANAGER->get_camera_y();

	ID2D1SolidColorBrush* whiteBrush = D2DMANAGER->CreateBrush(0xFFFFFF, 1.0f);
	D2DMANAGER->ElipseMakeCenter(whiteBrush, _x - cam_x - DF_elipse / 2, _y - cam_y - DF_elipse / 2, DF_elipse, DF_elipse);*/

}

void npcTownHall::renderInteraction()
{
	if (_interaction)
	{
		//카메라 보정
		float cam_x = CAMERAMANAGER->get_camera_x();
		float cam_y = CAMERAMANAGER->get_camera_y();
		//텍스트 상자 설정
		float X = 420;
		float Y = 390;
		float X2 = X + 510;
		float Y2 = Y + 500;
		//버튼 배경 위치 설정
		float XIB = 316 + cam_x;
		float YIB = 370 + cam_y;
		int sizeXB = 650;
		int sizeYB = 76;




		////
		if (_level < 2)
		{
			_shopUi2->render(XIB, YIB);
		}
		if (_level == 1)
		{
			swprintf_s(str, L"길드 업그래이드 2");
			D2DMANAGER->DrawTextD2D(D2DMANAGER->defaultBrush, L"메이플스토리", 30.0f, str, X, Y, X2, Y2);
			swprintf_s(str, L"%d", _level*_upgradeOre);
			D2DMANAGER->DrawTextD2DRight(D2DMANAGER->defaultBrush, L"메이플스토리", 30.0f, str, X, Y, X2, Y2);
		}

		////
		Y += 85;
		YIB += 85;

		if (_level < 3)
		{
			_shopUi2->render(XIB, YIB);
		}
		if (_level == 2)
		{
			swprintf_s(str, L"길드 업그래이드 2");
			D2DMANAGER->DrawTextD2D(D2DMANAGER->defaultBrush, L"메이플스토리", 30.0f, str, X, Y, X2, Y2);
			swprintf_s(str, L"%d", _level*_upgradeOre);
			D2DMANAGER->DrawTextD2DRight(D2DMANAGER->defaultBrush, L"메이플스토리", 30.0f, str, X, Y, X2, Y2);
		}
		////
		Y += 85;
		YIB += 85;

		if (_level < 4)
		{
			_shopUi2->render(XIB, YIB);

		}
		if (_level == 3)
		{
			swprintf_s(str, L"길드 업그래이드 2");
			D2DMANAGER->DrawTextD2D(D2DMANAGER->defaultBrush, L"메이플스토리", 30.0f, str, X, Y, X2, Y2);
			swprintf_s(str, L"%d", _level*_upgradeOre);
			D2DMANAGER->DrawTextD2DRight(D2DMANAGER->defaultBrush, L"메이플스토리", 30.0f, str, X, Y, X2, Y2);
		}
		////
		Y += 85;
		YIB += 85;

		if (_level < 5)
		{
			_shopUi2->render(XIB, YIB);
		}
		if (_level == 4)
		{
			swprintf_s(str, L"길드 업그래이드 2");
			D2DMANAGER->DrawTextD2D(D2DMANAGER->defaultBrush, L"메이플스토리", 30.0f, str, X, Y, X2, Y2);
			swprintf_s(str, L"%d", _level*_upgradeOre);
			D2DMANAGER->DrawTextD2DRight(D2DMANAGER->defaultBrush, L"메이플스토리", 30.0f, str, X, Y, X2, Y2);
		}
		//건물 업그래이드에 따라 활성화

		for (int i = 0; i < _skillLevel; i++)
		{
			_shopUi1->FrameRender(436 + cam_x, 300 + cam_y + 85 * i, 0, 0);
		}
		for (int i = 0; i < _blackSmithLevel; i++)
		{
			_shopUi1->FrameRender(520 + cam_x, 300 + cam_y + 85 * i, 1, 0);
		}


	}
}

void npcTownHall::setUpgradeCheck()
{
	//카메라 보정
	float cam_x = CAMERAMANAGER->get_camera_x();
	float cam_y = CAMERAMANAGER->get_camera_y();

	RECT rcSkill = {
		440 + cam_x,
		300 + cam_y + (85 * _skillLevel),
		500 + cam_x,
		360 + cam_y + (85 * _skillLevel)
	};
	RECT rcBlack = {
		520 + cam_x,
		300 + cam_y + (85 * _blackSmithLevel),
		560 + cam_x,
		360 + cam_y + (85 * _blackSmithLevel)
	};
	RECT rcBlock = {
		330 + cam_x,
		300 + cam_y + (85 * _level),
		1000 + cam_x,
		360 + cam_y + (85 * _level)
	};

	if (_skillLevel < _level)
	{
		if (PtInRect(&rcSkill, _ptMouse))
		{
			if (_playerOre >= _upgradeOre * (_skillLevel + 1))
			{
				_playerOre -= _upgradeOre * (_skillLevel + 1);
				_skillLevel++;
			}
		}
	}

	if (_blackSmithLevel < _level)
	{
		if (PtInRect(&rcBlack, _ptMouse))
		{
			if (_playerOre >= _upgradeOre * (_blackSmithLevel + 1))
			{
				_playerOre -= _upgradeOre * (_blackSmithLevel + 1);
				_blackSmithLevel++;
			}
		}
	}

	if (PtInRect(&rcBlock, _ptMouse))
	{
		if (_playerOre >= _upgradeOre * (_level + 1))
		{
			_playerOre -= _upgradeOre * (_level + 1);
			_level++;
		}
	}

}
