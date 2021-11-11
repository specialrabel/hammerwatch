#include "stdafx.h"
#include "testMap.h"
#include "player.h"

HRESULT testMap::init()
{
	CAMERAMANAGER->init(10000, 10000);

	_mapTool = new mapTool;
	_mapTool->init();
	_mapTool->load();

	if (SOUNDMANAGER->isPlaySound("Theme"))
	{
		SOUNDMANAGER->stop("Theme");
	}

	if (SOUNDMANAGER->isPlaySound("Village"))
	{
		SOUNDMANAGER->stop("Village");
	}

	SOUNDMANAGER->play("dungeon", 0.5f);

	ShowCursor(true);
	return S_OK;
}

void testMap::release()
{

}

void testMap::update()
{
	_mapTool->update();

	CAMERAMANAGER->updateScreen(0, 0, 0.5, 0.4);
}

void testMap::render()
{
	_mapTool->render();

	ITEMMANAGER->render();
	D2DMANAGER->Rectangle(D2DMANAGER->CreateBrush(RGB(0,0,255)),_rc);
}
