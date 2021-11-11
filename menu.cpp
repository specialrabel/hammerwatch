#include "stdafx.h"
#include "menu.h"
#include "Player.h"

HRESULT menu::init()
{
	//초기화
	_menuShow = _menuMain = _menuItems = _menuEquipArmour = _menuEquipWeapon = _menuOils = _menuOilUse = false;
	_dropItem = false;

	//이미지
	_menuBackGround = new image;
	_menuBackGround->D_Init(L"image\\Menu\\menuBackGround(132x33).png", 132, 33);
	_menuHeader = new image;
	_menuHeader->D_Init(L"image\\Menu\\menuHeader(132x33).png", 132, 33);
	_menuFooter = new image;
	_menuFooter->D_Init(L"image\\Menu\\menuFooter(132x3).png", 132, 3);
	_menuHighlight = new image;
	_menuHighlight->D_Init(L"image\\Menu\\menuHighlight(132x33).png", 132, 33);

	//장비 이미지
	_swordGreenImage = new image;
	_swordGreenImage->D_Init(L"image/weapon/green/검.png", 292, 18, 4, 1);
	_swordGoldImage = new image;
	_swordGoldImage->D_Init(L"image/weapon/gold/검.png", 352, 21, 4, 1);
	_lanceGreenImage = new image;
	_lanceGreenImage->D_Init(L"image/weapon/green/창.png", 316, 14, 4, 1);
	_lanceGoldImage = new image;
	_lanceGoldImage->D_Init(L"image/weapon/gold/창.png", 388, 18, 4, 1);
	_boomerangGreenImage = new image;
	_boomerangGreenImage->D_Init(L"image/weapon/green/부메랑.png", 81, 25, 3, 1);
	_boomerangGoldImage = new image;
	_boomerangGoldImage->D_Init(L"image/weapon/gold/부메랑.png", 99, 23, 3, 1);
	_staffGreenImage = new image;
	_staffGreenImage->D_Init(L"image/weapon/green/지팡이.png", 435, 39, 5, 1);
	_staffGoldImage = new image;
	_staffGoldImage->D_Init(L"image/weapon/gold/지팡이.png", 440, 22, 5, 1);


	_helmetGreenImage = new image;
	_helmetGreenImage->D_Init(L"image/Armor/green/모자.png", 35, 29);
	_helmetGoldImage = new image;
	_helmetGoldImage->D_Init(L"image/Armor/gold/모자.png", 28, 15);
	_armorGreenImage = new image;
	_armorGreenImage->D_Init(L"image/Armor/green/갑옷.png", 27, 30);
	_armorGoldImage = new image;
	_armorGoldImage->D_Init(L"image/Armor/gold/갑옷.png", 24, 28);
	_shoesGreenImage = new image;
	_shoesGreenImage->D_Init(L"image/Armor/green/신발.png", 12, 13);
	_shoesGoldImage = new image;
	_shoesGoldImage->D_Init(L"image/Armor/gold/신발.png", 11, 12);



	_greenOilImage = new image;
	_greenOilImage->D_Init(L"image/oil/초록물약.png", 19, 24);
	_goldOilImage = new image;
	_goldOilImage->D_Init(L"image/oil/황금물약.png", 15, 22);


	//글자 색에 사용할 브러쉬
	blueBrush = D2DMANAGER->CreateBrush(0x3681EA, 1.0f);
	whiteBrush = D2DMANAGER->CreateBrush(0xFFFFFF, 1.0f);

	//인벤토리 초기화
	_itemKind = _colorKind = 0;
	for (int i = 0; i < 4; i++)
	{
		_itemType[i] = TYPEEND;
		_itemColor[i] = COLOREND;
		_itemDurability[i] = 0;
	}
	for (int i = 0; i < 7; i++)
	{
		_oil[i] = COLOREND;
		_oilHaving[i] = 0;
	}
	_itemIndex = _oilIndex = 0;

	_playerData = _player->getTagPlayer();

	////테스트용 인벤토리에 아이템
	//_itemType[0] = SWORD;
	//_itemColor[0] = GOLD;
	//_itemType[1] = LANCE;
	//_itemColor[1] = GREEN;
	//_itemType[2] = BOOMERANG;
	//_itemColor[2] = GOLD;
	///*_itemType[3] = STAFF;
	//_itemColor[3] = GREEN;*/
	//_oil[0] = GREEN;
	//_oilHaving[0] = 3;
	//_oil[1] = GOLD;
	//_oilHaving[1] = 2;
	//_oilIndex = 2;


	//계산용 변수
	_sizeY = 32;
	_menuSelect = _menuNum = 0;
	_textX = _textY = 0;
	_oilKindNum = 0;




	return S_OK;
}

void menu::release()
{
}

void menu::update()
{
	//매뉴 열고 닫기
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		//매뉴가 생성될 위치
		_x = _player->getPlayerX();
		_y = _player->getPlayerY();

		//초기화
		_menuSelect = 0;
		_menuShow ^= 1;
		_menuMain = true;
		_menuItems = _menuOils = _menuItems = _menuEquipArmour = _menuEquipWeapon = _menuOilUse = false;
		_menuNum = 2;
	}

	updateMain();
	updateItems();
	updateEquipWeapon();
	updateEquipArmour();
	updateOils();
	updateOilUse();

}

void menu::render()
{
	_x = _player->getPlayerX();
	_y = _player->getPlayerY();

	if (_y >= 800) _y = 800;

	int debugX = _x - CAMERAMANAGER->get_camera_x();
	int debugY = _y - CAMERAMANAGER->get_camera_y();
	checkItems();

	//디버깅용 텍스트
	/*WCHAR str[128];
	swprintf_s(str, L"XYdata : %.1f | %.1f ",
		_x, _y);
	D2DMANAGER->DrawTextD2D(D2DMANAGER->defaultBrush, L"나눔고딕", 17.0f, str, debugX - 300, debugY -300,
		debugX - 100, debugY -250);
	swprintf_s(str, L"data :  %d |%d |%d |%d|%d  ",
		_weapon_left_color, _weapon_right_color, _helmet_color, _armor_color, _shoes_color);
	D2DMANAGER->DrawTextD2D(D2DMANAGER->defaultBrush, L"나눔고딕", 17.0f, str, debugX - 300, debugY - 250,
		debugX - 100, debugY -200);*/

		//x, y 위치 보정
	_x += 60;
	_y += 120;


	renderMain();
	renderItems();
	renderEquipWeapon();
	renderEquipArmour();
	renderOils();
	renderOilUse();

	//testRender();
}



void menu::updateMain()
{

	if (_menuShow && _menuMain)
	{
		//키입력 무시
		KEYMANAGER->isOnceKeyDown('W');
		KEYMANAGER->isOnceKeyDown(VK_LEFT);
		KEYMANAGER->isOnceKeyDown(VK_RIGHT);
		if (KEYMANAGER->isOnceKeyDown('A')) _menuShow = false;


		//확인 키
		if (KEYMANAGER->isOnceKeyDown('S') || KEYMANAGER->isOnceKeyDown('D'))
		{
			if (_menuSelect == 0)
			{
				_menuMain = false;
				_menuItems = true;
				_menuNum = 4;
				_menuSelect = 0;
			}
			if (_menuSelect == 1)
			{
				_oilKindNum = 0;
				for (int i = 0; i < 7; i++)
				{
					if (_oil[i] != COLOREND) _oilKindNum++;
				}

				_menuMain = false;
				_menuOils = true;
				_menuNum = _oilKindNum;
				_menuSelect = 0;

			}
			if (_menuSelect == 2)
			{
				_menuMain = false;
				_menuShow = false;
			}
		}

		//매뉴이동
		if (KEYMANAGER->isOnceKeyDown(VK_UP))
		{
			_menuSelect -= 1;
			if (_menuSelect == -1) _menuSelect = _menuNum;
		}
		if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
		{
			_menuSelect += 1;
			if (_menuSelect == _menuNum + 1) _menuSelect = 0;
		}

	}

}

void menu::updateItems()
{
	if (_menuShow && _menuItems)
	{

		//키입력 무시
		KEYMANAGER->isOnceKeyDown('W');
		KEYMANAGER->isOnceKeyDown(VK_LEFT);
		KEYMANAGER->isOnceKeyDown(VK_RIGHT);
		if (KEYMANAGER->isOnceKeyDown('A')) _menuShow = false;


		//확인 키
		if (KEYMANAGER->isOnceKeyDown('S') || KEYMANAGER->isOnceKeyDown('D'))
		{
			//인벤토리 데이터를 확인하여 무기나 장비 착용 페이지로 변경
			for (int i = 0; i < 4; i++)
			{
				if (_menuSelect == i)
				{

					//0번 슬롯에 아이템이 있을 경우
					if (_itemColor[i] != COLOREND)
					{
						//무기일 경우
						if (_itemType[i] == SWORD || _itemType[i] == LANCE || _itemType[i] == BOOMERANG || _itemType[i] == STAFF)
						{
							_menuEquipWeapon = true;
							_menuItems = false;
							_itemIndex = _menuSelect;
							_menuSelect = 0;
							_menuNum = 3;
						}
						//갑옷일 경우
						if (_itemType[i] == HEAD || _itemType[i] == BODY || _itemType[i] == FOOT)
						{
							_menuEquipArmour = true;
							_menuItems = false;
							_itemIndex = _menuSelect;
							_menuSelect = 0;
							_menuNum = 2;
						}
					}


				}
			}
			//뒤로 가기
			if (_menuSelect == 4)
			{
				_menuMain = true;
				_menuItems = false;
				_menuSelect = 0;
				_menuNum = 2;
			}
		}

		//매뉴이동
		if (KEYMANAGER->isOnceKeyDown(VK_UP))
		{
			_menuSelect -= 1;
			if (_menuSelect == -1) _menuSelect = _menuNum;
		}
		if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
		{
			_menuSelect += 1;
			if (_menuSelect == _menuNum + 1) _menuSelect = 0;
		}

	}

}

void menu::updateOils()
{
	if (_menuShow && _menuOils)
	{

		//키입력 무시
		KEYMANAGER->isOnceKeyDown('W');
		KEYMANAGER->isOnceKeyDown(VK_LEFT);
		KEYMANAGER->isOnceKeyDown(VK_RIGHT);
		if (KEYMANAGER->isOnceKeyDown('A')) _menuShow = false;


		//확인 키
		if (KEYMANAGER->isOnceKeyDown('S') || KEYMANAGER->isOnceKeyDown('D'))
		{
			for (int i = 0; i < _oilKindNum; i++)
			{
				if (_menuSelect == i)
				{
					_menuOilUse = true;
					_menuOils = false;
					_oilIndex = _oilSearch[_menuSelect];
					_menuSelect = 0;
					_itemHaving = 0;
					checkItems();
					_menuNum = _itemHaving;
				}
			}

			if (_menuSelect == _oilKindNum)
			{
				_menuMain = true;
				_menuOils = false;
				_menuSelect = 0;
				_menuNum = 2;
			}
		}

		//매뉴이동
		if (KEYMANAGER->isOnceKeyDown(VK_UP))
		{
			_menuSelect -= 1;
			if (_menuSelect == -1) _menuSelect = _menuNum;
		}
		if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
		{
			_menuSelect += 1;
			if (_menuSelect == _menuNum + 1) _menuSelect = 0;
		}

	}

}

void menu::updateEquipWeapon()
{

	if (_menuShow && _menuEquipWeapon)
	{

		//키입력 무시
		KEYMANAGER->isOnceKeyDown('W');
		KEYMANAGER->isOnceKeyDown(VK_LEFT);
		KEYMANAGER->isOnceKeyDown(VK_RIGHT);
		if (KEYMANAGER->isOnceKeyDown('A')) _menuShow = false;


		//확인 키
		if (KEYMANAGER->isOnceKeyDown('S') || KEYMANAGER->isOnceKeyDown('D'))
		{
			if (_menuSelect == 0)
			{
				changeEquipLeft();
				_menuShow = false;
			}
			if (_menuSelect == 1)
			{
				changeEquipRight();
				_menuShow = false;
			}
			if (_menuSelect == 2)
			{
				dropItem();
				_dropItem = true;
				_menuShow = false;
			}
			if (_menuSelect == 3)
			{
				_menuItems = true;
				_menuEquipWeapon = false;
				_menuSelect = 0;
				_menuNum = 4;
			}

		}

		//매뉴이동
		if (KEYMANAGER->isOnceKeyDown(VK_UP))
		{
			_menuSelect -= 1;
			if (_menuSelect == -1) _menuSelect = _menuNum;
		}
		if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
		{
			_menuSelect += 1;
			if (_menuSelect == _menuNum + 1) _menuSelect = 0;
		}

	}

}

void menu::updateEquipArmour()
{

	if (_menuShow && _menuEquipArmour)
	{

		//키입력 무시
		KEYMANAGER->isOnceKeyDown('W');
		KEYMANAGER->isOnceKeyDown(VK_LEFT);
		KEYMANAGER->isOnceKeyDown(VK_RIGHT);
		if (KEYMANAGER->isOnceKeyDown('A')) _menuShow = false;


		//확인 키
		if (KEYMANAGER->isOnceKeyDown('S') || KEYMANAGER->isOnceKeyDown('D'))
		{
			if (_menuSelect == 0)
			{
				if (_itemType[_itemIndex] == HEAD) changeEquipHelmet();
				if (_itemType[_itemIndex] == BODY) changeEquipArmor();
				if (_itemType[_itemIndex] == FOOT) changeEquipShoes();

				_menuShow = false;

			}
			if (_menuSelect == 1)
			{
				dropItem();
				_dropItem = true;
				_menuShow = false;
			}
			if (_menuSelect == 2)
			{
				//아이템 메뉴로 돌아감
				_menuItems = true;
				_menuEquipArmour = false;
				_menuSelect = 0;
				_menuNum = 4;
			}

		}

		//매뉴이동
		if (KEYMANAGER->isOnceKeyDown(VK_UP))
		{
			_menuSelect -= 1;
			if (_menuSelect == -1) _menuSelect = _menuNum;
		}
		if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
		{
			_menuSelect += 1;
			if (_menuSelect == _menuNum + 1) _menuSelect = 0;
		}

	}

}

void menu::updateOilUse()
{

	if (_menuShow && _menuOilUse)
	{

		//키입력 무시
		KEYMANAGER->isOnceKeyDown('W');
		KEYMANAGER->isOnceKeyDown(VK_LEFT);
		KEYMANAGER->isOnceKeyDown(VK_RIGHT);
		if (KEYMANAGER->isOnceKeyDown('A')) _menuShow = false;


		//확인 키
		if (KEYMANAGER->isOnceKeyDown('S') || KEYMANAGER->isOnceKeyDown('D'))
		{
			for (int i = 0; i < _itemHaving; i++)
			{
				if (_menuSelect == i)
				{
					changeItem();
					_menuShow = false;
				}
			}

			if (_menuSelect == _itemHaving)
			{
				_menuOils = true;
				_menuOilUse = false;
				_menuSelect = 0;
				_menuNum = _oilKindNum;
			}
		}

		//매뉴이동
		if (KEYMANAGER->isOnceKeyDown(VK_UP))
		{
			_menuSelect -= 1;
			if (_menuSelect == -1) _menuSelect = _menuNum;
		}
		if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
		{
			_menuSelect += 1;
			if (_menuSelect == _menuNum + 1) _menuSelect = 0;
		}

	}

}

void menu::renderMain()
{

	if (_menuShow && _menuMain)
	{



		_menuBackGround->render(_x, _y - _sizeY * 0, 1.0f);
		_menuBackGround->render(_x, _y - _sizeY * 1, 1.0f);
		_menuBackGround->render(_x, _y - _sizeY * 2, 1.0f);

		_menuFooter->render(_x, _y + _sizeY, 1.0f);
		_menuHeader->render(_x, _y - _sizeY * 3, 1.0f);


		_menuHighlight->render(_x, _y - (_sizeY * 2) + (_sizeY * _menuSelect), 1.0f);


		_textX = _x - CAMERAMANAGER->get_camera_x();
		_textY = _y - CAMERAMANAGER->get_camera_y();

		swprintf_s(str, L"what?");
		D2DMANAGER->DrawTextD2D(blueBrush, L"Consolas", 17.0f, str,
			_textX + DfXRevise,
			_textY - DfYRevise,
			_textX + DfXRevise + 100, _y - DfYRevise + _sizeY * 1);

		swprintf_s(str, L"Items");
		D2DMANAGER->DrawTextD2D(whiteBrush, L"Consolas", 17.0f, str,
			_textX + DfXRevise,
			_textY - DfYRevise + _sizeY,
			_textX + DfXRevise + 100, _y - DfYRevise + _sizeY * 2);

		swprintf_s(str, L"Oils");
		D2DMANAGER->DrawTextD2D(whiteBrush, L"Consolas", 17.0f, str,
			_textX + DfXRevise,
			_textY - DfYRevise + _sizeY * 2,
			_textX + DfXRevise + 100, _y - DfYRevise + _sizeY * 3);

		swprintf_s(str, L"Close");
		D2DMANAGER->DrawTextD2D(whiteBrush, L"Consolas", 17.0f, str,
			_textX + DfXRevise,
			_textY - DfYRevise + _sizeY * 3,
			_textX + DfXRevise + 100, _y - DfYRevise + _sizeY * 4);

	}

}

void menu::renderItems()
{

	if (_menuShow && _menuItems)
	{

		_menuBackGround->render(_x, _y - _sizeY * 0, 1.0f);
		_menuBackGround->render(_x, _y - _sizeY * 1, 1.0f);
		_menuBackGround->render(_x, _y - _sizeY * 2, 1.0f);
		_menuBackGround->render(_x, _y - _sizeY * 3, 1.0f);
		_menuBackGround->render(_x, _y - _sizeY * 4, 1.0f);
		_menuHeader->render(_x, _y - _sizeY * 5, 1.0f);
		_menuFooter->render(_x, _y + _sizeY, 1.0f);

		_menuHighlight->render(_x, _y - (_sizeY * 4) + (_sizeY * _menuSelect), 1.0f);

		_textX = _x - CAMERAMANAGER->get_camera_x();
		_textY = _y - CAMERAMANAGER->get_camera_y();

		swprintf_s(str, L"Items");
		D2DMANAGER->DrawTextD2D(blueBrush, L"Consolas", 17.0f, str,
			_textX + DfXRevise,
			_textY - DfYRevise + _sizeY * -2,
			_textX + DfXRevise + 100, _y - DfYRevise + _sizeY * 0);

		/*swprintf_s(str, L"무기 테스트");
		D2DMANAGER->DrawTextD2D(whiteBrush, L"Consolas", 17.0f, str,
			_textX + DfXRevise,
			_textY - DfYRevise + _sizeY * -1,
			_textX + DfXRevise + 100, _y - DfYRevise + _sizeY * 4);

		swprintf_s(str, L"갑옷 테스트");
		D2DMANAGER->DrawTextD2D(whiteBrush, L"Consolas", 17.0f, str,
			_textX + DfXRevise,
			_textY - DfYRevise + _sizeY * 0,
			_textX + DfXRevise + 100, _y - DfYRevise + _sizeY * 4);*/

			//0번 슬롯에 아이템이 있을 경우
		if (_itemColor[0] != COLOREND)
		{
			renderItems(_x, _y - _sizeY * 4, _itemType[0], _itemColor[0], _itemDurability[0]);
		}
		if (_itemColor[1] != COLOREND)
		{
			renderItems(_x, _y - _sizeY * 3, _itemType[1], _itemColor[1], _itemDurability[1]);
		}
		if (_itemColor[2] != COLOREND)
		{
			renderItems(_x, _y - _sizeY * 2, _itemType[2], _itemColor[2], _itemDurability[2]);
		}
		if (_itemColor[3] != COLOREND)
		{
			renderItems(_x, _y - _sizeY * 1, _itemType[3], _itemColor[3], _itemDurability[3]);
		}

		swprintf_s(str, L"Back");
		D2DMANAGER->DrawTextD2D(whiteBrush, L"Consolas", 17.0f, str,
			_textX + DfXRevise,
			_textY - DfYRevise + _sizeY * 3,
			_textX + DfXRevise + 100, _y - DfYRevise + _sizeY * 4);

	}

}

void menu::renderOils()
{

	if (_menuShow && _menuOils)
	{
		//소지하고 있는 오일의 종류에 따라 랜더링 증가
		for (int i = 0; i < _oilKindNum + 1; i++)
		{
			_menuBackGround->render(_x, _y - _sizeY * i, 1.0f);
		}


		_menuHeader->render(_x, _y - _sizeY * (_oilKindNum + 1), 1.0f);
		_menuFooter->render(_x, _y + _sizeY, 1.0f);

		_menuHighlight->render(_x, _y - (_sizeY * _oilKindNum) + (_sizeY * _menuSelect), 1.0f);

		//소지하고 있는 오일의 개수에 따라 랜더링
		int j = 1;
		int k = _oilKindNum - 1;

		for (int i = 0; i < 7; i++)
		{
			if (_oil[i] != COLOREND)
			{
				if (_oilHaving[i] == 1)
				{
					_oilSearch[k] = i;
					k--;
					renderItems(_x + 25, _y - _sizeY * j, OIL, _oil[i], 0);
					j++;
				}
				if (_oilHaving[i] == 2)
				{
					_oilSearch[k] = i;
					k--;
					renderItems(_x + 25, _y - _sizeY * j, OIL, _oil[i], 0);
					renderItems(_x + 5, _y - _sizeY * j, OIL, _oil[i], 0);
					j++;
				}
				if (_oilHaving[i] == 3)
				{
					_oilSearch[k] = i;
					k--;
					renderItems(_x + 45, _y - _sizeY * j, OIL, _oil[i], 0);
					renderItems(_x + 5, _y - _sizeY * j, OIL, _oil[i], 0);
					renderItems(_x + 25, _y - _sizeY * j, OIL, _oil[i], 0);
					j++;
				}
			}
		}

		_textX = _x - CAMERAMANAGER->get_camera_x();
		_textY = _y - CAMERAMANAGER->get_camera_y();

		swprintf_s(str, L"Oils");
		D2DMANAGER->DrawTextD2D(blueBrush, L"Consolas", 17.0f, str,
			_textX + DfXRevise,
			_textY - DfYRevise + _sizeY * 2 - (_sizeY*_oilKindNum),
			_textX + DfXRevise + 100, _y - DfYRevise + _sizeY * 1);


		swprintf_s(str, L"Back");
		D2DMANAGER->DrawTextD2D(whiteBrush, L"Consolas", 17.0f, str,
			_textX + DfXRevise,
			_textY - DfYRevise + _sizeY * 3,
			_textX + DfXRevise + 100, _y - DfYRevise + _sizeY * 4);

	}

}

void menu::renderEquipWeapon()
{

	if (_menuShow && _menuEquipWeapon)
	{

		_menuBackGround->render(_x, _y - _sizeY * 0, 1.0f);
		_menuBackGround->render(_x, _y - _sizeY * 1, 1.0f);
		_menuBackGround->render(_x, _y - _sizeY * 2, 1.0f);
		_menuBackGround->render(_x, _y - _sizeY * 3, 1.0f);

		_menuHeader->render(_x, _y - _sizeY * 4, 1.0f);
		_menuFooter->render(_x, _y + _sizeY, 1.0f);

		_menuHighlight->render(_x, _y - (_sizeY * 3) + (_sizeY * _menuSelect), 1.0f);

		_textX = _x - CAMERAMANAGER->get_camera_x();
		_textY = _y - CAMERAMANAGER->get_camera_y();

		renderItems(_x, _y - _sizeY * 4, _itemType[_itemIndex], _itemColor[_itemIndex], _itemDurability[_itemIndex]);

		swprintf_s(str, L"Back H.");
		D2DMANAGER->DrawTextD2D(whiteBrush, L"Consolas", 17.0f, str,
			_textX + DfXRevise - 15,
			_textY - DfYRevise + _sizeY * 0,
			_textX + DfXRevise + 100, _y - DfYRevise + _sizeY * 4);

		swprintf_s(str, L"Front H.");
		D2DMANAGER->DrawTextD2D(whiteBrush, L"Consolas", 17.0f, str,
			_textX + DfXRevise - 15,
			_textY - DfYRevise + _sizeY * 1,
			_textX + DfXRevise + 100, _y - DfYRevise + _sizeY * 4);

		swprintf_s(str, L"Drop");
		D2DMANAGER->DrawTextD2D(whiteBrush, L"Consolas", 17.0f, str,
			_textX + DfXRevise,
			_textY - DfYRevise + _sizeY * 2,
			_textX + DfXRevise + 100, _y - DfYRevise + _sizeY * 4);


		swprintf_s(str, L"Back");
		D2DMANAGER->DrawTextD2D(whiteBrush, L"Consolas", 17.0f, str,
			_textX + DfXRevise,
			_textY - DfYRevise + _sizeY * 3,
			_textX + DfXRevise + 100, _y - DfYRevise + _sizeY * 4);

	}

}

void menu::renderEquipArmour()
{

	if (_menuShow && _menuEquipArmour)
	{

		_menuBackGround->render(_x, _y - _sizeY * 0, 1.0f);
		_menuBackGround->render(_x, _y - _sizeY * 1, 1.0f);
		_menuBackGround->render(_x, _y - _sizeY * 2, 1.0f);
		_menuBackGround->render(_x, _y - _sizeY * 3, 1.0f);

		_menuHeader->render(_x, _y - _sizeY * 4, 1.0f);
		_menuFooter->render(_x, _y + _sizeY, 1.0f);

		_menuHighlight->render(_x, _y - (_sizeY * 3) + (_sizeY * _menuSelect), 1.0f);

		_textX = _x - CAMERAMANAGER->get_camera_x();
		_textY = _y - CAMERAMANAGER->get_camera_y();


		swprintf_s(str, L"Equip");
		D2DMANAGER->DrawTextD2D(whiteBrush, L"Consolas", 17.0f, str,
			_textX + DfXRevise,
			_textY - DfYRevise + _sizeY * 0,
			_textX + DfXRevise + 100, _y - DfYRevise + _sizeY * 4);

		swprintf_s(str, L"Drop");
		D2DMANAGER->DrawTextD2D(whiteBrush, L"Consolas", 17.0f, str,
			_textX + DfXRevise,
			_textY - DfYRevise + _sizeY * 1,
			_textX + DfXRevise + 100, _y - DfYRevise + _sizeY * 4);

		swprintf_s(str, L"Back");
		D2DMANAGER->DrawTextD2D(whiteBrush, L"Consolas", 17.0f, str,
			_textX + DfXRevise,
			_textY - DfYRevise + _sizeY * 2,
			_textX + DfXRevise + 100, _y - DfYRevise + _sizeY * 4);

	}

}

void menu::renderOilUse()
{

	if (_menuShow && _menuOilUse)
	{
		//소지하고 있는 장비의 개수에 따라 랜더링 증가
		for (int i = 0; i < _itemHaving + 1; i++)
		{
			_menuBackGround->render(_x, _y - _sizeY * i, 1.0f);
		}


		_menuHeader->render(_x, _y - _sizeY * (_itemHaving + 1), 1.0f);
		_menuFooter->render(_x, _y + _sizeY, 1.0f);

		//사용 오일 표시
		renderItems(_x, _y - _sizeY * (_itemHaving + 1), OIL, _oil[_oilIndex], 0);

		_menuHighlight->render(_x, _y - (_sizeY * _itemHaving) + (_sizeY * _menuSelect), 1.0f);

		//소지하고 있는 아이탬 순서대로 랜더링

		int j = 1;
		int k = _itemHaving - 1;

		//장착중인 아이템
		if (_shoes_color != COLOREND)
		{
			_search[k] = IndexShoes;
			k--;
			renderItems(_x, _y - _sizeY * j, FOOT, _shoes_color, _shoes_durability);
			j++;
		}
		if (_armor_color != COLOREND)
		{
			_search[k] = IndexArmor;
			k--;
			renderItems(_x, _y - _sizeY * j, BODY, _armor_color, _armor_durability);
			j++;
		}
		if (_helmet_color != COLOREND)
		{
			_search[k] = IndexHelmet;
			k--;
			renderItems(_x, _y - _sizeY * j, HEAD, _helmet_color, _helmet_durability);
			j++;
		}
		if (_weapon_right_color != COLOREND)
		{
			_search[k] = IndexRight;
			k--;
			renderItems(_x, _y - _sizeY * j, _weapon_right_type, _weapon_right_color, _weapon_right_durability);
			j++;
		}
		if (_weapon_left_color != COLOREND)
		{
			_search[k] = IndexLeft;
			k--;
			renderItems(_x, _y - _sizeY * j, _weapon_left_type, _weapon_left_color, _weapon_left_durability);
			j++;
		}
		//소지하고 있는 아이템
		for (int i = 3; i >= 0; i--)
		{
			if (_itemColor[i] != COLOREND)
			{
				_search[k] = i;
				k--;
				renderItems(_x, _y - _sizeY * j, _itemType[i], _itemColor[i], _itemDurability[i]);
				j++;
			}
		}

		_textX = _x - CAMERAMANAGER->get_camera_x();
		_textY = _y - CAMERAMANAGER->get_camera_y();

		swprintf_s(str, L"Apply");
		D2DMANAGER->DrawTextD2D(blueBrush, L"Consolas", 17.0f, str,
			_textX + DfXRevise,
			_textY - DfYRevise + _sizeY * 2 - (_sizeY*_itemHaving),
			_textX + DfXRevise + 100, _y - DfYRevise + _sizeY * 1);


		swprintf_s(str, L"Back");
		D2DMANAGER->DrawTextD2D(whiteBrush, L"Consolas", 17.0f, str,
			_textX + DfXRevise,
			_textY - DfYRevise + _sizeY * 3,
			_textX + DfXRevise + 100, _y - DfYRevise + _sizeY * 4);

	}

}

bool menu::checkPickUp(int type, int color, int durability)
{
	//무기 및 방어구라면
	if (type == SWORD || type == LANCE || type == BOOMERANG || type == STAFF || type == HEAD || type == BODY || type == FOOT)
	{
		//인벤토리에 자리가 있으면 넣는다
		for (int i = 0; i < 4; i++)
		{
			if (_itemColor[i] == COLOREND)
			{
				_itemType[i] = type;
				_itemColor[i] = color;
				_itemDurability[i] = durability;
				return true;
			}
		}
	}
	//오일의 경우
	if (type == OIL)
	{
		//인벤토리에 자리가 있으면 넣는다
		if (_oilHaving[color] < 3)
		{
			_oilHaving[color] += 1;
			return true;
		}
	}

	//인벤토리에 자리가 없을 경우
	return false;

}


void menu::menuShow()
{

}

void menu::menuCoverUp()
{
}


void menu::changeEquipLeft()
{
	_playerData = _player->getTagPlayer();
	//기존 데이터 저장
	_weapon_left_color = _playerData->weapon_left_color;
	_weapon_left_type = _playerData->weapon_left_type;

	//플레이어 장비 변경
	_playerData->weapon_left_color = _itemColor[_itemIndex];
	_playerData->weapon_left_type = _itemType[_itemIndex];

	//인벤토리에 플레이어 장비 넣기
	_itemColor[_itemIndex] = _weapon_left_color;
	_itemType[_itemIndex] = _weapon_left_type;

}

void menu::changeEquipRight()
{

	_playerData = _player->getTagPlayer();
	//기존 데이터 저장
	_weapon_right_color = _playerData->weapon_right_color;
	_weapon_right_type = _playerData->weapon_right_type;

	//플레이어 장비 변경
	_playerData->weapon_right_color = _itemColor[_itemIndex];
	_playerData->weapon_right_type = _itemType[_itemIndex];

	//인벤토리에 플레이어 장비 넣기
	_itemColor[_itemIndex] = _weapon_right_color;
	_itemType[_itemIndex] = _weapon_right_type;

}

void menu::changeEquipHelmet()
{

	_playerData = _player->getTagPlayer();
	//기존 데이터 저장
	_helmet_color = _playerData->helmet_color;

	//플레이어 장비 변경
	_playerData->helmet_color = _itemColor[_itemIndex];

	//인벤토리에 플레이어 장비 넣기
	_itemColor[_itemIndex] = _helmet_color;


}

void menu::changeEquipArmor()
{

	_playerData = _player->getTagPlayer();
	//기존 데이터 저장
	_armor_color = _playerData->armor_color;

	//플레이어 장비 변경
	_playerData->armor_color = _itemColor[_itemIndex];

	//인벤토리에 플레이어 장비 넣기
	_itemColor[_itemIndex] = _armor_color;

}

void menu::changeEquipShoes()
{

	_playerData = _player->getTagPlayer();
	//기존 데이터 저장
	_shoes_color = _playerData->shoes_color;

	//플레이어 장비 변경
	_playerData->shoes_color = _itemColor[_itemIndex];

	//인벤토리에 플레이어 장비 넣기
	_itemColor[_itemIndex] = _shoes_color;

}

void menu::changeItem()
{

	//아이템 변화
	switch (_search[_menuSelect])
	{
	case menu::Index0:
		_itemColor[0] = _oil[_oilIndex];
		_itemDurability[0] = 0;
		break;
	case menu::Index1:
		_itemColor[1] = _oil[_oilIndex];
		_itemDurability[1] = 0;
		break;
	case menu::Index2:
		_itemColor[2] = _oil[_oilIndex];
		_itemDurability[2] = 0;
		break;
	case menu::Index3:
		_itemColor[3] = _oil[_oilIndex];
		_itemDurability[3] = 0;
		break;
	case menu::IndexLeft:
		_playerData->weapon_left_color = _oil[_oilIndex];
		_playerData->weapon_left_durability = 0;
		break;
	case menu::IndexRight:
		_playerData->weapon_right_color = _oil[_oilIndex];
		_playerData->weapon_right_durability = 0;
		break;
	case menu::IndexHelmet:
		_playerData->helmet_color = _oil[_oilIndex];
		_playerData->helmet_durability = 0;
		break;
	case menu::IndexArmor:
		_playerData->armor_color = _oil[_oilIndex];
		_playerData->armor_durability = 0;
		break;
	case menu::IndexShoes:
		_playerData->shoes_color = _oil[_oilIndex];
		_playerData->shoes_durability = 0;
		break;
	default:
		break;
	}

	//오일 소모
	_oilHaving[_oilIndex] -= 1;
	if (_oilHaving[_oilIndex] == 0)
	{
		_oil[_oilIndex] = COLOREND;
		_oilKindNum -= 1;
	}

}

void menu::renderItems(int x, int y, int type, int color, int durability)
{
	switch (type)
	{
	case SWORD:
		switch (color)
		{
		case GREEN:
			_swordGreenImage->FrameRender(x + 20, y + 5, durability, 0);
			break;
		case GOLD:
			_swordGoldImage->FrameRender(x + 20, y + 5, durability, 0);
			break;
		}
		break;
	case LANCE:
		switch (color)
		{
		case GREEN:
			_lanceGreenImage->FrameRender(x + 30, y + 5, durability, 0);

			break;
		case GOLD:
			_lanceGoldImage->FrameRender(x + 30, y + 5, durability, 0);

			break;
		}
		break;
	case BOOMERANG:
		switch (color)
		{
		case GREEN:
			_boomerangGreenImage->FrameRender(x + 30, y + 5, durability, 0);

			break;
		case GOLD:
			_boomerangGoldImage->FrameRender(x + 30, y + 5, durability, 0);

			break;
		}
		break;
	case STAFF:
		switch (color)
		{
		case GREEN:
			_staffGreenImage->FrameRender(x + 30, y + 5, durability, 0);

			break;
		case GOLD:
			_staffGoldImage->FrameRender(x + 30, y + 5, durability, 0);

			break;
		}
		break;

	case HEAD:
		switch (color)
		{
		case GREEN:
			_helmetGreenImage->render(x + 30, y + 5);

			break;
		case GOLD:
			_helmetGoldImage->render(x + 30, y + 5);

			break;
		}
		break;

	case BODY:
		switch (color)
		{
		case GREEN:
			_armorGreenImage->render(x + 30, y + 5);

			break;
		case GOLD:
			_armorGoldImage->render(x + 30, y + 5);

			break;
		}
		break;

	case FOOT:
		switch (color)
		{
		case GREEN:
			_shoesGreenImage->render(x + 30, y + 5);

			break;
		case GOLD:
			_shoesGoldImage->render(x + 30, y + 5);

			break;
		}
		break;


	case OIL:
		switch (color)
		{
		case GREEN:
			_greenOilImage->render(x + 30, y + 5);

			break;
		case GOLD:
			_goldOilImage->render(x + 30, y + 5);

			break;
		}
		break;
	}



}

void menu::checkItems()
{
	//장비 존재 여부 데이터 로딩
	_itemHaving = 0;
	_playerData = _player->getTagPlayer();
	_weapon_left_color = _playerData->weapon_left_color;
	_weapon_right_color = _playerData->weapon_right_color;
	_helmet_color = _playerData->helmet_color;
	_armor_color = _playerData->armor_color;
	_shoes_color = _playerData->shoes_color;

	//다른 함수에서 사용하기 위한 데이터 로딩
	_weapon_left_type = _playerData->weapon_left_type;
	_weapon_right_type = _playerData->weapon_right_type;
	_weapon_left_durability = _playerData->weapon_left_durability;
	_weapon_right_durability = _playerData->weapon_right_durability;
	_helmet_durability = _playerData->helmet_durability;
	_armor_durability = _playerData->armor_durability;
	_shoes_durability = _playerData->shoes_durability;

	//존재 여부 확인
	if (_weapon_left_color != COLOREND) _itemHaving++;
	if (_weapon_right_color != COLOREND) _itemHaving++;
	if (_helmet_color != COLOREND) _itemHaving++;
	if (_armor_color != COLOREND) _itemHaving++;
	if (_shoes_color != COLOREND) _itemHaving++;
	//인벤토리 확인
	for (int i = 0; i < 4; i++)
	{
		if (_itemColor[i] != COLOREND) _itemHaving++;
	}

}

void menu::dropItem()
{
	//드랍 아이템 정보 저장
	_dropType = _itemType[_itemIndex];
	_dropColor = _itemColor[_itemIndex];
	_dropDurability = _itemDurability[_itemIndex];
	//인벤토리 데이터 삭제
	_itemType[_itemIndex] = TYPEEND;
	_itemColor[_itemIndex] = COLOREND;
	_itemDurability[_itemIndex] = 0;
}


//void menu::testRender()
//{
//	_playerData = _player->getTagPlayer();
//
//	//기존 데이터 저장
//	_weapon_left_color = _playerData->weapon_left_color;
//	_weapon_left_type = _playerData->weapon_left_type;
//	_weapon_right_color = _playerData->weapon_right_color;
//	_weapon_right_type = _playerData->weapon_right_type;
//	/*_helmet_color = _playerData->helmet_color;
//	_armor_color = _playerData->armor_color;
//	_shoes_color = _playerData->shoes_color;*/
//
//	_x = _player->getPlayerX();
//	_y = _player->getPlayerY();
//
//	renderItems(_x - 100, _y, _weapon_right_type, _weapon_right_color, 0);
//	renderItems(_x - 200, _y, _weapon_left_type, _weapon_left_color, 0);
//
//}
