#pragma once
//#include "gameNode.h"
#include "npcNode.h"

#define DF_widthHalf	11
#define DF_scale		3
#define DF_elipse		96

class npcBlackSmith :
	public npcNode
{
private:

	image* _blackSmithImage;
	image* _interactionImage;
	int _indexX;
	bool _interaction;

	//대장간 강화 레벨
	int _level;
	float _attack;
	float _armor;
	float _crit;
	float _speed;

	int _attackLevel;
	int _armorLevel;
	int _critLevel;
	int _speedLevel;

	int _upgradeGold;

	int _playerGold;

	//위치
	float _x;
	float _y;

	D2D1_RECT_F _rc;

	//랜더링 변수
	int _frame;
	bool _wait;
	bool _chat;
	WCHAR str[128];

public:

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
	virtual void renderInteraction();

	virtual bool getInteraction() { return _interaction; }
	virtual void setInteraction(bool b = false) { _interaction = b; }
	virtual int getNpcLevel() { return _level; }
	virtual void setChat(bool b = false) { _chat = b; }

	//////////////

	D2D1_RECT_F getRC() { return _rc; }
	float getX() { return _x; }
	float getY() { return _y; }

	int getBlackSmithGold(int num);
	void setPlayerGold(int gold) { _playerGold = gold; }
	void setUpgrade(int num);

	float getUpgradeData(int num);
	int getUpgradeDataLevel(int num);
	void setBlackSmithLevel(int level) { _level = level; }

};

