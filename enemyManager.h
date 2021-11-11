#pragma once
#include "gameNode.h"
#include "enemy.h"
#include "bat.h"
#include "tick.h"
#include "skeleton.h"
#include "maggot.h"
#include "tileNode.h"
#include "tile.h"
#include <vector>

#define TILE_NUM_X 20
#define TILE_NUM_Y 20

class player;
class mapTool;

class enemyManager : public gameNode
{
private:
	typedef vector<enemy*>				Enemy_pool;
	typedef vector<enemy*>::iterator	pool_iter;

private:
	Enemy_pool _enemy_pool;
	pool_iter _pool_iter;
	player* _player;
	mapTool* _map;

	int current_index;
	int past_index;
	
	vector<int> reset_list;

	vector<tile*>			_vTotalList;
	vector<tile*>::iterator _viTotalList;

	//갈 수 있는 타일 담을 벡터
	vector<tile*>			_vOpenList;
	vector<tile*>::iterator _viOpenList;

	//가장 가까운 경로를 담을 벡터
	vector<tile*>			_vCloseList;
	vector<tile*>::iterator _viCloseList;

	tile* _startTile;
	tile* _endtile;
	tile* _currentTile;

	D2D1_RECT_F temp;
	D2D1_RECT_F destination;

	float update_count;
	bool _start;
	bool _FindPath;

public:
	enemyManager() {};
	~enemyManager() {};

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	inline void LinkPlayerClass(player* player) { _player = player; }
	inline void LinkMaptoolClass(mapTool* _mt) { _map = _mt; }

	vector<tile*> addOpenList(tile* currentTile, vector<tile*>& openlist);
	void pathFinder(tile* currentTile, vector<tile*>& openlist, vector<tile*>& closeList);

	void set_bats(float x, float y);
	void set_ticks(float x, float y);
	void set_skeletons(float x, float y);
	void set_maggots(float x, float y);

	void find_path();
	void find_player();
	void reset();
	void remove_enemy(int num);

	POINT PointMake(int x, int y);
	vector<enemy*> get_enemy() { return _enemy_pool; }


};

