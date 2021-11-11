#include "stdafx.h"
#include "village.h"

HRESULT village::init()
{
	CAMERAMANAGER->init(10000, 10000);

	_mapTool = new mapTool;
	_mapTool->init();

	_player = new player;
	_player->init();

	_player->set_x(1200);
	_player->set_y(1800);

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

	//面倒贸府
	_collision = new collision;
	//_collision->init();
	_collision->Link_PlayerClass(_player);
	_collision->Link_npcManagerClass(_npcManager);
	_collision->Link_mapToolClass(_mapTool);
	_collision->Link_enemyClass(_enemy);
	_collision->Link_UiClass(_ui);

	_tp1 = D2DMANAGER->RectMake(1632, 864, 64, 64);

	_mapTool->load(0);
	
	if (SOUNDMANAGER->isPlaySound("Theme"))
	{
		SOUNDMANAGER->stop("Theme");
	}

	if (SOUNDMANAGER->isPlaySound("dungeon"))
	{
		SOUNDMANAGER->stop("dungeon");
	}

	SOUNDMANAGER->play("Village", 0.5f);

	SOUNDMANAGER->set_volume("Village", SOUNDMANAGER->currentVolume());


	return S_OK;
}

void village::release()
{

	_npcManager->release();

}

void village::update()
{
	_mapTool->update();
	if(!_ui->getPause() && !_ui->getIsInfo() && _ui->getNpcUi())
	_player->update();
	_collision->update();

	if (KEYMANAGER->isOnceKeyDown(VK_F1))
	{
		INIDATA->updateData(INIDATA->currentDataNum(), "X coordinate", 5705);
		INIDATA->updateData(INIDATA->currentDataNum(), "Y coordinate", 340);
		SCENEMANAGER->changeScene("带傈");
	}

	CAMERAMANAGER->updateScreen(_player->get_playerInfo().x, _player->get_playerInfo().y, 0.5, 0.4);

	_ui->update();
	_mouseCursor->update();
	teleport();
}

void village::render()
{
	_mapTool->render();
	_npcManager->render();
	ITEMMANAGER->render();
	_player->render();
	_ui->render();
	ITEMMANAGER->renderInventory();
	_npcManager->renderInteraction();
	_mouseCursor->render();
}

void village::teleport()
{
	D2D_RECT_F temp;
	D2D_RECT_F player_rc = _player->get_playerInfo().rc;

	if (INTERSECTION_RECT(temp, player_rc, _tp1))
	{
		if (KEYMANAGER->isOnceKeyDown('F'))
		{
			INIDATA->updateData(INIDATA->currentDataNum(), "X coordinate", 5705);
			INIDATA->updateData(INIDATA->currentDataNum(), "Y coordinate", 340);
			SCENEMANAGER->changeScene("带傈");
		}
		_in = true;
	}
	else _in = false;
}
