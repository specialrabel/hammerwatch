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
		//표시될 좌표
		int x;
		int y;
		//아이템 이름
		string str;
		//배율
		float magnification;
		//랜더링 여부
		bool render;
		//아이템 데이터
		itemData itemData;
	};



	itemDataSet _itemDataSet;
	itemData _descriptionData;

	vector<itemDataSet>									arrItems;
	vector<itemDataSet>::iterator						iterItems;

	vector<itemDataSet>									arrItemInventory;
	vector<itemDataSet>::iterator						iterItemInventory;

	//설명문 변수들
	ID2D1SolidColorBrush* customBrush;
	ID2D1SolidColorBrush* defaultBrush;

	string _description;
	bool _renderDescription;
	bool _renderDescriptionInventory;
	float _descriptionX;
	float _descriptionY;

	//상호작용
	image* _interaction;
	float _testX;
	float _testY;
	bool _npcBool;
	bool _itemBool;
	int _interactionKind;
	int _interactionIndexX;
	float _testTime;
	float _nowTime;
	//상점
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
	// 화면에 아이템을 추가, 위치는 좌표 중심
	// x좌표, y좌표, 아이템 이름, 확대 배율, 랜더링 여부
	void addItemCenter(int x, int y, string str, float magnification = 1.0F, bool render = true);
	void addItemCenter(int x, int y, int itemNum, float magnification = 1.0F, bool render = true);
	void addItemCenter(float x, float y, itemData data, float magnification = 1.0F, bool render = true);
	void addItemCenterInventory(float x, float y, itemData data, float magnification = 1.0F, bool render = true);


	//나중에 구조체 반환을 해야함 아이템 데이터 받기
	itemData getItemData(int num) { return arrItems[num].itemData; }
	itemData getItemDataInventory(int num) { return arrItemInventory[num].itemData; }


	//생성된 모든 아이템 정보 나중에 구현
	//vector<itemData> getItemList();

	//추가된 아이템 제거
	void deletItem(int x, int y, string str);
	void deletItem(int x, int y, int itemNum);

	void deletItem(int num) { arrItems.erase(arrItems.begin() + num); }

	//추가된 모든 아이템 제거
	void deletAllItem() { arrItems.clear(); }
	void deletAllItemInventory() { arrItemInventory.clear(); }


	//충돌 처리용
	int getAllItemNum() { return arrItems.size(); }
	float getItemX(int num) { iterItems = arrItems.begin(); return iterItems[num].x; }
	float getItemY(int num) { iterItems = arrItems.begin(); return iterItems[num].y; }
	//인벤토리용
	int getAllItemNumInventory() { return arrItemInventory.size(); }
	float getItemXInventory(int num) { iterItemInventory = arrItemInventory.begin(); return iterItemInventory[num].x; }
	float getItemYInventory(int num) { iterItemInventory = arrItemInventory.begin(); return iterItemInventory[num].y; }

	//상호작용
	void setInteractionNpc(float x, float y, int kind);
	void setInteractionNpc(bool b = false) { _npcBool = b; }

	void setInteractionItem(float x, float y, int kind);
	void setInteractionItem(bool b = false) { _itemBool = b; }


	//설명문 랜더링
	void setDescription(float x, float y, itemData data);
	void setDescription(bool b = false) { _renderDescription = b; }
	void setDescriptionInventory(float x, float y, itemData data);
	void setDescriptionInventory(bool b = false) { _renderDescriptionInventory = b; }


	//상점 이미지 랜더링
	void renderShop(float destX, float destY, float destWidth, float destHeight, float sourX, float sourY, float sourWidth, float sourHeight, float opacity = 1.0f);
	void renderShop2(float destX, float destY, float destWidth, float destHeight, float opacity = 1.0f);


};

