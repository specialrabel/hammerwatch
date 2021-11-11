#pragma once
#include "gameNode.h"
#include "village.h"
#include "dungeon.h"
#include "title.h"
#include "testMap.h"

class playGround : public gameNode
{
private:

	player* _player;
	Ui* _ui;
	title* _title;
	village* _village;
	dungeon* _dungeon;
	testMap* _tm;

public:
	playGround();
	~playGround();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

