#pragma once
#include "gameNode.h"
#include "mapTool.h"
#include "player.h"
#include "enemyManager.h"
#include "collision.h"
#include "npcManager.h"

class testMap : public gameNode
{
private:
	mapTool* _mapTool;
	player* _player;
	enemyManager* _enemy;
	collision* _collision;
	npcManager* _nm;

	D2D_RECT_F _rc;

	float _x, _y;
	int _rcSpeed;

public:
	testMap() {};
	~testMap() {};

	HRESULT init();
	void release();
	void update();
	void render();
};

