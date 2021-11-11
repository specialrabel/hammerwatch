#include "stdafx.h"
#include "npcManager.h"

HRESULT npcManager::init()
{
	_npcBlackSmith.init();
	_npcTownHall.init();

	return S_OK;
}

void npcManager::release()
{
	setClearNpc();
}

void npcManager::update()
{
}

void npcManager::render()
{
	//��ϵ� Npc ������
	for (iterNpcs = arrNpcs.begin(); iterNpcs != arrNpcs.end(); ++iterNpcs)
	{
		(*iterNpcs)->render();
	}
}

void npcManager::renderInteraction()
{
	//��ȣ�ۿ�� ������
	for (iterNpcs = arrNpcs.begin(); iterNpcs != arrNpcs.end(); ++iterNpcs)
	{
		if ((*iterNpcs)->getInteraction())
		{
			(*iterNpcs)->renderInteraction();
		}
	}
}

void npcManager::setVillageNpc()
{
	//�迭 �ʱ�ȭ
	arrNpcs.clear();
	arrNpcPosition.clear();

	//���� Npc ���
	arrNpcs.push_back((npcBlackSmith*)&_npcBlackSmith);
	_NpcPosition.rc = _npcBlackSmith.getRC();
	_NpcPosition.x = _npcBlackSmith.getX();
	_NpcPosition.y = _npcBlackSmith.getY();
	_NpcPosition.kind = BLACKSMITH;
	arrNpcPosition.push_back(_NpcPosition);

	arrNpcs.push_back((npcTownHall*)&_npcTownHall);
	_NpcPosition.rc = _npcTownHall.getRC();
	_NpcPosition.x = _npcTownHall.getX();
	_NpcPosition.y = _npcTownHall.getY();
	_NpcPosition.kind = TOWNHALL;
	arrNpcPosition.push_back(_NpcPosition);
}