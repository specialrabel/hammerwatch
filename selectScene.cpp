#include "stdafx.h"
#include "selectScene.h"


selectScene::selectScene()
{
}


selectScene::~selectScene()
{
}

HRESULT selectScene::init()
{
	_btnSceneChange = new button;
	_btnSceneChange->init("¹öÆ°", WINSIZEX / 2, WINSIZEY / 2,
		PointMake(0, 1), PointMake(0, 0), cbSceneChange);

	return S_OK;
}

void selectScene::release()
{
}

void selectScene::update()
{
	_btnSceneChange->update();
}

void selectScene::render()
{
	_btnSceneChange->render();
}

void selectScene::cbSceneChange()
{
	SCENEMANAGER->changeScene("½ºÅ¸¾À");
}
