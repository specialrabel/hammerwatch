#pragma once
#include "gameNode.h"
#include "mapTool.h"
#include "npcManager.h"
#include "player.h"
#include "Ui.h"
#include "collision.h"
#include "MouseCursor.h"
#include "enemyManager.h"


class village : public gameNode
{
private:
	player* _player;
	Ui* _ui;
	MouseCursor* _mouseCursor;
	mapTool* _mapTool;
	npcManager* _npcManager;
	collision* _collision;
	enemyManager* _enemy;

	D2D_RECT_F _tp1;

	bool _in;
public:
	village() {};
	~village() {};

	HRESULT init();
	void release();
	void update();
	void render();
	void teleport();
};

