#pragma once
#include "singletonBase.h"
#include "item.h"


class itemManager : public singletonBase<itemManager>
{
private:

	item _item;
	itemData _itemData;

	struct itemDataSet
	{
		//ǥ�õ� ��ǥ
		int x;
		int y;
		//������ �̸�
		string str;
		//����
		float magnification;
		//������ ����
		bool render;
		//������ ������
		itemData itemData;
	};



	itemDataSet _itemDataSet;
	itemData _descriptionData;

	vector<itemDataSet>									arrItems;
	vector<itemDataSet>::iterator						iterItems;

	vector<itemDataSet>									arrItemInventory;
	vector<itemDataSet>::iterator						iterItemInventory;

	//���� ������
	ID2D1SolidColorBrush* customBrush;
	ID2D1SolidColorBrush* defaultBrush;

	string _description;
	bool _renderDescription;
	bool _renderDescriptionInventory;
	float _descriptionX;
	float _descriptionY;

	//��ȣ�ۿ�
	image* _interaction;
	float _testX;
	float _testY;
	bool _npcBool;
	bool _itemBool;
	int _interactionKind;
	int _interactionIndexX;
	float _testTime;
	float _nowTime;
	//����
	image* _shop;
	image* _shop2;


public:
	itemManager() {};
	~itemManager() {};

	HRESULT init();
	void release();
	void update();
	void render();
	void renderInventory();


	void renderInteraction();

	void renderDescription();
	void renderDescriptionInventory();


	////////////////////////////////////////////////////////////////
	// ȭ�鿡 �������� �߰�, ��ġ�� ��ǥ �߽�
	// x��ǥ, y��ǥ, ������ �̸�, Ȯ�� ����, ������ ����
	void addItemCenter(int x, int y, string str, float magnification = 1.0F, bool render = true);
	void addItemCenter(int x, int y, int itemNum, float magnification = 1.0F, bool render = true);
	void addItemCenter(float x, float y, itemData data, float magnification = 1.0F, bool render = true);
	void addItemCenterInventory(float x, float y, itemData data, float magnification = 1.0F, bool render = true);


	//���߿� ����ü ��ȯ�� �ؾ��� ������ ������ �ޱ�
	itemData getItemData(int num) { return arrItems[num].itemData; }
	itemData getItemDataInventory(int num) { return arrItemInventory[num].itemData; }


	//������ ��� ������ ���� ���߿� ����
	//vector<itemData> getItemList();

	//�߰��� ������ ����
	void deletItem(int x, int y, string str);
	void deletItem(int x, int y, int itemNum);

	void deletItem(int num) { arrItems.erase(arrItems.begin() + num); }

	//�߰��� ��� ������ ����
	void deletAllItem() { arrItems.clear(); }
	void deletAllItemInventory() { arrItemInventory.clear(); }


	//�浹 ó����
	int getAllItemNum() { return arrItems.size(); }
	float getItemX(int num) { iterItems = arrItems.begin(); return iterItems[num].x; }
	float getItemY(int num) { iterItems = arrItems.begin(); return iterItems[num].y; }
	//�κ��丮��
	int getAllItemNumInventory() { return arrItemInventory.size(); }
	float getItemXInventory(int num) { iterItemInventory = arrItemInventory.begin(); return iterItemInventory[num].x; }
	float getItemYInventory(int num) { iterItemInventory = arrItemInventory.begin(); return iterItemInventory[num].y; }

	//��ȣ�ۿ�
	void setInteractionNpc(float x, float y, int kind);
	void setInteractionNpc(bool b = false) { _npcBool = b; }

	void setInteractionItem(float x, float y, int kind);
	void setInteractionItem(bool b = false) { _itemBool = b; }


	//���� ������
	void setDescription(float x, float y, itemData data);
	void setDescription(bool b = false) { _renderDescription = b; }
	void setDescriptionInventory(float x, float y, itemData data);
	void setDescriptionInventory(bool b = false) { _renderDescriptionInventory = b; }


	//���� �̹��� ������
	void renderShop(float destX, float destY, float destWidth, float destHeight, float sourX, float sourY, float sourWidth, float sourHeight, float opacity = 1.0f);
	void renderShop2(float destX, float destY, float destWidth, float destHeight, float opacity = 1.0f);


};

