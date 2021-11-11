#include "stdafx.h"
#include "item.h"

item::item()
{

	_itemsImage = new image;
	_itemsImage->D_Init(L"image/item/items.png", 280, 294, 20, 21);
	_itemsImage2 = new image;
	_itemsImage2->D_Init(L"image/item/items_general.png", 160, 160, 10, 10);
	_accountBackGround = new image;
	_accountBackGround->D_Init(L"image/item/accountBackGround.png", 500, 500, 500, 500);
	//������ �̹��� ���
	IMAGEMANAGER->addFrameImage("items", L"image/item/items.png", 280, 294, 20, 21);
	IMAGEMANAGER->addFrameImage("items2", L"image/item/items.png", 160, 160, 10, 10);


	//������ ���� �߰� ���� �ʱ�ȭ
	_items.itemNum = 0000;
	_items.fileName = "items";
	_items.itemName = "NoData";
	_items.indexX = 0;
	_items.indexY = 0;
	_items.account = "NoData";
	_items.setName = "NoData";
	_items.kind = HAVING;
	_items.max_hp = 0;
	_items.max_mp = 0;
	_items.hp_regen = 0;
	_items.attack_dmg = 0;
	_items.armor = 0;
	_items.magic_regist = 0;


	arrItems.push_back(_items);

	_items.itemNum = 0001;
	_items.fileName = "items";
	_items.itemName = "������ �ƹķ�";
	_items.indexX = 2;
	_items.indexY = 0;
	_items.account = "+5 ��������";
	_items.setName = "NoData";
	_items.kind = HAVING;
	_items.max_hp = 0;
	_items.max_mp = 0;
	_items.hp_regen = 0;
	_items.attack_dmg = 0;
	_items.armor = 0;
	_items.magic_regist = 5;

	arrItems.push_back(_items);

	_items.itemNum = 0002;
	_items.fileName = "items";
	_items.itemName = "���ݼ����� ����";
	_items.indexX = 5;
	_items.indexY = 0;
	_items.account = "������ ���ø� 5�� ���� �̵� �ӵ��� 50% �����մϴ�.";
	_items.setName = "���ݼ����� ����";
	_items.kind = HAVING;
	_items.max_hp = 0;
	_items.max_mp = 0;
	_items.hp_regen = 0;
	_items.attack_dmg = 0;
	_items.armor = 0;
	_items.magic_regist = 0;


	arrItems.push_back(_items);

	_items.itemNum = 0003;
	_items.fileName = "items";
	_items.itemName = "��ε� �ҵ�";
	_items.indexX = 1;
	_items.indexY = 10;
	_items.account = "+10 ���ݷ�";
	_items.setName = "NoData";
	_items.kind = HAVING;
	_items.max_hp = 0;
	_items.max_mp = 0;
	_items.hp_regen = 0;
	_items.attack_dmg = 10;
	_items.armor = 0;
	_items.magic_regist = 0;


	arrItems.push_back(_items);

	_items.itemNum = 0004;
	_items.fileName = "items";
	_items.itemName = "ü�θ���";
	_items.indexX = 9;
	_items.indexY = 0;
	_items.account = "+5 ����";
	_items.setName = "NoData";
	_items.kind = HAVING;
	_items.max_hp = 0;
	_items.max_mp = 0;
	_items.hp_regen = 0;
	_items.attack_dmg = 0;
	_items.armor = 5;
	_items.magic_regist = 0;


	arrItems.push_back(_items);

	_items.itemNum = 0005;
	_items.fileName = "items";
	_items.itemName = "��� ��Ʋ��";
	_items.indexX = 1;
	_items.indexY = 5;
	_items.account = "+15 ü��";
	_items.setName = "NoData";
	_items.kind = HAVING;
	_items.max_hp = 15;
	_items.max_mp = 0;
	_items.hp_regen = 0;
	_items.attack_dmg = 0;
	_items.armor = 0;
	_items.magic_regist = 0;


	arrItems.push_back(_items);
	_items.itemNum = 0006;
	_items.fileName = "items";
	_items.itemName = "������ �κ�";
	_items.indexX = 4;
	_items.indexY = 7;
	_items.account = "+20 ����";
	_items.setName = "NoData";
	_items.kind = HAVING;
	_items.max_hp = 0;
	_items.max_mp = 20;
	_items.hp_regen = 0;
	_items.attack_dmg = 0;
	_items.armor = 0;
	_items.magic_regist = 0;


	arrItems.push_back(_items);

	arrItems.push_back(_items);
	_items.itemNum = 0007;
	_items.fileName = "items";
	_items.itemName = "�ǰ��� ����";
	_items.indexX = 6;
	_items.indexY = 6;
	_items.account = "+0.2 ü�����";
	_items.setName = "NoData";
	_items.kind = HAVING;
	_items.max_hp = 0;
	_items.max_mp = 0;
	_items.hp_regen = 0.2;
	_items.attack_dmg = 0;
	_items.armor = 0;
	_items.magic_regist = 0;


	arrItems.push_back(_items);


	//������2 �� �̹���
	//��� ������
	_items.itemNum = 1000;
	_items.fileName = "items2";
	_items.itemName = "��ȭ1";
	_items.indexX = 0;
	_items.indexY = 0;
	_items.account = "��ȭ1";
	_items.setName = "NoData";
	_items.kind = GOLD;
	_items.value = 1;

	arrItems.push_back(_items);

	_items.itemNum = 1001;
	_items.fileName = "items2";
	_items.itemName = "��ȭ2";
	_items.indexX = 1;
	_items.indexY = 0;
	_items.account = "��ȭ2";
	_items.setName = "NoData";
	_items.kind = GOLD;
	_items.value = 5;

	arrItems.push_back(_items);

	_items.itemNum = 1002;
	_items.fileName = "items2";
	_items.itemName = "��ȭ3";
	_items.indexX = 2;
	_items.indexY = 0;
	_items.account = "��ȭ3";
	_items.setName = "NoData";
	_items.kind = GOLD;
	_items.value = 10;

	arrItems.push_back(_items);

	_items.itemNum = 1003;
	_items.fileName = "items2";
	_items.itemName = "��ȭ1";
	_items.indexX = 3;
	_items.indexY = 0;
	_items.account = "��ȭ1";
	_items.setName = "NoData";
	_items.kind = GOLD;
	_items.value = 2;

	arrItems.push_back(_items);

	_items.itemNum = 1004;
	_items.fileName = "items2";
	_items.itemName = "��ȭ2";
	_items.indexX = 4;
	_items.indexY = 0;
	_items.account = "��ȭ2";
	_items.setName = "NoData";
	_items.kind = GOLD;
	_items.value = 10;

	arrItems.push_back(_items);

	_items.itemNum = 1005;
	_items.fileName = "items2";
	_items.itemName = "��ȭ3";
	_items.indexX = 5;
	_items.indexY = 0;
	_items.account = "��ȭ3";
	_items.setName = "NoData";
	_items.kind = GOLD;
	_items.value = 20;

	arrItems.push_back(_items);

	_items.itemNum = 1006;
	_items.fileName = "items2";
	_items.itemName = "��ȭ1";
	_items.indexX = 6;
	_items.indexY = 0;
	_items.account = "��ȭ1";
	_items.setName = "NoData";
	_items.kind = GOLD;
	_items.value = 3;

	arrItems.push_back(_items);

	_items.itemNum = 1007;
	_items.fileName = "items2";
	_items.itemName = "��ȭ2";
	_items.indexX = 7;
	_items.indexY = 0;
	_items.account = "��ȭ2";
	_items.setName = "NoData";
	_items.kind = GOLD;
	_items.value = 15;

	arrItems.push_back(_items);

	_items.itemNum = 1008;
	_items.fileName = "items2";
	_items.itemName = "��ȭ3";
	_items.indexX = 8;
	_items.indexY = 0;
	_items.account = "��ȭ3";
	_items.setName = "NoData";
	_items.kind = GOLD;
	_items.value = 30;

	arrItems.push_back(_items);

	_items.itemNum = 1009;
	_items.fileName = "items2";
	_items.itemName = "����";
	_items.indexX = 9;
	_items.indexY = 0;
	_items.account = "����";
	_items.setName = "NoData";
	_items.kind = ORE;
	_items.value = 1;

	arrItems.push_back(_items);


	//�Ҹ� ������
	_items.itemNum = 1010;
	_items.fileName = "items2";
	_items.itemName = "���";
	_items.indexX = 0;
	_items.indexY = 2;
	_items.account = "���";
	_items.setName = "NoData";
	_items.kind = HP;
	_items.value = 10;

	arrItems.push_back(_items);

	_items.itemNum = 1011;
	_items.fileName = "items2";
	_items.itemName = "������";
	_items.indexX = 1;
	_items.indexY = 2;
	_items.account = "������";
	_items.setName = "NoData";
	_items.kind = HP;
	_items.value = 25;

	arrItems.push_back(_items);

	_items.itemNum = 1012;
	_items.fileName = "items2";
	_items.itemName = "ġ��";
	_items.indexX = 2;
	_items.indexY = 2;
	_items.account = "ġ��";
	_items.setName = "NoData";
	_items.kind = HP;
	_items.value = 50;

	arrItems.push_back(_items);

	_items.itemNum = 1013;
	_items.fileName = "items2";
	_items.itemName = "����";
	_items.indexX = 3;
	_items.indexY = 2;
	_items.account = "����";
	_items.setName = "NoData";
	_items.kind = HP;
	_items.value = 75;

	arrItems.push_back(_items);

	_items.itemNum = 1014;
	_items.fileName = "items2";
	_items.itemName = "���";
	_items.indexX = 4;
	_items.indexY = 2;
	_items.account = "���";
	_items.setName = "NoData";
	_items.kind = HP;
	_items.value = 100;

	arrItems.push_back(_items);

	_items.itemNum = 1015;
	_items.fileName = "items2";
	_items.itemName = "��������(��)";
	_items.indexX = 5;
	_items.indexY = 2;
	_items.account = "��������(��)";
	_items.setName = "NoData";
	_items.kind = MP;
	_items.value = 15;

	arrItems.push_back(_items);

	_items.itemNum = 1016;
	_items.fileName = "items2";
	_items.itemName = "��������(��)";
	_items.indexX = 6;
	_items.indexY = 2;
	_items.account = "��������(��)";
	_items.setName = "NoData";
	_items.kind = MP;
	_items.value = 30;

	arrItems.push_back(_items);

	_items.itemNum = 1017;
	_items.fileName = "items2";
	_items.itemName = "��������(��)";
	_items.indexX = 7;
	_items.indexY = 2;
	_items.account = "��������(��)";
	_items.setName = "NoData";
	_items.kind = MP;
	_items.value = 50;

	arrItems.push_back(_items);

	_items.itemNum = 1020;
	_items.fileName = "items2";
	_items.itemName = "ũ����Ż";
	_items.indexX = 0;
	_items.indexY = 4;
	_items.account = "ũ����Ż";
	_items.setName = "NoData";
	_items.kind = GOLD;
	_items.value = 50;

	arrItems.push_back(_items);

	_items.itemNum = 1021;
	_items.fileName = "items2";
	_items.itemName = "ũ����Ż(��)";
	_items.indexX = 1;
	_items.indexY = 4;
	_items.account = "ũ����Ż";
	_items.setName = "NoData";
	_items.kind = GOLD;
	_items.value = 100;

	arrItems.push_back(_items);

	_items.itemNum = 1022;
	_items.fileName = "items2";
	_items.itemName = "Ȳ��ũ����Ż";
	_items.indexX = 2;
	_items.indexY = 4;
	_items.account = "Ȳ��ũ����Ż";
	_items.setName = "NoData";
	_items.kind = GOLD;
	_items.value = 75;

	arrItems.push_back(_items);

	_items.itemNum = 1023;
	_items.fileName = "items2";
	_items.itemName = "Ȳ��ũ����Ż(��)";
	_items.indexX = 3;
	_items.indexY = 4;
	_items.account = "Ȳ��ũ����Ż(��)";
	_items.setName = "NoData";
	_items.kind = GOLD;
	_items.value = 150;

	arrItems.push_back(_items);

	_items.itemNum = 1024;
	_items.fileName = "items2";
	_items.itemName = "����ũ����Ż";
	_items.indexX = 4;
	_items.indexY = 4;
	_items.account = "����ũ����Ż";
	_items.setName = "NoData";
	_items.kind = GOLD;
	_items.value = 100;

	arrItems.push_back(_items);

	_items.itemNum = 1025;
	_items.fileName = "items2";
	_items.itemName = "����ũ����Ż(��)";
	_items.indexX = 5;
	_items.indexY = 4;
	_items.account = "����ũ����Ż(��)";
	_items.setName = "NoData";
	_items.kind = GOLD;
	_items.value = 200;

	arrItems.push_back(_items);

	_items.itemNum = 1026;
	_items.fileName = "items2";
	_items.itemName = "����";
	_items.indexX = 6;
	_items.indexY = 4;
	_items.account = "����";
	_items.setName = "NoData";
	_items.kind = POSION;
	_items.value = 1;

	arrItems.push_back(_items);

	_items.itemNum = 1030;
	_items.fileName = "items2";
	_items.itemName = "����Ű";
	_items.indexX = 0;
	_items.indexY = 6;
	_items.account = "����Ű";
	_items.setName = "NoData";
	_items.kind = KEY;
	_items.value = 1;

	arrItems.push_back(_items);

	_items.itemNum = 1031;
	_items.fileName = "items2";
	_items.itemName = "����Ű";
	_items.indexX = 1;
	_items.indexY = 6;
	_items.account = "����Ű";
	_items.setName = "NoData";
	_items.kind = KEY;
	_items.value = 2;

	arrItems.push_back(_items);

	_items.itemNum = 1032;
	_items.fileName = "items2";
	_items.itemName = "Ȳ��Ű";
	_items.indexX = 2;
	_items.indexY = 6;
	_items.account = "Ȳ��Ű";
	_items.setName = "NoData";
	_items.kind = KEY;
	_items.value = 3;

	arrItems.push_back(_items);

	_items.itemNum = 1033;
	_items.fileName = "items2";
	_items.itemName = "����Ű";
	_items.indexX = 3;
	_items.indexY = 6;
	_items.account = "����Ű";
	_items.setName = "NoData";
	_items.kind = KEY;
	_items.value = 4;

	arrItems.push_back(_items);


}

item::~item()
{
	_itemsImage->release();
	SAFE_DELETE(_itemsImage);

	_itemsImage2->release();
	SAFE_DELETE(_itemsImage2);

	_accountBackGround->release();
	SAFE_DELETE(_accountBackGround);

}

image* item::findItemImage(string fileName)
{
	if (fileName == "items")
	{
		return _itemsImage;
	}
	if (fileName == "items2")
	{
		return _itemsImage2;
	}

	return _itemsImage;
}

itemData item::findItem(string itemName)
{
	//������ �������� Ư�� �̸� ������ ã��
	for (iterItems = arrItems.begin(); iterItems != arrItems.end(); ++iterItems)
	{

		if (iterItems->itemName == itemName)
		{
			return *iterItems;
		}

	}
	//ã�� ���ߴٸ� 0�� ������ ��ȯ
	return iterItems[0];
}

itemData item::findItem(int itemNum)
{
	//������ �������� Ư�� �̸� ������ ã��
	for (iterItems = arrItems.begin(); iterItems != arrItems.end(); ++iterItems)
	{

		if (iterItems->itemNum == itemNum)
		{
			return *iterItems;
		}

	}
	//ã�� ���ߴٸ� 0�� ������ ��ȯ
	return iterItems[0];
}

void item::renderItemImage(float x, float y, string fileName, int indexX, int indexY, float magnification)
{
	image* image = findItemImage(fileName);

	//��ǥ �߽ɿ��� ������
	x = x - (image->getFrameHeight() / 2);
	y = y - (image->getFrameWidth() / 2);


	image->Frame_scale_start(x, y, magnification, magnification);

	if (fileName == "items2")
	{
		image->FrameRender(x, y, indexX, indexY + 1, 0.5F);
	}

	image->FrameRender(x, y, indexX, indexY, 1.0F);

	image->scale_end();

}

void item::renderItemName(float x, float y, float width, float height, string itemName)
{
	//string s = _items.itemName;
	string s = itemName;

	//string -> LPCWSTR ��ȯ
	int len;
	int slength = (int)s.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
	std::wstring r(buf);
	delete[] buf;
	wstring result = r;
	LPCWSTR t = result.c_str();

	ID2D1SolidColorBrush* whiteBrush = D2DMANAGER->CreateBrush(0xFFFFFF, 1.0f);

	D2DMANAGER->DrawTextD2DCenter(whiteBrush, L"Consolas", 20.0f, t,
		x,
		y,
		x + width,
		y + height);
}

void item::renderItemAccount(float x, float y, float width, float height, string itemAccount)
{

	//string s = _items.account;
	string s = itemAccount;

	//string -> LPCWSTR ��ȯ
	int len;
	int slength = (int)s.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
	std::wstring r(buf);
	delete[] buf;
	wstring result = r;
	LPCWSTR t = result.c_str();

	ID2D1SolidColorBrush* whiteBrush = D2DMANAGER->CreateBrush(0xFFFFFF, 1.0f);

	D2DMANAGER->DrawTextD2DCenter(whiteBrush, L"Consolas", 15.0f, t,
		x,
		y,
		x + width,
		y + height);

}

void item::renderItemAccountBackGround(float x, float y, float width, float height)
{
	_accountBackGround->render(x, y, width, height, 0, 0, width, height, 1.0F);
}


