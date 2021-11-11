#pragma once
#include "gameNode.h"
#include "effect.h"

class player;
class mapTool;
class npcManager;
class enemyManager;
class Ui;


class collision
{
private:

	//충돌 객체
	player* _player;
	npcManager* _npcManager;
	mapTool* _mapTool;
	enemyManager* _enemy;
	Ui* _ui;

	D2D1_RECT_F temp;

	//연산변수
	bool _boolBlackSmith;
	bool _boolInn;


public:
	collision() {};
	~collision() {};

	// 맵 정보를 받아오기 위한 init 함수 
	virtual HRESULT init(image* stage);
	virtual void release();
	virtual void update();
	virtual void render();

	//Link용
	inline void Link_PlayerClass(player* player) { _player = player; }
	inline void Link_npcManagerClass(npcManager* npc) { _npcManager = npc; }
	inline void Link_mapToolClass(mapTool* map) { _mapTool = map; }
	inline void Link_enemyClass(enemyManager* _em) { _enemy = _em; }
	inline void Link_UiClass(Ui* ui) { _ui = ui; }


	// 충돌관리 함수
	void player_AND_CrossTiles();
	void player_AND_diagonalTiles();
	void player_AND_enemy();
	void playerBullet_AND_Anything();

	void enemy_AND_CrossTiles();
	void enemy_AND_diagonalTiles();

	//아이템과 NPC
	void player_AND_item();
	void player_AND_NPC();
	void inventory_AND_item();
	void player_AND_blackSmith();
	void player_AND_Inn();

};


