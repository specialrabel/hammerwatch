#include "stdafx.h"
#include "npcBlackSmith.h"

HRESULT npcBlackSmith::init()
{
	_blackSmithImage = new image;
	_blackSmithImage->D_Init(L"image/npc/village/blackSmith/blackSmith.png", 288, 32, 9, 1);
	_interactionImage = new image;
	_interactionImage->D_Init(L"image/npc/village/blackSmith/interaction.png", 80, 16, 5, 1);


	//초기 위치 지정
	_x = 1200;
	_y = 1500;

	_rc = { _x - DF_widthHalf, _y - DF_widthHalf, _x + DF_widthHalf, _y + DF_widthHalf };


	//대장장이 업그레이드 변수 초기화
	_attack = 5;
	_armor = 5;
	_crit = 5;
	_speed = 0.2;

	_level = 0;
	_attackLevel = 1;
	_armorLevel = 1;
	_critLevel = 1;
	_speedLevel = 1;

	_frame = 0;
	_wait = false;

	_upgradeGold = 250;

	return S_OK;
}

void npcBlackSmith::release()
{
	_blackSmithImage->release();
	SAFE_DELETE(_blackSmithImage);
	_interactionImage->release();
	SAFE_DELETE(_interactionImage);

}

void npcBlackSmith::update()
{
}
//마을에서 NPC 랜더
void npcBlackSmith::render()
{
	//대장장이 랜더 스케일
	//대장장이 래벨에 따라 랜더링 변경
	if (_level == 0)
	{
		_interactionImage->Frame_scale_start(_x, _y, 3, 3);
		_interactionImage->FrameRender(_x - 2.5, _y - 22, 1, 0);
		_interactionImage->scale_end();

		//이미지 위치 보정

		float x = 5.5;
		float y = 8;
		_blackSmithImage->Frame_scale_start(_x, _y, DF_scale, DF_scale);
		_blackSmithImage->FrameRender(_x - x, _y - y, 0, 0);
		_blackSmithImage->scale_end();
	}
	else
	{
		//상호작용 이미지
		_interactionImage->Frame_scale_start(_x, _y, 3, 3);
		_interactionImage->FrameRender(_x - 1, _y - 24, 0, 0);
		_interactionImage->scale_end();

		_frame++;
		float x = 7;
		float y = 8;

		if (_frame >= 10)
		{
			_frame = 0;
			_indexX++;
			if (_wait)
			{
				_indexX = 1;
				_wait = false;
			}
			if (_indexX == 9)
			{
				_frame = -60;
				_indexX = 8;
				_wait = true;
			}
		}
		_blackSmithImage->Frame_scale_start(_x, _y, DF_scale, DF_scale);
		_blackSmithImage->FrameRender(_x - x, _y - y, _indexX, 0);
		_blackSmithImage->scale_end();
	}


	float cam_x = CAMERAMANAGER->get_camera_x();
	float cam_y = CAMERAMANAGER->get_camera_y();
	//대화창 생성
	if (_chat)
	{
		_frame++;
		//보정값
		float x = -100;
		float y = -110;

		//뒷 배경 생성
		D2D1_RECT_F rc = D2DMANAGER->RectMake(
			_x + x,
			_y + y,
			200,
			50);
		D2DMANAGER->Rectangle(D2DMANAGER->defaultBrush, D2DMANAGER->CreateBrush(0xFFFFFF), rc);
		swprintf_s(str, L"광석이 없어서 대장간을 열수가 없습니다.");
		D2DMANAGER->DrawTextD2DCenter(
			D2DMANAGER->defaultBrush,
			L"메이플스토리",
			18.0f,
			str,
			_x + x - cam_x,
			_y + y - cam_y,
			_x + x + 200 - cam_x,
			_y + y + 100 - cam_y
		);

		//일정 시간이 지나면 대화창 끔
		if (_frame > 300)
		{
			_frame = 0;
			_chat = false;
		}
	}




	//D2DMANAGER->Rectangle(_rc);

	//ID2D1SolidColorBrush* whiteBrush = D2DMANAGER->CreateBrush(0xFFFFFF, 1.0f);
	//D2DMANAGER->ElipseMakeCenter(whiteBrush, _x - cam_x - DF_elipse / 2, _y - cam_y - DF_elipse / 2, DF_elipse, DF_elipse);

}

//상호작용시 상점 페이지 랜더
void npcBlackSmith::renderInteraction()
{
	//대장간 레벨이 낮으면 대화창 출력
	if (_level > 0)
	{
		//카메라 보정
		float cam_x = CAMERAMANAGER->get_camera_x();
		float cam_y = CAMERAMANAGER->get_camera_y();
		//텍스트 상자 설정
		float X = 550;
		float Y = 360;
		float X2 = X + 510;
		float Y2 = Y + 500;
		//이미지 위치 설정
		float XI = 480 + cam_x;
		float YI = 352 + cam_y;
		int sizeX = 64;
		int sizeY = 64;
		//버튼 배경 위치 설정
		float XIB = 475 + cam_x;
		float YIB = 348 + cam_y;
		int sizeXB = 650;
		int sizeYB = 76;

		//활성화된 버튼
		if (_playerGold >= _armorLevel * _upgradeGold && _level >= _armorLevel)
		{
			ITEMMANAGER->renderShop2(XIB, YIB, sizeXB, sizeYB);
			ITEMMANAGER->renderShop(XI, YI, sizeX, sizeY, 0, 0, 25, 25);
		}
		swprintf_s(str, L"방어구 제련 %d", _armorLevel);
		D2DMANAGER->DrawTextD2D(D2DMANAGER->defaultBrush, L"메이플스토리", 30.0f, str, X, Y, X2, Y2);
		swprintf_s(str, L" %d", _armorLevel*_upgradeGold);
		D2DMANAGER->DrawTextD2DRight(D2DMANAGER->defaultBrush, L"메이플스토리", 30.0f, str, X, Y, X2, Y2);

		YIB += 77;
		YI += 77;
		Y += 78;
		if (_playerGold >= _attackLevel * _upgradeGold && _level >= _attackLevel)
		{
			ITEMMANAGER->renderShop2(XIB, YIB, sizeXB, sizeYB);
			ITEMMANAGER->renderShop(XI, YI, sizeX, sizeY, 25, 0, 25, 25);
		}
		swprintf_s(str, L"무기 제련 %d", _attackLevel);
		D2DMANAGER->DrawTextD2D(D2DMANAGER->defaultBrush, L"메이플스토리", 30.0f, str, X, Y, X2, Y2);
		swprintf_s(str, L" %d", _attackLevel*_upgradeGold);
		D2DMANAGER->DrawTextD2DRight(D2DMANAGER->defaultBrush, L"메이플스토리", 30.0f, str, X, Y, X2, Y2);

		YIB += 77;
		YI += 77;
		Y += 78;
		if (_playerGold >= _critLevel * _upgradeGold && _level >= _critLevel)
		{
			ITEMMANAGER->renderShop2(XIB, YIB, sizeXB, sizeYB);
			ITEMMANAGER->renderShop(XI, YI, sizeX, sizeY, 50, 0, 25, 25);
		}
		swprintf_s(str, L"치명타 확률 증가 %d", _critLevel);
		D2DMANAGER->DrawTextD2D(D2DMANAGER->defaultBrush, L"메이플스토리", 30.0f, str, X, Y, X2, Y2);
		swprintf_s(str, L" %d", _critLevel*_upgradeGold);
		D2DMANAGER->DrawTextD2DRight(D2DMANAGER->defaultBrush, L"메이플스토리", 30.0f, str, X, Y, X2, Y2);

		YIB += 77;
		YI += 77;
		Y += 78;
		if (_playerGold >= _speedLevel * _upgradeGold && _level >= _speedLevel)
		{
			ITEMMANAGER->renderShop2(XIB, YIB, sizeXB, sizeYB);
			ITEMMANAGER->renderShop(XI, YI, sizeX, sizeY, 75, 0, 25, 25);
		}
		swprintf_s(str, L"이동속도 증가 %d", _speedLevel);
		D2DMANAGER->DrawTextD2D(D2DMANAGER->defaultBrush, L"메이플스토리", 30.0f, str, X, Y, X2, Y2);
		swprintf_s(str, L" %d", _speedLevel*_upgradeGold);
		D2DMANAGER->DrawTextD2DRight(D2DMANAGER->defaultBrush, L"메이플스토리", 30.0f, str, X, Y, X2, Y2);
	}

}

int npcBlackSmith::getBlackSmithGold(int num)
{

	switch (num)
	{
	case 1:
		return _armorLevel * _upgradeGold;
		break;
	case 2:
		return _attackLevel * _upgradeGold;
		break;
	case 3:
		return _critLevel * _upgradeGold;
		break;
	case 4:
		return _speedLevel * _upgradeGold;
		break;
	}
	return 0;
}

void npcBlackSmith::setUpgrade(int num)
{

	switch (num)
	{
	case 1:
		_armorLevel++;
		break;
	case 2:
		_attackLevel++;
		break;
	case 3:
		_critLevel++;
		break;
	case 4:
		_speedLevel++;
		break;
	}
}

float npcBlackSmith::getUpgradeData(int num)
{
	switch (num)
	{
	case 1:
		return _armor;
		break;
	case 2:
		return _attack;
		break;
	case 3:
		return _crit;
		break;
	case 4:
		return _speed;
		break;
	}

	return 0.0f;
}

int npcBlackSmith::getUpgradeDataLevel(int num)
{
	switch (num)
	{
	case 1:
		return _armorLevel;
		break;
	case 2:
		return _attackLevel;
		break;
	case 3:
		return _critLevel;
		break;
	case 4:
		return _speedLevel;
		break;
	}

	return 0;
}
