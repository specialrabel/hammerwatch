#pragma once
#include "gameNode.h"
#include "mapTool.h"
#include "npcManager.h"
#include "player.h"
#include "Ui.h"
#include "MouseCursor.h"
#include "collision.h"
#include "npcManager.h"
#include "enemyManager.h"

struct tagTeleport
{
	D2D_RECT_F rc;
};

class dungeon : public gameNode
{
private:
	player* _player;
	Ui* _ui;
	MouseCursor* _mouseCursor;
	mapTool* _mapTool;
	npcManager* _npcManager;
	collision* _collision;
	image* img;
	enemyManager* _enemy;

	tagTeleport _tp1;
	tagTeleport _tp2;
	tagTeleport _tp3;
	tagTeleport _tp4;
	tagTeleport _tp5;
	tagTeleport _tp6;
	tagTeleport _tp7;
	tagTeleport _tp8;

	bool _in;

public:
	dungeon() {};
	~dungeon() {};

	HRESULT init();
	void release();
	void update();
	void render();

	void teleport();

	void set_enemy();

	void setItem();
};

