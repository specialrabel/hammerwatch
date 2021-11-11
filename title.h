#pragma once
#include "gameNode.h"
#include "Ui.h"
#include "MouseCursor.h"

struct BTN
{
	image* img;
	D2D_RECT_F rc;
	int index;
	bool On;
};

class title : public gameNode
{
private:
	Ui* _ui;
	MouseCursor* _mouseCursor;

	image* tt;
	image* loading;
	image* loading2;

	image* bg;

	image* fg;

	image* mine;
	image* mine2;
	image* mine3;

	image* cloud;
	image* cloud2;

	image* thunder;
	image* thunder2;

	image* building;
	image* building2;
	image* building3;

	image* monster;
	image* monster2;

	image* tree;

	BTN profile;
	BTN start;
	BTN quit;

	image* profile2;
	   
	int _monsterIndex, _monster2Index, _thunderIndex, _thunder2Index, _count, _loadingIndex, _loadingCount;
	bool _roop, _thunderEND, _monster, _loadingVal, _onMenu, _inMenu;
	float _loadingOpacity, _menuOpacity;
public:
	title() {};
	~title() {};

	HRESULT init();
	void release();
	void update();
	void render();
};

