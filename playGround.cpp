#include "stdafx.h"
#include "playGround.h"


playGround::playGround()
{
}


playGround::~playGround()
{
}

HRESULT playGround::init()
{
	gameNode::init(true);

	SOUNDMANAGER->addSound("Theme", "sound/Theme.mp3", true, true);
	SOUNDMANAGER->addSound("dungeon", "sound/Mines.mp3", true, true);
	SOUNDMANAGER->addSound("Village", "sound/Village.mp3", true, true);

	_title = new title;
	_village = new village;
	_dungeon = new dungeon;
	_tm = new testMap;

	SCENEMANAGER->addScene("Ÿ��Ʋ", _title);
	SCENEMANAGER->addScene("����", _village);
	SCENEMANAGER->addScene("����", _dungeon);

	SCENEMANAGER->addScene("�׽�Ʈ��", _tm);

	SCENEMANAGER->changeScene("Ÿ��Ʋ");

	return S_OK;
}

void playGround::release()
{
	gameNode::release();
}

void playGround::update()
{
	gameNode::update();
	SCENEMANAGER->update();
}

void playGround::render()
{
	D2DMANAGER->BeginDraw();

	SCENEMANAGER->render();
	TIMEMANAGER->render();

	D2DMANAGER->EndDraw();
}
