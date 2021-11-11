#pragma once
#include "npcNode.h"

#define DF_widthHalf	11
#define DF_scale		3
#define DF_elipse		96

class npcTownHall :
	public npcNode
{
private:

	image* _townHallImage;
	image* _shopUi1;
	image* _shopUi2;

	//위치
	float _x;
	float _y;
	D2D1_RECT_F _rc;
	WCHAR str[128];
	//렙은 1이상
	int _level;
	//상호작용시
	bool _interaction;

	int _blackSmithLevel;
	int _skillLevel;

	//
	int _playerOre;
	int _upgradeOre;


public:

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
	virtual void renderInteraction();

	virtual bool getInteraction() { return _interaction; }
	virtual void setInteraction(bool b = false) { _interaction = b; }
	virtual int getNpcLevel() { return _level; }

	//////////////

	D2D1_RECT_F getRC() { return _rc; }
	float getX() { return _x; }
	float getY() { return _y; }

	void setPlayerOre(int ore) { _playerOre = ore; }
	int getPlayerOre() { return _playerOre; }

	void setUpgradeCheck();
	int getBlackSmithLevel() { return _blackSmithLevel; }
};

