#pragma once
#include "gameNode.h"
#include "item.h"

#define DfXRevise  45
#define DfYRevise  93


class player;
struct PLAYER;

class menu :
	public gameNode
{

private:
	//�÷��̾� ����
	player* _player;

	float _x, _y;


	PLAYER* _playerData;

	enum SEARCH
	{
		Index0,
		Index1,
		Index2,
		Index3,
		IndexLeft,
		IndexRight,
		IndexHelmet,
		IndexArmor,
		IndexShoes
	};

	//��� �̹���
	image* _swordGreenImage;
	image* _swordGoldImage;
	image* _lanceGreenImage;
	image* _lanceGoldImage;
	image* _boomerangGreenImage;
	image* _boomerangGoldImage;
	image* _staffGreenImage;
	image* _staffGoldImage;
	image* _helmetGreenImage;
	image* _helmetGoldImage;
	image* _armorGreenImage;
	image* _armorGoldImage;
	image* _shoesGreenImage;
	image* _shoesGoldImage;

	image* _greenOilImage;
	image* _goldOilImage;

	//�Ŵ�
	bool _menuShow;
	bool _menuMain;
	bool _menuItems;
	bool _menuEquipWeapon;
	bool _menuEquipArmour;
	bool _menuOils;
	bool _menuOilUse;

	//������ ��� ���
	bool _dropItem;
	int _dropType;
	int _dropColor;
	int _dropDurability;

	int _menuNum;

	//�κ��丮
	int _oilKindNum;
	int _itemKind;
	int _colorKind;
	int _oldItemKind;
	int _oldColorKind;


	int _itemType[4];
	int _itemColor[4];
	int _itemIndex;
	int _itemDurability[4];
	int _oil[7];
	int _oilHaving[7];
	int _oilIndex;
	int _oilSearch[7];
	int _itemHaving;
	int _search[9];

	int _weapon_left_type;        //�޼չ��� Ÿ��
	int _weapon_left_color;       //�޼չ��� ����
	int _weapon_left_durability;

	int _weapon_right_type;       //�����չ��� Ÿ��
	int _weapon_right_color;      //�����չ��� ����
	int _weapon_right_durability;

	int _helmet_color;            //���� ����
	int _helmet_durability;
	int _armor_color;             //���� ����
	int _armor_durability;
	int _shoes_color;             //�Ź� ����
	int _shoes_durability;

	//�̹���
	image* _menuBackGround;
	image* _menuHeader;
	image* _menuFooter;
	image* _menuHighlight;
	WCHAR str[128];
	ID2D1SolidColorBrush* blueBrush;
	ID2D1SolidColorBrush* whiteBrush;


	//����
	int _sizeY;
	int _menuSelect;
	float _textX, _textY;


public:

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
	///////////////////////

	void linkPlayerClass(player* player) { _player = player; }

	void updateMain();
	void updateItems();
	void updateOils();
	void updateEquipWeapon();
	void updateEquipArmour();
	void updateOilUse();

	void renderMain();
	void renderItems();
	void renderOils();
	void renderEquipWeapon();
	void renderEquipArmour();
	void renderOilUse();

	//�÷��̾�� ��ȣ�ۿ�
	bool checkPickUp(int type, int color, int durability);


	//�޴� ���� �ݱ� ȿ��
	void menuShow();
	void menuCoverUp();

	//�÷��̾� ��� ������ ����
	void changeEquipLeft();
	void changeEquipRight();
	void changeEquipHelmet();
	void changeEquipArmor();
	void changeEquipShoes();

	//���� ������� ������ ��ȭ
	void changeItem();

	//������ �̹��� ������
	void renderItems(int x, int y, int type, int color, int durability);
	//�÷��̾� ��� ������ Ȯ��
	void checkItems();

	//������ ��� ����
	bool getdropItem() { return _dropItem; }
	void setdropItemF() { _dropItem = false; }

	void dropItem();

	int dropType() { return _dropType; }
	int dropColor() { return _dropColor; }
	int dropDurability() { return _dropDurability; }



	//void testRender();
};

