#pragma once

enum itemKind
{
	HAVING,
	HP,
	MP,
	GOLD,
	ORE,
	KEY,
	POSION
};

struct potion
{
	//포션 최대치
	int maxHave;
	//포션 개수
	int crrentHave;
	//포션 회복량
	int recovreyValueHP;
	int recovreyValueMP;

};

//아이템 데이터 구조체
struct itemData
{
	int itemNum;
	string fileName;
	string itemName;
	int indexX;
	int indexY;
	string account;
	string setName;
	int kind;
	int value;

	float max_hp;
	float max_mp;
	float hp_regen;
	float attack_dmg;
	float armor;
	float magic_regist;

};

class item
{
private:
	//이미지 데이터
	image* _itemsImage;
	image* _itemsImage2;
	image* _accountBackGround;
	int _itemsImageWidth;
	int _itemsImageHight;
	//아이템 데이터
	vector<itemData>								arrItems;
	vector<itemData>::iterator						iterItems;
	//연산용
	itemData _items;

public:
	item();
	~item();

	/////////////////////////////////////////////

	//이미지 이름으로 이미지 파일 경로 찾기
	image* findItemImage(string fileName);

	//아이템 이름으로 데이터 찾기
	itemData findItem(string itemName);

	//아이템 번호로 데이터 찾기
	itemData findItem(int itemNum);

	//아이템 이미지 랜더링 하기
	void renderItemImage(float x, float y, string fileName, int indexX, int indexY, float magnification = 1.0f);

	//아이템 이름 랜더링
	void renderItemName(float x, float y, float width, float height, string itemName);

	//아이템 설명 랜더링
	void renderItemAccount(float x, float y, float width, float height, string itemAccount);

	//아이템 설명 뒷 배경 랜더링
	void renderItemAccountBackGround(float x, float y, float width, float height);
};
