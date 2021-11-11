#pragma once
//#include "gameNode.h"
#include "npcNode.h"


//npc
#include "npcBlackSmith.h"
#include "npcTownHall.h"

struct NpcPosition
{
	float x;
	float y;
	D2D1_RECT_F rc;
	int kind;
};

enum NpcKind
{
	BLACKSMITH,
	TOWNHALL,
	SKILL
};


class npcManager
	//public npcNode
{
	//�������� NPC
	vector<npcNode*>									arrNpcs;
	vector<npcNode*>::iterator							iterNpcs;

	//NPC ��ġ ����
	vector<NpcPosition>									arrNpcPosition;
	vector<NpcPosition>::iterator						iterNpcPosition;

	//�����
	NpcPosition _NpcPosition;
	int _num;

	//NPC ���
	npcBlackSmith _npcBlackSmith;
	npcTownHall _npcTownHall;


public:

	HRESULT init();
	void release();
	void update();
	void render();
	void renderInteraction();

	//////////////////////////
	//NPC ��ġ �� ���� ����
	void setVillageNpc();
	void setClearNpc() { arrNpcs.clear(); arrNpcPosition.clear(); }

	int getNpcNum() { return arrNpcs.size(); }
	float getNpcX(int num) { return arrNpcPosition[num].x; }
	float getNpcY(int num) { return arrNpcPosition[num].y; }
	D2D1_RECT_F getNpcRc(int num) { return arrNpcPosition[num].rc; }
	int getNpcKind(int num) { return arrNpcPosition[num].kind; }

	void setInteraction(int num, bool b = false) { arrNpcs[num]->setInteraction(b); }
	bool getInteraction(int num) { return arrNpcs[num]->getInteraction(); }

	//npc ������ �̿�
	void setPlayerGold(int gold) { _npcBlackSmith.setPlayerGold(gold); }
	void setPlayerOre(int Ore) { _npcTownHall.setPlayerOre(Ore); }
	int getBlackSmithGold(int num) { return _npcBlackSmith.getBlackSmithGold(num); }
	void setBlackSmithUpgrade(int num) { _npcBlackSmith.setUpgrade(num); }
	float getBlackSmithUpgardeData(int num) { return _npcBlackSmith.getUpgradeData(num); }
	float getBlackSmithUpgardeDataLevel(int num) { return _npcBlackSmith.getUpgradeDataLevel(num); }


	int getNpcLevel(int num) { return arrNpcs[num]->getNpcLevel(); }
	void setChat(int num) { arrNpcs[num]->setChat(true); }

	int getPlayerOre() { return _npcTownHall.getPlayerOre(); }
	void upgradeCheck() { _npcTownHall.setUpgradeCheck(); }

	void setBlackSmithLevel(int level) { _npcBlackSmith.setBlackSmithLevel(level); }
	int getBlackSmithLevel() { return _npcTownHall.getBlackSmithLevel(); }

};

