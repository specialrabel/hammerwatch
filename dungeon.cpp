#include "stdafx.h"
#include "dungeon.h"

HRESULT dungeon::init()
{
	CAMERAMANAGER->init(10000, 10000);

	_mapTool = new mapTool;
	_mapTool->init();
	_mapTool->load(1);

	_player = new player;
	_player->init();

	_ui = new Ui;
	_ui->init();

	_mouseCursor = new MouseCursor;
	_mouseCursor->init();

	_mouseCursor->setUiMemoryAdressLink(_ui);
	_ui->setPlayerMemoryAdressLink(_player);
	_player->setMapToolMemoryAddressLink(_mapTool);

	_npcManager = new npcManager;
	_npcManager->init();
	_npcManager->setVillageNpc();

	_enemy = new enemyManager;
	_enemy->LinkMaptoolClass(_mapTool);
	_enemy->LinkPlayerClass(_player);
	_enemy->init();

	set_enemy();

	setItem();

	_collision = new collision;
	_collision->Link_mapToolClass(_mapTool);
	_collision->Link_npcManagerClass(_npcManager);
	_collision->Link_PlayerClass(_player);
	_collision->Link_enemyClass(_enemy);

	img = new image;
	img = IMAGEMANAGER->addImage("fg", L"img/tile/제목 없음.png", 1600, 900);

	_tp1.rc = D2DMANAGER->RectMake(1824, 416, 64, 64);  //tp4번이랑 링크
	_tp2.rc = D2DMANAGER->RectMake(2272, 1952, 64, 64); //tp6번이랑 링크
	_tp3.rc = D2DMANAGER->RectMake(4448, 1760, 64, 64); //tp5번이랑 링크
	_tp4.rc = D2DMANAGER->RectMake(4224, 928, 64, 64);	//tp1번이랑 링크
	_tp5.rc = D2DMANAGER->RectMake(5152, 64, 64, 64);	//tp3번이랑 링크
	_tp6.rc = D2DMANAGER->RectMake(3072, 2848, 64, 64); //tp2번이랑 링크
	_tp7.rc = D2DMANAGER->RectMake(5696, 224, 64, 64);	//마을맵 가는곳, 처음 소환되는 곳
	_tp8.rc = D2DMANAGER->RectMake(2144, 1504, 64, 64); //보스맵 이동 텔포

	if (SOUNDMANAGER->isPlaySound("Village"))
	{
		SOUNDMANAGER->stop("Village");
	}

	SOUNDMANAGER->play("dungeon", 0.5f);

	return S_OK;
}

void dungeon::release()
{
	_npcManager->release();
}

void dungeon::update()
{
	_mapTool->update();
	_player->update();
	_enemy->update();
	_collision->update();
	teleport();
	CAMERAMANAGER->updateScreen(_player->get_playerInfo().x, _player->get_playerInfo().y, 0.5, 0.4);
	
	_ui->update();
	_mouseCursor->update();
}

void dungeon::render()
{
	_mapTool->render();
	_npcManager->render();
	ITEMMANAGER->render();
	_player->render();
	_enemy->render();
	_ui->render();
	ITEMMANAGER->renderInventory();

	img->render(CAMERAMANAGER->get_camera_x(), CAMERAMANAGER->get_camera_y(), 0.3);

	_mouseCursor->render();
}

void dungeon::teleport()
{
	D2D_RECT_F temp;
	D2D_RECT_F player_rc = _player->get_playerInfo().rc;

	if (INTERSECTION_RECT(temp, player_rc, _tp1.rc))
	{
		if (KEYMANAGER->isOnceKeyDown('F'))
		{
			_player->set_x((_tp4.rc.left + _tp4.rc.right) / 2);
			_player->set_y(_tp4.rc.bottom);
		}
		_in = true;
	}
	else _in = false;

	if (INTERSECTION_RECT(temp, player_rc, _tp2.rc))
	{
		if (KEYMANAGER->isOnceKeyDown('F'))
		{
			_player->set_x((_tp6.rc.left + _tp6.rc.right) / 2);
			_player->set_y(_tp6.rc.bottom);
		}
		_in = true;
	}
	else _in = false;

	if (INTERSECTION_RECT(temp, player_rc, _tp3.rc))
	{
		if (KEYMANAGER->isOnceKeyDown('F'))
		{
			_player->set_x((_tp5.rc.left + _tp5.rc.right) / 2);
			_player->set_y(_tp5.rc.bottom);
		}
		_in = true;
	}
	else _in = false;

	if (INTERSECTION_RECT(temp, player_rc, _tp4.rc))
	{
		if (KEYMANAGER->isOnceKeyDown('F'))
		{
			_player->set_x((_tp1.rc.left + _tp1.rc.right) / 2);
			_player->set_y(_tp1.rc.bottom);
		}
		_in = true;
	}
	else _in = false;

	if (INTERSECTION_RECT(temp, player_rc, _tp5.rc))
	{
		if (KEYMANAGER->isOnceKeyDown('F'))
		{
			_player->set_x((_tp3.rc.left + _tp3.rc.right) / 2);
			_player->set_y(_tp3.rc.bottom);
		}
		_in = true;
	}
	else _in = false;

	if (INTERSECTION_RECT(temp, player_rc, _tp6.rc))
	{
		if (KEYMANAGER->isOnceKeyDown('F'))
		{
			_player->set_x((_tp2.rc.left + _tp2.rc.right) / 2);
			_player->set_y(_tp2.rc.bottom);
		}
		_in = true;
	}
	else _in = false;

	if (INTERSECTION_RECT(temp, player_rc, _tp7.rc))
	{
		if (KEYMANAGER->isOnceKeyDown('F'))
		{
			SCENEMANAGER->changeScene("마을");
		}
		_in = true;
	}
	else _in = false;

	if (INTERSECTION_RECT(temp, player_rc, _tp8.rc))
	{
		if (KEYMANAGER->isOnceKeyDown('F'))
		{
			SCENEMANAGER->changeScene("보스맵");
		}
		_in = true;
	}
	else _in = false;
}

void dungeon::set_enemy()
{
	for (int i = 1; i < 9; i++)
	{
		_enemy->set_ticks(5000 + i * 100, 760);
		_enemy->set_maggots(5000 + i * 100, 790);
		_enemy->set_skeletons(4600 + i * 100, 825);
	}

	for (int i = 0; i < 10; i++)
	{
		_enemy->set_ticks(4600, 845 + 50 * i);
		_enemy->set_bats(4700, 845 + 50 * i);
		_enemy->set_maggots(4790, 845 + 50 * i);
	}

	for (int i = 0; i < 10; i++)
	{
		_enemy->set_bats(4840 + i * 100, 1480);
	}

	for (int i = 0; i < 12; i++)
	{
		_enemy->set_ticks(3785 + i * 100, 2200);
		_enemy->set_maggots(3785 + i * 100, 2250);
		_enemy->set_bats(3955 + i * 100, 2300);
	}

	for (int i = 0; i < 10; i++)
	{
		_enemy->set_skeletons(4530 + i * 100, 2735);
	}

	for (int i = 0; i < 5; i++)
	{
		_enemy->set_ticks(4545 + i * 50, 2810);
		_enemy->set_maggots(4545 + i * 50, 2890);
		_enemy->set_bats(4545 + i * 50, 2990);
	}

	for (int i = 0; i < 10; i++)
	{
		_enemy->set_maggots(3910, 2310 + i * 80);
	}
}

void dungeon::setItem()
{
	int k = 0;
	int j = 0;

	//아이템 배치
	for (int i = 0; i < 7; i++)
	{
		k = i / 4;
		j = i % 4;

		ITEMMANAGER->addItemCenter(5750 + j * 35, 340 + k * 40, i + 1, 2);

	}
	//골드 배치

	for (int i = 0; i < 10; i++)
	{
		ITEMMANAGER->addItemCenter(5780 + i*20, 760, 1000 + i, 2);
	}
	for (int i = 0; i < 6; i++)
	{
		ITEMMANAGER->addItemCenter(5780 + i * 30, 790, 1020 + i, 2);
	}
	//회복 아이탬 배치
	for (int i = 0; i < 8; i++)
	{
		ITEMMANAGER->addItemCenter(5080 + i * 30, 760, 1010 + i, 2);
	}


}
