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
	//플레이어 정보
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

	//장비 이미지
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

	//매뉴
	bool _menuShow;
	bool _menuMain;
	bool _menuItems;
	bool _menuEquipWeapon;
	bool _menuEquipArmour;
	bool _menuOils;
	bool _menuOilUse;

	//아이템 드롭 기능
	bool _dropItem;
	int _dropType;
	int _dropColor;
	int _dropDurability;

	int _menuNum;

	//인벤토리
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

	int _weapon_left_type;        //왼손무기 타입
	int _weapon_left_color;       //왼손무기 색상
	int _weapon_left_durability;

	int _weapon_right_type;       //오른손무기 타입
	int _weapon_right_color;      //오른손무기 색상
	int _weapon_right_durability;

	int _helmet_color;            //투구 색상
	int _helmet_durability;
	int _armor_color;             //갑옷 색상
	int _armor_durability;
	int _shoes_color;             //신발 색상
	int _shoes_durability;

	//이미지
	image* _menuBackGround;
	image* _menuHeader;
	image* _menuFooter;
	image* _menuHighlight;
	WCHAR str[128];
	ID2D1SolidColorBrush* blueBrush;
	ID2D1SolidColorBrush* whiteBrush;


	//계산용
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

	//플레이어와 상호작용
	bool checkPickUp(int type, int color, int durability);


	//메뉴 열기 닫기 효과
	void menuShow();
	void menuCoverUp();

	//플레이어 장비 데이터 적용
	void changeEquipLeft();
	void changeEquipRight();
	void changeEquipHelmet();
	void changeEquipArmor();
	void changeEquipShoes();

	//오일 사용으로 아이템 변화
	void changeItem();

	//아이템 이미지 랜더링
	void renderItems(int x, int y, int type, int color, int durability);
	//플레이어 장비 아이템 확인
	void checkItems();

	//아이템 드랍 구현
	bool getdropItem() { return _dropItem; }
	void setdropItemF() { _dropItem = false; }

	void dropItem();

	int dropType() { return _dropType; }
	int dropColor() { return _dropColor; }
	int dropDurability() { return _dropDurability; }



	//void testRender();
};

