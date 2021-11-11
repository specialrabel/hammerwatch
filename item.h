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
	//���� �ִ�ġ
	int maxHave;
	//���� ����
	int crrentHave;
	//���� ȸ����
	int recovreyValueHP;
	int recovreyValueMP;

};

//������ ������ ����ü
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
	//�̹��� ������
	image* _itemsImage;
	image* _itemsImage2;
	image* _accountBackGround;
	int _itemsImageWidth;
	int _itemsImageHight;
	//������ ������
	vector<itemData>								arrItems;
	vector<itemData>::iterator						iterItems;
	//�����
	itemData _items;

public:
	item();
	~item();

	/////////////////////////////////////////////

	//�̹��� �̸����� �̹��� ���� ��� ã��
	image* findItemImage(string fileName);

	//������ �̸����� ������ ã��
	itemData findItem(string itemName);

	//������ ��ȣ�� ������ ã��
	itemData findItem(int itemNum);

	//������ �̹��� ������ �ϱ�
	void renderItemImage(float x, float y, string fileName, int indexX, int indexY, float magnification = 1.0f);

	//������ �̸� ������
	void renderItemName(float x, float y, float width, float height, string itemName);

	//������ ���� ������
	void renderItemAccount(float x, float y, float width, float height, string itemAccount);

	//������ ���� �� ��� ������
	void renderItemAccountBackGround(float x, float y, float width, float height);
};
