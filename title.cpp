#include "stdafx.h"
#include "title.h"

HRESULT title::init()
{
	CAMERAMANAGER->init(0, 0);

	_ui = new Ui;
	_ui->init();

	_mouseCursor = new MouseCursor;
	_mouseCursor->init();

	_mouseCursor->setUiMemoryAdressLink(_ui);

	tt = new image;
	loading = new image;
	loading2 = new image;

	bg = new image;

	fg = new image;

	mine = new image;
	mine2 = new image;
	mine3 = new image;

	cloud = new image;
	cloud2 = new image;

	thunder = new image;
	thunder2 = new image;

	building = new image;
	building2 = new image;
	building3 = new image;

	monster = new image;
	monster2 = new image;

	tree = new image;

	profile.img = new image;
	quit.img = new image;
	start.img = new image;

	profile2 = new image;

	tt->D_Init(L"img/title/title.png", 197, 65);
	loading->D_Init(L"img/title/loading.png", 260, 46, 2, 1);
	loading2->D_Init(L"img/title/loading2.png", 297, 70);

	bg->D_Init(L"img/title/background.png", 608, 371);

	fg->D_Init(L"img/title/foreground.png", 608, 293);

	mine->D_Init(L"img/title/mine.png", 608, 310);
	mine2->D_Init(L"img/title/mine2.png", 122, 79);
	mine3->D_Init(L"img/title/mine3.png", 120, 67);

	cloud->D_Init(L"img/title/cloud.png", 608, 234);
	cloud2->D_Init(L"img/title/cloud2.png", 608, 262);

	thunder->D_Init(L"img/title/thunder.png", 375, 84, 3, 1);
	thunder2->D_Init(L"img/title/thunder2.png", 122, 72, 2, 1);

	building->D_Init(L"img/title/building.png", 141, 101);
	building2->D_Init(L"img/title/building2.png", 79, 62);
	building3->D_Init(L"img/title/building3.png", 150, 126);

	monster->D_Init(L"img/title/monster.png", 140, 25, 4, 1);
	monster2->D_Init(L"img/title/monster2.png", 32, 9, 4, 1);

	tree->D_Init(L"img/title/tree.png", 309, 138);

	profile.img->D_Init(L"img/title/btn/profile.png", 270, 90, 3, 1);
	quit.img->D_Init(L"img/title/btn/quit.png", 960, 90, 3, 1);
	start.img->D_Init(L"img/title/btn/start.png", 960, 90, 3, 1);

	profile2->D_Init(L"img/title/btn/profile2.png", 315, 95);

	profile.rc = D2DMANAGER->RectMake(450, WINSIZEY - 200, profile.img->getFrameWidth(), profile.img->getFrameHeight());
	quit.rc = D2DMANAGER->RectMake(880, WINSIZEY - 200, quit.img->getFrameWidth(), quit.img->getFrameHeight());
	start.rc = D2DMANAGER->RectMake(550, WINSIZEY - 200, start.img->getFrameWidth(), start.img->getFrameHeight());

	_monsterIndex = _loadingIndex = _loadingVal = _inMenu = _onMenu = 0;
	_thunder2Index = -1;
	_thunderIndex = 3;
	_loadingCount = 15;
	_loadingOpacity = 1.0f;
	_menuOpacity = 0;
	_count = 900;

	if (SOUNDMANAGER->isPlaySound("Village"))
	{
		SOUNDMANAGER->stop("Village");
	}

	if (SOUNDMANAGER->isPlaySound("dungeon"))
	{
		SOUNDMANAGER->stop("dungeon");
	}

	SOUNDMANAGER->play("Theme", 0.5f);

	SOUNDMANAGER->set_volume("Theme", SOUNDMANAGER->currentVolume());

	return S_OK;
}

void title::release()
{
}

void title::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_F1))
	{
		SCENEMANAGER->changeScene("Å×½ºÆ®¸Ê");
	}

	_count++;

	if (_count % _loadingCount == 0 && !_loadingVal)
	{
		_loadingIndex++;
		if (_loadingIndex > loading->getMaxFrameX())
		{
			_loadingIndex = 0;
			_loadingCount--;
			if (_loadingCount == 1) 
			{
				_loadingVal = 1;
			}
		}
	}

	if (_count % 5 == 0) 
	{
		if (_loadingVal)
		{
			_loadingOpacity-= 0.1f;
		}

		if (_loadingOpacity < 0)
		{
			_menuOpacity += 0.1f;
		}
	}

	if (_menuOpacity > 1.0f)
	{
		_inMenu = 1;
	}

	if (_count % 19 == 0)
	{
		_monsterIndex++;
		if (_monsterIndex > monster->getMaxFrameX())
		{
			_monsterIndex = 0;
		}

		if (_monster2Index >= monster2->getMaxFrameX())
		{
			_monster = true;
		}

		if (_monster)
		{
			_monster2Index--;
			if (_monster2Index <= 0)
			{
				_monster = false;
			}
		}
		else
		{
			_monster2Index++;
		}
	}
	
	if (_roop)
	{
		if (_count % 3 == 0)
		{
			_thunderIndex--;

			if (_thunderIndex < 0)
			{
				_thunderIndex = 3;
				_thunderEND = true;
			}
		}

		if (_thunderEND && _count % 5 == 0)
		{
			_thunder2Index++;

			if (_thunder2Index > thunder2->getMaxFrameX())
			{
				_thunder2Index = -1;
				_thunderIndex = 3;
				_roop = false;
				_thunderEND = false;
			}
		}
	}

	if (_count % 1000 == 0) _roop = true;

	if (_inMenu)
	{
		_ui->update();
		_mouseCursor->update();
	}

	CAMERAMANAGER->updateScreen(0, 0);
}

void title::render()
{
	bg->scale_start(0, 0, 3, 3);
	bg->render(170 + (_ptMouse.x / 200), 100 + (_ptMouse.y / 200));
	bg->scale_end();

	cloud->scale_start(0, 0, 3, 3);
	cloud->render(170 + (_ptMouse.x / 200), 30 + (_ptMouse.y / 200));
	cloud->scale_end();

	cloud2->scale_start(0, 0, 3, 3);
	cloud2->render(170 + (_ptMouse.x / 150), 30 + (_ptMouse.y / 150));
	cloud2->scale_end();

	building->scale_start(0, 0, 3, 3);
	building->render(250 + (_ptMouse.x / 200), 0 + (_ptMouse.y / 200));
	building->scale_end();

	building2->scale_start(0, 0, 3, 3);
	building2->render(264 + (_ptMouse.x / 200), 50 + (_ptMouse.y / 200));
	building2->scale_end();

	thunder2->Frame_scale_start(0, 0, 3, 3);
	thunder2->FrameRender(294 + (_ptMouse.x / 200), 37 + (_ptMouse.y / 200), _thunder2Index, 0);
	thunder2->scale_end();

	building3->scale_start(0, 0, 3, 3);
	building3->render(250 + (_ptMouse.x / 200), 100 + (_ptMouse.y / 200));
	building3->scale_end();

	thunder->Frame_scale_start(0, 0, 3, 3);
	thunder->FrameRender(345 + (_ptMouse.x / 200), 50 + (_ptMouse.y / 200), _thunderIndex, 0);
	thunder->scale_end();

	monster->Frame_scale_start(0, 0, 5, 6);
	monster->FrameRender(160 + (_ptMouse.x / 200), 90 + (_ptMouse.y / 200), _monsterIndex, 0);
	monster->scale_end();

	monster2->Frame_scale_start(0, 0, 5, 6);
	monster2->FrameRender(160 + (_ptMouse.x / 200), 90 + (_ptMouse.y / 200), _monster2Index, 0);
	monster2->scale_end();

	mine3->scale_start(0, 0, 3, 3);
	mine3->render(252 + (_ptMouse.x / 100), 175 + (_ptMouse.y / 100));
	mine3->scale_end();

	mine2->scale_start(0, 0, 3, 3);
	mine2->render(248 + (_ptMouse.x / 125), 173 + (_ptMouse.y / 125));
	mine2->scale_end();

	mine->scale_start(0, 0, 3, 3);
	mine->render(170 + (_ptMouse.x / 200), 140 + (_ptMouse.y / 200));
	mine->scale_end();

	fg->scale_start(0, 0, 3, 3);
	fg->render(170 + (_ptMouse.x / 150), 150 + (_ptMouse.y / 150));
	fg->scale_end();

	tree->scale_start(0, 0, 3, 3);
	tree->render(232 + (_ptMouse.x / 150), 270 + (_ptMouse.y / 150));
	tree->scale_end();

	loading->Frame_scale_start(0, 0, 3, 3);
	loading->FrameRender(250 + (_ptMouse.x / 200), 150 + (_ptMouse.y / 200), _loadingIndex, 0, _loadingOpacity);
	loading->scale_end();


	if (_onMenu)
	{
		profile2->render(_ptMouse.x + 45, _ptMouse.y + 20);
	}

	if (!_ui->getIsCharacterCreate())
	{
		tt->scale_start(0, 0, 2.5f, 2.5f);
		tt->render(tt->getWidth() + tt->getWidth() / 2, 100, _menuOpacity);
		tt->scale_end();
	}

	if (_inMenu) {
		_ui->render();
		_mouseCursor->render();
	}

}
