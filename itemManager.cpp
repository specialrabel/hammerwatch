#include "stdafx.h"
#include "itemManager.h"

HRESULT itemManager::init()
{
	_interaction = new image;
	_interaction->D_Init(L"image/interaction/interaction.png", 80, 16, 5, 1);
	_shop = new image;
	_shop->D_Init(L"image/interaction/shopUi.png", 100, 50, 4, 2);
	_shop2 = new image;
	_shop2->D_Init(L"image/interaction/shopUi2.png", 1079, 129, 1, 1);

	_npcBool = false;
	_itemBool = false;
	_interactionIndexX = 3;
	customBrush = D2DMANAGER->CreateBrush(0xFFA400, 1);
	defaultBrush = D2DMANAGER->CreateBrush(0x000000, 0);


	return S_OK;
}

void itemManager::release()
{
	_interaction->release();

}

void itemManager::update()
{

}

void itemManager::render()
{
	//추가된 아이템들 화면에 랜더링
	for (iterItems = arrItems.begin(); iterItems != arrItems.end(); ++iterItems)
	{
		if (iterItems->render)
		{
			_item.renderItemImage(
				iterItems->x,
				iterItems->y,
				iterItems->itemData.fileName,
				iterItems->itemData.indexX,
				iterItems->itemData.indexY,
				iterItems->magnification
			);
		}
	}


	renderDescription();

	renderInteraction();

}

void itemManager::renderInventory()
{

	//인벤토리 아이템 랜더링
	for (iterItemInventory = arrItemInventory.begin(); iterItemInventory != arrItemInventory.end(); ++iterItemInventory)
	{
		if (iterItemInventory->render)
		{
			_item.renderItemImage(
				iterItemInventory->x,
				iterItemInventory->y,
				iterItemInventory->itemData.fileName,
				iterItemInventory->itemData.indexX,
				iterItemInventory->itemData.indexY,
				iterItemInventory->magnification
			);
		}
	}

	//아이템 설명문 랜더링
	renderDescriptionInventory();

}

void itemManager::addItemCenter(int x, int y, string str, float magnification, bool render)
{
	_itemDataSet.itemData = _item.findItem(str);

	_itemDataSet.x = x;
	_itemDataSet.y = y;
	_itemDataSet.magnification = magnification;
	_itemDataSet.render = render;
	_itemDataSet.str = str;

	arrItems.push_back(_itemDataSet);
}

void itemManager::addItemCenter(int x, int y, int itemNum, float magnification, bool render)
{
	_itemDataSet.itemData = _item.findItem(itemNum);

	_itemDataSet.x = x;
	_itemDataSet.y = y;
	_itemDataSet.str = _itemDataSet.itemData.itemName;
	_itemDataSet.magnification = magnification;
	_itemDataSet.render = render;

	arrItems.push_back(_itemDataSet);
}

void itemManager::addItemCenter(float x, float y, itemData data, float magnification, bool render)
{
	_itemDataSet.itemData = data;
	_itemDataSet.x = x;
	_itemDataSet.y = y;
	_itemDataSet.str = _itemDataSet.itemData.itemName;
	_itemDataSet.magnification = magnification;
	_itemDataSet.render = render;

	arrItems.push_back(_itemDataSet);
}

void itemManager::addItemCenterInventory(float x, float y, itemData data, float magnification, bool render)
{
	_itemDataSet.itemData = data;
	_itemDataSet.x = x;
	_itemDataSet.y = y;
	_itemDataSet.str = _itemDataSet.itemData.itemName;
	_itemDataSet.magnification = magnification;
	_itemDataSet.render = render;

	arrItemInventory.push_back(_itemDataSet);
}

void itemManager::deletItem(int x, int y, string str)
{
	//아이템 찾기
	for (iterItems = arrItems.begin(); iterItems != arrItems.end(); ++iterItems)
	{
		//이름으로 먼저 확인
		if (iterItems->str == str)
		{
			//좌표값 확인
			if (!(iterItems->x == x)) continue;
			if (!(iterItems->y == y)) continue;

			//모두 일치할 경우 삭제
			arrItems.erase(iterItems);
			break;
		}
	}
}

void itemManager::deletItem(int x, int y, int itemNum)
{
	_itemData = _item.findItem(itemNum);
	string str = _itemData.itemName;

	//아이템 찾기
	for (iterItems = arrItems.begin(); iterItems != arrItems.end(); ++iterItems)
	{
		//이름으로 먼저 확인
		if (iterItems->str == str)
		{
			//좌표값 확인
			if (!(iterItems->x == x)) continue;
			if (!(iterItems->y == y)) continue;

			//모두 일치할 경우 삭제
			arrItems.erase(iterItems);
			break;
		}
	}

}

void itemManager::setInteractionNpc(float x, float y, int kind)
{
	_testX = x;
	_testY = y;
	_interactionKind = kind;
	_npcBool = true;

}

void itemManager::setInteractionItem(float x, float y, int kind)
{
	_testX = x;
	_testY = y;
	_interactionKind = kind;
	_itemBool = true;

}

//상호작용 이미지 랜더
void itemManager::renderInteraction()
{

	if (_npcBool)
	{

		_interaction->Frame_scale_start(_testX, _testY, 3, 3);

		_interaction->FrameRender(_testX, _testY, 0, 0);

		_interaction->scale_end();

	}
	if (_itemBool)
	{
		_interaction->Frame_scale_start(_testX, _testY, 3, 3);

		_interaction->FrameRender(_testX, _testY, _interactionIndexX, 0);

		_interaction->scale_end();

		//1초마다 랜더링 이미지 변경
		_nowTime = TIMEMANAGER->getWorldTime();

		if (_nowTime - _testTime > 1)
		{
			_testTime = TIMEMANAGER->getWorldTime();
			if (_interactionIndexX == 3)
			{
				_interactionIndexX = 4;
			}
			else
			{
				_interactionIndexX = 3;
			}
		}
	}
}

void itemManager::renderDescription()
{
	if (_renderDescription)
	{
		int lineHeight = _descriptionData.account.length();


		int width = 200;
		int height = 52 + 12 * ((lineHeight / 25) + 1);

		float cam_x = CAMERAMANAGER->get_camera_x();
		float cam_y = CAMERAMANAGER->get_camera_y();

		//뒷 배경 생성
		D2D1_RECT_F rc = D2DMANAGER->RectMake(
			_descriptionX - 2,
			_descriptionY - 2,
			width + 4,
			height + 4);
		D2DMANAGER->Rectangle(customBrush, customBrush, rc);
		_item.renderItemAccountBackGround(_descriptionX, _descriptionY,
			width, height);

		//아이템 이름 랜더링
		_item.renderItemName(_descriptionX + 5 - cam_x, _descriptionY + 5 - cam_y,
			width - 5, height, _descriptionData.itemName);

		//아이템 설명 랜더링
		_item.renderItemAccount(_descriptionX + 5 - cam_x, _descriptionY + 40 - cam_y,
			width - 5, height, _descriptionData.account);
	}

}

void itemManager::renderDescriptionInventory()
{

	if (_renderDescriptionInventory)
	{
		int lineHeight = _descriptionData.account.length();


		int width = 200;
		int height = 52 + 12 * ((lineHeight / 25) + 1);

		float cam_x = CAMERAMANAGER->get_camera_x();
		float cam_y = CAMERAMANAGER->get_camera_y();

		//뒷 배경 생성
		D2D1_RECT_F rc = D2DMANAGER->RectMake(
			_descriptionX - 2,
			_descriptionY - 2,
			width + 4,
			height + 4);
		D2DMANAGER->Rectangle(customBrush, customBrush, rc);
		_item.renderItemAccountBackGround(_descriptionX, _descriptionY,
			width, height);

		//아이템 이름 랜더링
		_item.renderItemName(_descriptionX + 5 - cam_x, _descriptionY + 5 - cam_y,
			width - 5, height, _descriptionData.itemName);

		//아이템 설명 랜더링
		_item.renderItemAccount(_descriptionX + 5 - cam_x, _descriptionY + 40 - cam_y,
			width - 5, height, _descriptionData.account);
	}

}

void itemManager::setDescription(float x, float y, itemData data)
{
	_descriptionData = data;

	_descriptionX = x;
	_descriptionY = y;
	_renderDescription = true;

}

void itemManager::setDescriptionInventory(float x, float y, itemData data)
{

	_descriptionData = data;

	_descriptionX = x;
	_descriptionY = y;
	_renderDescriptionInventory = true;

}

void itemManager::renderShop(float destX, float destY, float destWidth, float destHeight, float sourX, float sourY, float sourWidth, float sourHeight, float opacity)
{
	_shop->render(destX, destY, destWidth, destHeight, sourX, sourY, sourWidth, sourHeight, opacity);
}

void itemManager::renderShop2(float destX, float destY, float destWidth, float destHeight, float opacity)
{
	_shop2->render(destX, destY, destWidth, destHeight, 0, 0, 1079, 129, opacity);
}
