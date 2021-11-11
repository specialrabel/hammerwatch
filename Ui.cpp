#include "stdafx.h"
#include "Ui.h"

Ui::Ui()
{

}

Ui::~Ui()
{

}

HRESULT Ui::init()
{
	addImage();
	addButton();

	//============================
	//         BOOL INIT
	//============================
	_isPause = false;
	_isInfo = false;
	_isMap = false;
	_isCharacter = true;
	_isEffects = false;
	_isStats = false;
	_isCharacterList = false;
	_isCharacterCreate = false;
	_isSetting = false;
	_isInnNpc = false;
	_isSkillNpc = false;
	_isBlackSmithNpc = false;
	_isList[0] = true;
	_updateTime = 0;

	volumeInit();

	INIDATA->soltData();

	return S_OK;
}

void Ui::release()
{

}

void Ui::update()
{
	cam_x = CAMERAMANAGER->get_camera_x();
	cam_y = CAMERAMANAGER->get_camera_y();

	if (SCENEMANAGER->currentScene("타이틀")) {

		if (!_isCharacterList && !_isCharacterCreate && !_isSetting) titleUiUpdate();

		//SINGLEPLAY를 눌렀을 때
		if (_isCharacterList && !_isCharacterCreate) characterListUiUpdate();

		if (_isCharacterCreate) characterCreateUiUpdate();

		if (_isSetting) volumeUiUpdate();
	}
	if (SCENEMANAGER->currentScene("마을"))
	{
		playingUiUpdate();

		if (KEYMANAGER->isOnceKeyDown(VK_ESCAPE))
		{
			if (!_isInnNpc && !_isSkillNpc && !_isBlackSmithNpc)
			{
				if (_isPause) _isPause = false;
				else if (!_isPause && !_isInfo) _isPause = true;
				else if (!_isPause && _isInfo) _isInfo = false;
			}
			else if (_isInnNpc && !_isSkillNpc && !_isBlackSmithNpc)
			{
				_isInnNpc = false;
			}
			else if (!_isInnNpc && _isSkillNpc && !_isBlackSmithNpc)
			{
				_isSkillNpc = false;
			}
			else if (!_isInnNpc && !_isSkillNpc && _isBlackSmithNpc)
			{
				_isBlackSmithNpc = false;
			}
		}

		if (KEYMANAGER->isOnceKeyDown('C'))
		{
			_isCharacterInventory = false;
			if (_isInfo) _isInfo = false;
			else if (!_isInfo && !_isPause) _isInfo = true;
		}

		//ESC를 눌렀을 때
		if (_isPause) pauseUiUpdate();
	
		//정보창이 틀어졌을 때
		if (_isInfo) playerInfoUiUpdate();
	}
	if (SCENEMANAGER->currentScene("던전"))
	{
		playingUiUpdate();

		if (KEYMANAGER->isOnceKeyDown(VK_ESCAPE))
		{
			if (!_isInnNpc && !_isSkillNpc && !_isBlackSmithNpc)
			{
				if (_isPause) _isPause = false;
				else if (!_isPause && !_isInfo) _isPause = true;
				else if (!_isPause && _isInfo) _isInfo = false;
			}
			else if (_isInnNpc && !_isSkillNpc && !_isBlackSmithNpc)
			{
				_isInnNpc = false;
			}
			else if (!_isInnNpc && _isSkillNpc && !_isBlackSmithNpc)
			{
				_isSkillNpc = false;
			}
			else if (!_isInnNpc && !_isSkillNpc && _isBlackSmithNpc)
			{
				_isBlackSmithNpc = false;
			}
		}

		if (KEYMANAGER->isOnceKeyDown('C'))
		{
			_isCharacterInventory = false;
			if (_isInfo) _isInfo = false;
			else if (!_isInfo && !_isPause) _isInfo = true;
		}

		//ESC를 눌렀을 때
		if (_isPause) pauseUiUpdate();

		//정보창이 틀어졌을 때
		if (_isInfo) playerInfoUiUpdate();
	}

}

void Ui::render()
{
	if (SCENEMANAGER->currentScene("타이틀")) {
		//메인타이틀 UI
		if (!_isCharacterList && !_isCharacterCreate && !_isSetting) titleUiRender();

		//싱글플레이 UI
		if (_isCharacterList && !_isCharacterCreate) characterListUiRender();

		//캐릭터생성 UI
		if (_isCharacterCreate) characterCreateUiRender();

		if (_isSetting) volumeUiRender();
	}
	if (SCENEMANAGER->currentScene("마을")) {
		//플레이 시작 했을 때, 렌더되는 UI
		playingUiRender();

		if (_isInnNpc) innUiRender();
		if (_isSkillNpc) skillUiRender();
		if (_isBlackSmithNpc) blackSmithUiRender();

		//ESC를 눌렀을 때, 렌더되는 UI
		if (_isPause) pauseUiRender();
		
		else if (!_isPause && _isInfo) playerInfoUiRender();

		if (!(_isInfo && _isCharacter))
		{
			ITEMMANAGER->deletAllItemInventory();
		}
	}
	if (SCENEMANAGER->currentScene("던전")) {
		//플레이 시작 했을 때, 렌더되는 UI
		playingUiRender();

		if (_isInnNpc) innUiRender();
		if (_isSkillNpc) skillUiRender();
		if (_isBlackSmithNpc) blackSmithUiRender();

		//ESC를 눌렀을 때, 렌더되는 UI
		if (_isPause) pauseUiRender();

		else if (!_isPause && _isInfo) playerInfoUiRender();

		if (!(_isInfo && _isCharacter))
		{
			ITEMMANAGER->deletAllItemInventory();
		}
	}
}

#pragma region TITLE UI
void Ui::titleUiUpdate()
{
	_button[TITLE_PROFILES].rc = D2DMANAGER->RectMake(_button[TITLE_PROFILES].x, _button[TITLE_PROFILES].y
		, _button[TITLE_PROFILES].width, _button[TITLE_PROFILES].height);

	if (PTIN_RECT(&_button[TITLE_PROFILES].rc, _ptMouse)) {
		if (KEYMANAGER->isStayKeyDown(VK_LBUTTON)) _title_profiles = IMAGEMANAGER->findImage("title_profilesBtn3");
		else
			_title_profiles = IMAGEMANAGER->findImage("title_profilesBtn2");

		if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON));
	}
	else {
		_title_profiles = IMAGEMANAGER->findImage("title_profilesBtn");
	}

	_button[TITLE_SINGLEPLAY].rc = D2DMANAGER->RectMake(_button[TITLE_SINGLEPLAY].x, _button[TITLE_SINGLEPLAY].y
		, _button[TITLE_SINGLEPLAY].width, _button[TITLE_SINGLEPLAY].height);

	if (PTIN_RECT(&_button[TITLE_SINGLEPLAY].rc, _ptMouse)) {
		if (KEYMANAGER->isStayKeyDown(VK_LBUTTON)) _title_play = IMAGEMANAGER->findImage("title_playBtn3");
		else
			_title_play = IMAGEMANAGER->findImage("title_playBtn2");

		if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON) && !_isCharacterList)
		{
			_isCharacterList = true;
		}
	}
	else {
		_title_play = IMAGEMANAGER->findImage("title_playBtn");
	}


	_button[TITLE_SETTING].rc = D2DMANAGER->RectMake(_button[TITLE_SETTING].x, _button[TITLE_SETTING].y
		, _button[TITLE_SETTING].width, _button[TITLE_SETTING].height);

	if (PTIN_RECT(&_button[TITLE_SETTING].rc, _ptMouse)) {
		if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON)) _isSetting = true;
		
		if (KEYMANAGER->isStayKeyDown(VK_LBUTTON)) _title_option = IMAGEMANAGER->findImage("title_optionBtn3");
		else
			_title_option = IMAGEMANAGER->findImage("title_optionBtn2");
	}
	else {
		_title_option = IMAGEMANAGER->findImage("title_optionBtn");
	}


	_button[TITLE_EXIT].rc = D2DMANAGER->RectMake(_button[TITLE_EXIT].x, _button[TITLE_EXIT].y
		, _button[TITLE_EXIT].width, _button[TITLE_EXIT].height);

	if (PTIN_RECT(&_button[TITLE_EXIT].rc, _ptMouse)) {
		if (KEYMANAGER->isStayKeyDown(VK_LBUTTON)) _title_exit = IMAGEMANAGER->findImage("title_exitBtn3");
		else
			_title_exit = IMAGEMANAGER->findImage("title_exitBtn2");

		if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON)) PostQuitMessage(0);
	}
	else {
		_title_exit = IMAGEMANAGER->findImage("title_exitBtn");
	}


	_button[TITLE_MAPEDIT].rc = D2DMANAGER->RectMake(_button[TITLE_MAPEDIT].x, _button[TITLE_MAPEDIT].y
		, _button[TITLE_MAPEDIT].width, _button[TITLE_MAPEDIT].height);

	if (PTIN_RECT(&_button[TITLE_MAPEDIT].rc, _ptMouse)) {
		if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON)) SCENEMANAGER->changeScene("테스트맵");
		
		if (KEYMANAGER->isStayKeyDown(VK_LBUTTON)) _title_mapEdit = IMAGEMANAGER->findImage("title_mapEditBtn3");
		else
			_title_mapEdit = IMAGEMANAGER->findImage("title_mapEditBtn2");
	}
	else {
		_title_mapEdit = IMAGEMANAGER->findImage("title_mapEditBtn");
	}
}

void Ui::titleUiRender()
{
	_title_profiles->render(WINSIZEX / 2 - 235, WINSIZEY - 200);
	_title_play->render(WINSIZEX / 2 - 185, WINSIZEY - 200);
	_title_option->render(WINSIZEX / 2 - 25, WINSIZEY - 200);
	_title_exit->render(WINSIZEX / 2 + 135, WINSIZEY - 200);
	_title_mapEdit->render(WINSIZEX - 50, 10);
}
#pragma endregion

#pragma region CHARACTER LIST UI
void Ui::characterListUiUpdate()
{
	_button[CHARACTER_LIST_NEW].rc = D2DMANAGER->RectMake(_button[CHARACTER_LIST_NEW].x, _button[CHARACTER_LIST_NEW].y
		, _button[CHARACTER_LIST_NEW].width, _button[CHARACTER_LIST_NEW].height);

	if (PTIN_RECT(&_button[CHARACTER_LIST_NEW].rc, _ptMouse)) {
		if (KEYMANAGER->isStayKeyDown(VK_LBUTTON)) _characterList_new = IMAGEMANAGER->findImage("characterList_new3");
		else
			_characterList_new = IMAGEMANAGER->findImage("characterList_new2");

		if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON)) _isCharacterCreate = true;
	}
	else {
		_characterList_new = IMAGEMANAGER->findImage("characterList_new");
	}


	_button[CHARACTER_LIST_PLAY].rc = D2DMANAGER->RectMake(_button[CHARACTER_LIST_PLAY].x, _button[CHARACTER_LIST_PLAY].y
		, _button[CHARACTER_LIST_PLAY].width, _button[CHARACTER_LIST_PLAY].height);

	if (PTIN_RECT(&_button[CHARACTER_LIST_PLAY].rc, _ptMouse)) {
		if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON)) SCENEMANAGER->changeScene("마을");
		
		if (KEYMANAGER->isStayKeyDown(VK_LBUTTON)) _characterList_play = IMAGEMANAGER->findImage("characterList_play3");
		else
			_characterList_play = IMAGEMANAGER->findImage("characterList_play2");
	}
	else {
		_characterList_play = IMAGEMANAGER->findImage("characterList_play");
	}

	_button[CHARACTER_LIST_TRESH].rc = D2DMANAGER->RectMake(_button[CHARACTER_LIST_TRESH].x, _button[CHARACTER_LIST_TRESH].y
		, _button[CHARACTER_LIST_TRESH].width, _button[CHARACTER_LIST_TRESH].height);

	if (PTIN_RECT(&_button[CHARACTER_LIST_TRESH].rc, _ptMouse)) {
		if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
		{
			if (_isList[0]) INIDATA->deleteData(0);
			if (_isList[1]) INIDATA->deleteData(1);
			if (_isList[2]) INIDATA->deleteData(2);
			if (_isList[3]) INIDATA->deleteData(3);
			if (_isList[4]) INIDATA->deleteData(4);
			INIDATA->soltData();
		}

		if (KEYMANAGER->isStayKeyDown(VK_LBUTTON)) _characterList_tresh = IMAGEMANAGER->findImage("characterList_tresh3");
		else
			_characterList_tresh = IMAGEMANAGER->findImage("characterList_tresh2");
	}
	else {
		_characterList_tresh = IMAGEMANAGER->findImage("characterList_tresh");
	}

	_button[CHARACTER_LIST_BOX1].rc = D2DMANAGER->RectMake(_button[CHARACTER_LIST_BOX1].x, _button[CHARACTER_LIST_BOX1].y
		, _button[CHARACTER_LIST_BOX1].width, _button[CHARACTER_LIST_BOX1].height);

	if (PTIN_RECT(&_button[CHARACTER_LIST_BOX1].rc, _ptMouse)) {
		if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
		{
			_isList[0] = true;
			_isList[1] = false;
			_isList[2] = false;
			_isList[3] = false;
			_isList[4] = false;

			INIDATA->currentData(0);
		}

		if (KEYMANAGER->isStayKeyDown(VK_LBUTTON)) _characterListBox[0] = IMAGEMANAGER->findImage("characterList_Box3");
		else
			_characterListBox[0] = IMAGEMANAGER->findImage("characterList_Box2");
	}
	else {
		if(!_isList[0]) _characterListBox[0] = IMAGEMANAGER->findImage("characterList_Box");
		else if(_isList[0]) _characterListBox[0] = IMAGEMANAGER->findImage("characterList_Box3");
	}


	_button[CHARACTER_LIST_BOX2].rc = D2DMANAGER->RectMake(_button[CHARACTER_LIST_BOX2].x, _button[CHARACTER_LIST_BOX2].y
		, _button[CHARACTER_LIST_BOX2].width, _button[CHARACTER_LIST_BOX2].height);

	if (PTIN_RECT(&_button[CHARACTER_LIST_BOX2].rc, _ptMouse)) {
		if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
		{
			_isList[0] = false;
			_isList[1] = true;
			_isList[2] = false;
			_isList[3] = false;
			_isList[4] = false;

			INIDATA->currentData(1);
		}

		if (KEYMANAGER->isStayKeyDown(VK_LBUTTON)) _characterListBox[1] = IMAGEMANAGER->findImage("characterList_Box3");
		else
			_characterListBox[1] = IMAGEMANAGER->findImage("characterList_Box2");
	}
	else {
		if (!_isList[1]) _characterListBox[1] = IMAGEMANAGER->findImage("characterList_Box");
		else if (_isList[1]) _characterListBox[1] = IMAGEMANAGER->findImage("characterList_Box3");
	}


	_button[CHARACTER_LIST_BOX3].rc = D2DMANAGER->RectMake(_button[CHARACTER_LIST_BOX3].x, _button[CHARACTER_LIST_BOX3].y
		, _button[CHARACTER_LIST_BOX3].width, _button[CHARACTER_LIST_BOX3].height);

	if (PTIN_RECT(&_button[CHARACTER_LIST_BOX3].rc, _ptMouse)) {
		if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
		{
			_isList[0] = false;
			_isList[1] = false;
			_isList[2] = true;
			_isList[3] = false;
			_isList[4] = false;

			INIDATA->currentData(2);
		}

		if (KEYMANAGER->isStayKeyDown(VK_LBUTTON)) _characterListBox[2] = IMAGEMANAGER->findImage("characterList_Box3");
		else
			_characterListBox[2] = IMAGEMANAGER->findImage("characterList_Box2");
	}
	else {
		if (!_isList[2]) _characterListBox[2] = IMAGEMANAGER->findImage("characterList_Box");
		else if (_isList[2]) _characterListBox[2] = IMAGEMANAGER->findImage("characterList_Box3");
	}


	_button[CHARACTER_LIST_BOX4].rc = D2DMANAGER->RectMake(_button[CHARACTER_LIST_BOX4].x, _button[CHARACTER_LIST_BOX4].y
		, _button[CHARACTER_LIST_BOX4].width, _button[CHARACTER_LIST_BOX4].height);

	if (PTIN_RECT(&_button[CHARACTER_LIST_BOX4].rc, _ptMouse)) {
		if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
		{
			_isList[0] = false;
			_isList[1] = false;
			_isList[2] = false;
			_isList[3] = true;
			_isList[4] = false;

			INIDATA->currentData(3);
		}

		if (KEYMANAGER->isStayKeyDown(VK_LBUTTON)) _characterListBox[3] = IMAGEMANAGER->findImage("characterList_Box3");
		else
			_characterListBox[3] = IMAGEMANAGER->findImage("characterList_Box2");
	}
	else {
		if (!_isList[3]) _characterListBox[3] = IMAGEMANAGER->findImage("characterList_Box");
		else if (_isList[3]) _characterListBox[3] = IMAGEMANAGER->findImage("characterList_Box3");
	}


	_button[CHARACTER_LIST_BOX5].rc = D2DMANAGER->RectMake(_button[CHARACTER_LIST_BOX5].x, _button[CHARACTER_LIST_BOX5].y
		, _button[CHARACTER_LIST_BOX5].width, _button[CHARACTER_LIST_BOX5].height);

	if (PTIN_RECT(&_button[CHARACTER_LIST_BOX5].rc, _ptMouse)) {
		if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
		{
			_isList[0] = false;
			_isList[1] = false;
			_isList[2] = false;
			_isList[3] = false;
			_isList[4] = true;

			INIDATA->currentData(4);
		}

		if (KEYMANAGER->isStayKeyDown(VK_LBUTTON)) _characterListBox[4] = IMAGEMANAGER->findImage("characterList_Box3");
		else
			_characterListBox[4] = IMAGEMANAGER->findImage("characterList_Box2");
	}
	else {
		if (!_isList[4]) _characterListBox[4] = IMAGEMANAGER->findImage("characterList_Box");
		else if (_isList[4]) _characterListBox[4] = IMAGEMANAGER->findImage("characterList_Box3");
	}

	_button[CHARACTER_LIST_EXIT].rc = D2DMANAGER->RectMake(_button[CHARACTER_LIST_EXIT].x, _button[CHARACTER_LIST_EXIT].y
		, _button[CHARACTER_LIST_EXIT].width, _button[CHARACTER_LIST_EXIT].height);

	if (PTIN_RECT(&_button[CHARACTER_LIST_EXIT].rc, _ptMouse)) {
		if (KEYMANAGER->isStayKeyDown(VK_LBUTTON)) _characterList_exit = IMAGEMANAGER->findImage("PlayerInfoExitBtn3");
		else
			_characterList_exit = IMAGEMANAGER->findImage("PlayerInfoExitBtn2");

		if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON)) _isCharacterList = false;
	}
	else {
		_characterList_exit = IMAGEMANAGER->findImage("PlayerInfoExitBtn");
	}

	_listNum = INIDATA->listNum();
}
void Ui::characterListUiRender()
{
	_characterListUi->render(WINSIZEX / 2 - _characterListUi->getWidth() / 2, WINSIZEY / 2 - _characterListUi->getHeight() / 2);

	_characterList_new->render(498, 647);

	_characterList_play->render(822, 647);

	_characterList_tresh->render(1074, 647);

	_characterList_exit->render(1233, 210);

	for (int i = 0; i < _listNum; i++)
	{
		_characterListBox[i]->render(325, 260 + _characterListBox[i]->getHeight() * i);

		WCHAR str2[128];
		
		
		if (INIDATA->readData(i, "CLASS") == 0)
		{
			swprintf_s(str2, L"PHAND THE PALADIN, %d HOUR %d MINUTE", (int)INIDATA->readData(i, "PLAY TIME") / 3600, (int)INIDATA->readData(i, "PLAY TIME") % 3600 / 60);
			D2DMANAGER->DrawTextD2DCenter(D2DMANAGER->CreateBrush(0xffffff), L"DOSGothic", 25.0f, str2, 625, 700, 1200, 290 + 86 * i);
			
			_characterList_paladin_picture->render(339, 273 + 86 * i);
			_characterList_paladin_icon->render(406, 273 + 86 * i);
		}
		else if (INIDATA->readData(i, "CLASS") == 1)
		{
			swprintf_s(str2, L"AURA THE RANGER, %d HOUR %d MINUTE", (int)INIDATA->readData(i, "PLAY TIME") / 3600, (int)INIDATA->readData(i, "PLAY TIME") % 3600 / 60);
			D2DMANAGER->DrawTextD2DCenter(D2DMANAGER->CreateBrush(0xffffff), L"DOSGothic", 25.0f, str2, 625, 700, 1200, 290 + 86 * i);

			_characterList_ranger_picture->render(339, 273 + 86 * i);
			_characterList_ranger_icon->render(406, 273 + 86 * i);
		}

		WCHAR str1[128];
		swprintf_s(str1, L"%.0f", INIDATA->readData(i, "LEVEL"));
		D2DMANAGER->DrawTextD2DCenter(D2DMANAGER->CreateBrush(0xffffff), L"DOSGothic", 25.0f, str1, 498, 700, 545, 290 + 86*i);

	}
}
#pragma endregion

#pragma region CHARACTER CREATE UI
void Ui::characterCreateUiUpdate()
{
	_button[CHARACTER_CREATE_PALADIN].rc = D2DMANAGER->RectMake(_button[CHARACTER_CREATE_PALADIN].x, _button[CHARACTER_CREATE_PALADIN].y
		, _button[CHARACTER_CREATE_PALADIN].width, _button[CHARACTER_CREATE_PALADIN].height);

	if (PTIN_RECT(&_button[CHARACTER_CREATE_PALADIN].rc, _ptMouse)) {
		if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON)) {
			_isPaladin = true;
			_isRanger = false;
		}

		if (KEYMANAGER->isStayKeyDown(VK_LBUTTON)) _characterCreate_paladin = IMAGEMANAGER->findImage("characterCreate_paladin3");
		else if (_isPaladin) _characterCreate_paladin = IMAGEMANAGER->findImage("characterCreate_paladin3");
		else _characterCreate_paladin = IMAGEMANAGER->findImage("characterCreate_paladin2");
	}
	else {
		if (!_isPaladin) _characterCreate_paladin = IMAGEMANAGER->findImage("characterCreate_paladin");
		else if (_isPaladin) _characterCreate_paladin = IMAGEMANAGER->findImage("characterCreate_paladin3");
	}


	_button[CHARACTER_CREATE_RANGER].rc = D2DMANAGER->RectMake(_button[CHARACTER_CREATE_RANGER].x, _button[CHARACTER_CREATE_RANGER].y
		, _button[CHARACTER_CREATE_RANGER].width, _button[CHARACTER_CREATE_RANGER].height);

	if (PTIN_RECT(&_button[CHARACTER_CREATE_RANGER].rc, _ptMouse)) {
		if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON)) {
			_isPaladin = false;
			_isRanger = true;
		}
		if (KEYMANAGER->isStayKeyDown(VK_LBUTTON)) _characterCreate_ranger = IMAGEMANAGER->findImage("characterCreate_ranger3");
		else if (_isRanger) _characterCreate_ranger = IMAGEMANAGER->findImage("characterCreate_ranger3");
		else _characterCreate_ranger = IMAGEMANAGER->findImage("characterCreate_ranger2");
	}
	else {
		if (!_isRanger) _characterCreate_ranger = IMAGEMANAGER->findImage("characterCreate_ranger");
		else if (_isRanger) _characterCreate_ranger = IMAGEMANAGER->findImage("characterCreate_ranger3");
	}


	_button[CHARACTER_CREATE_PLAY].rc = D2DMANAGER->RectMake(_button[CHARACTER_CREATE_PLAY].x, _button[CHARACTER_CREATE_PLAY].y
		, _button[CHARACTER_CREATE_PLAY].width, _button[CHARACTER_CREATE_PLAY].height);

	if (PTIN_RECT(&_button[CHARACTER_CREATE_PLAY].rc, _ptMouse)) {
		if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON)) { 
			if (_isPaladin) {
				_data->createCharacter("팔라딘");
			}
			if (_isRanger) {
				_data->createCharacter("궁수");
			}
			INIDATA->currentData(_listNum);


			SCENEMANAGER->changeScene("마을"); 
		}

		if (KEYMANAGER->isStayKeyDown(VK_LBUTTON)) _characterCreate_play = IMAGEMANAGER->findImage("characterCreate_play3");
		else _characterCreate_play = IMAGEMANAGER->findImage("characterCreate_play2");
	}
	else {
		_characterCreate_play = IMAGEMANAGER->findImage("characterCreate_play");
	}


	_button[CHARACTER_CREATE_EXIT].rc = D2DMANAGER->RectMake(_button[CHARACTER_CREATE_EXIT].x, _button[CHARACTER_CREATE_EXIT].y
		, _button[CHARACTER_CREATE_EXIT].width, _button[CHARACTER_CREATE_EXIT].height);

	if (PTIN_RECT(&_button[CHARACTER_CREATE_EXIT].rc, _ptMouse)) {
		if (KEYMANAGER->isStayKeyDown(VK_LBUTTON)) _characterCreate_exit = IMAGEMANAGER->findImage("PlayerInfoExitBtn3");
		else _characterCreate_exit = IMAGEMANAGER->findImage("PlayerInfoExitBtn2");

		if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON)) {
			_isCharacterCreate = false;
			_isPaladin = false;
			_isRanger = false;
		}
	}
	else {
		_characterCreate_exit = IMAGEMANAGER->findImage("PlayerInfoExitBtn");
	}
}
void Ui::characterCreateUiRender()
{
	_characterCreateUi->render(WINSIZEX / 2 - _characterCreateUi->getWidth() / 2, WINSIZEY / 2 - _characterCreateUi->getHeight() / 2);

	_characterCreate_paladin->render(734, 384);

	if (_isPaladin) {
		for (int i = 0; i < 7; i++) {
			_characterCreate_paladin_skill[i]->render(548 + (i*(58 + 16)), 458);
		}
	}

	_characterCreate_ranger->render(808, 384);

	if (_isRanger) {
		for (int i = 0; i < 7; i++) {
			_characterCreate_ranger_skill[i]->render(548 + (i*(58 + 16)), 458);
		}
	}

	_characterCreate_play->render(WINSIZEX / 2 - _characterCreate_play->getWidth() / 2, 528);

	_characterCreate_exit->render(1088, 328);
}
#pragma endregion

#pragma region VOLUME UI
void Ui::volumeUiUpdate()
{
	float volume = (_button[VOLUME_BUTTON].rc.left - 788) / (1125 - 788);

	_button[VOLUME_RESET].rc = D2DMANAGER->RectMake(_button[VOLUME_RESET].x + cam_x, _button[VOLUME_RESET].y + cam_y
		, _button[VOLUME_RESET].width, _button[VOLUME_RESET].height);

	if (PTIN_RECT(&_button[VOLUME_RESET].rc, _ptMouse)) {
		if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
		{
			_volume_button_x = 950;
			_volume_button_y = 434;
		}
		
		if (KEYMANAGER->isStayKeyDown(VK_LBUTTON)) _volume_reset = IMAGEMANAGER->findImage("volume_reset3");
		else
			_volume_reset = IMAGEMANAGER->findImage("volume_reset2");
	}
	else {
		_volume_reset = IMAGEMANAGER->findImage("volume_reset1");
	}

	_button[VOLUME_ACCEPT].rc = D2DMANAGER->RectMake(_button[VOLUME_ACCEPT].x + cam_x, _button[VOLUME_ACCEPT].y + cam_y
		, _button[VOLUME_ACCEPT].width, _button[VOLUME_ACCEPT].height);

	if (PTIN_RECT(&_button[VOLUME_ACCEPT].rc, _ptMouse)) {
		if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON)) {
			_isSetting = false;
			SOUNDMANAGER->saveVolume(volume);
		}

		if (KEYMANAGER->isStayKeyDown(VK_LBUTTON)) _volume_accept = IMAGEMANAGER->findImage("volume_accept3");
		else
			_volume_accept = IMAGEMANAGER->findImage("volume_accept2");
	}
	else {
		_volume_accept = IMAGEMANAGER->findImage("volume_accept1");
	}

	_button[VOLUME_EXIT].rc = D2DMANAGER->RectMake(_button[VOLUME_EXIT].x + cam_x, _button[VOLUME_EXIT].y + cam_y
		, _button[VOLUME_EXIT].width, _button[VOLUME_EXIT].height);

	if (PTIN_RECT(&_button[VOLUME_EXIT].rc, _ptMouse)) {
		if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON)) {
			_isSetting = false;
			_volume_button_x = 950;
			_volume_button_y = 434;
		}

		if (KEYMANAGER->isStayKeyDown(VK_LBUTTON)) _volume_exit = IMAGEMANAGER->findImage("volume_exit3");
		else
			_volume_exit = IMAGEMANAGER->findImage("volume_exit2");
	}
	else {
		_volume_exit = IMAGEMANAGER->findImage("volume_exit1");
	}

	_button[VOLUME_BUTTON].rc = D2DMANAGER->RectMakeCenter(_volume_button_x+11, _volume_button_y+16, 22, 32);

	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		if (PTIN_RECT(&_button[VOLUME_BUTTON].rc, _ptMouse)) {
			if(_volume_button_x >= 788 && _volume_button_x <= 1125)
			_volume_button_x = _ptMouse.x - 11;
			
			if (_volume_button_x <= 788)
				_volume_button_x = 789;
			if (_volume_button_x >= 1125)
				_volume_button_x = 1124;
		}
	}

	SOUNDMANAGER->set_volume("Theme", volume);
	SOUNDMANAGER->set_volume("dungeon", volume);
	SOUNDMANAGER->set_volume("Village", volume);
}
void Ui::volumeUiRender()
{
	_volumeUi->render(WINSIZEX / 2 - _volumeUi->getWidth() / 2 + 30, WINSIZEY / 2 - _volumeUi->getHeight() / 2);
	
	_volume_reset->render(595, 483);
	_volume_accept->render(872, 483);
	_volume_exit->render(1154, 380);

	_volume_button->render(_volume_button_x, _volume_button_y);

	D2DMANAGER->Rectangle(_button[VOLUME_BUTTON].rc);
}
#pragma endregion

#pragma region PLAYING UI
void Ui::playingUiUpdate()
{
	_updateTime += 1;

	if (_updateTime % 5 == 0)
	{
		playerSAVE();
	}
}

void Ui::playingUiRender()
{
	//UI BAR RENDER
	_leftBar->render(0 + cam_x, WINSIZEY - _leftBar->getHeight() + cam_y);
	_rightBar->render(WINSIZEX - _rightBar->getWidth() + cam_x, WINSIZEY - _rightBar->getHeight() + cam_y);
	_upBar->render(WINSIZEX / 2 - _upBar->getWidth() / 2 + cam_x, 0 + cam_y);


	//JOB ICON RENDER
	if (_pl->get_playerStatus().player_class == Player_Class::Paladin) {
		_paladin->render(5 + cam_x, WINSIZEY / 2 + 83 + cam_y);
		_paladin_skill1->render(WINSIZEX - _paladin_skill1->getWidth() - 5 + cam_x, WINSIZEY / 2 + 185 + cam_y);
		_paladin_skill2->render(WINSIZEX - _paladin_skill2->getWidth() - 5 + cam_x, WINSIZEY / 2 + 253 + cam_y);
		_paladin_skill2_cooltime->renderUI(
										WINSIZEX - _paladin_skill2->getWidth() - 5 + cam_x, 
										WINSIZEY / 2 + 253 + cam_y,
										0,
										_pl->get_currentCD() * 2 / _pl->get_playerStatus().skill_cd * _paladin_skill2_cooltime->getHeight(),
										0,
										57
		);

		//SKILL COOLTIME END(스킬쿨타임 다 됐을 때 반짝이기) 나중에 getHp()는 getSkillCooltime()으로 변경할것
		if (_pl->get_currentCD() * 2 / _pl->get_playerStatus().skill_cd > 0.90f && _pl->get_currentCD() * 2 / _pl->get_playerStatus().skill_cd <= 1.6f)
		{
			_playing_cooltime_end->render(WINSIZEX - _paladin_skill2->getWidth() - 5 + cam_x, WINSIZEY / 2 + 253 + cam_y);
		}
	}
	else if (_pl->get_playerStatus().player_class == Player_Class::Ranger) {
		_ranger->render(5 + cam_x, WINSIZEY / 2 + 83 + cam_y);
		_ranger_skill1->render(WINSIZEX - _ranger_skill1->getWidth() - 5 + cam_x, WINSIZEY / 2 + 185 + cam_y);
		_ranger_skill2->render(WINSIZEX - _ranger_skill2->getWidth() - 5 + cam_x, WINSIZEY / 2 + 253 + cam_y);
		_ranger_skill2_cooltime->renderUI(
			WINSIZEX - _ranger_skill2->getWidth() - 5 + cam_x,
			WINSIZEY / 2 + 253 + cam_y,
			0,
			_pl->get_currentCD() / _pl->get_playerStatus().skill_cd * _ranger_skill2_cooltime->getHeight(),
			0,
			57
		);
	
		//SKILL COOLTIME END(스킬쿨타임 다 됐을 때 반짝이기) 나중에 getHp()는 getSkillCooltime()으로 변경할것
		if (_pl->get_currentCD() / _pl->get_playerStatus().skill_cd > 0.94f && _pl->get_currentCD() / _pl->get_playerStatus().skill_cd <= 1.6f)
		{
			_playing_cooltime_end->render(WINSIZEX - _paladin_skill2->getWidth() - 5 + cam_x, WINSIZEY / 2 + 253 + cam_y);
		}
	}




	//POTION ICON RENDER
	if (_pl->get_playerResource()._potion.crrentHave == _pl->get_playerResource()._potion.maxHave) _potion->render(5 + cam_x, WINSIZEY / 2 + 186 + cam_y);
	else if (_pl->get_playerResource()._potion.crrentHave > 0) _potion_half->render(5 + cam_x, WINSIZEY / 2 + 186 + cam_y);


	//GAUGE BAR
	_playing_hpBar->renderUI(5 + cam_x, WINSIZEY - 190 + cam_y, 0, _playing_hpBar->getHeight() - _pl->get_playerStatus().hp / _pl->get_playerStatus().max_hp * _playing_hpBar->getHeight(), 0, 0);
	_playing_mpBar->renderUI(41 + cam_x, WINSIZEY - 190 + cam_y, 0, _playing_mpBar->getHeight() - _pl->get_playerStatus().mp / _pl->get_playerStatus().max_mp * _playing_mpBar->getHeight(), 0, 0);
	_playing_hpBar2->renderUI(7 + cam_x, WINSIZEY - 321 + cam_y, _playing_hpBar2->getWidth() - _pl->get_playerStatus().hp / _pl->get_playerStatus().max_hp * _playing_hpBar2->getWidth(), 0, 0, 0);
	_playing_mpBar2->renderUI(7 + cam_x, WINSIZEY - 318 + cam_y, _playing_mpBar2->getWidth() - _pl->get_playerStatus().mp / _pl->get_playerStatus().max_mp * _playing_mpBar2->getWidth(), 0, 0, 0);
	_playing_expBar->renderUI(WINSIZEX - 77 + cam_x, WINSIZEY - 264 + cam_y, 0, _playing_expBar->getHeight() - _pl->get_playerStatus().exp / _pl->get_playerStatus().max_exp * _playing_expBar->getHeight(), 0, 0);

	switch (_pl->get_playerResource()._potion.maxHave) {
		case 1 :
			if(_pl->get_playerResource()._potion.maxHave == _pl->get_playerResource()._potion.crrentHave) _playing_potion_gauge1->render(7 + cam_x, WINSIZEY / 2 + 238 + cam_y);
			break;
	}


	//TEXT RENDER
	WCHAR gold[128];
	WCHAR ore[128];
	WCHAR skillpoint[128];
	swprintf_s(gold, L"%d", _pl->get_playerResource().gold);
	D2DMANAGER->DrawTextD2DRight(D2DMANAGER->CreateBrush(0xffffff), L"DOSGothic", 25.0f, gold, 600, 10, 725, 100);

	swprintf_s(ore, L"%d", _pl->get_playerResource().ore);
	D2DMANAGER->DrawTextD2DRight(D2DMANAGER->CreateBrush(0xffffff), L"DOSGothic", 25.0f, ore, 750, 10, 803, 100);

	swprintf_s(skillpoint, L"%d", _pl->get_playerStatus().skill_point);
	D2DMANAGER->DrawTextD2DRight(D2DMANAGER->CreateBrush(0xffffff), L"DOSGothic", 25.0f, skillpoint, 930, 10, 978, 100);
}
#pragma endregion

#pragma region PAUSE UI
void Ui::pauseUiUpdate()
{
	_button[PAUSE_RESUME].rc = D2DMANAGER->RectMake(_button[PAUSE_RESUME].x + cam_x, _button[PAUSE_RESUME].y + cam_y
		, _button[PAUSE_RESUME].width, _button[PAUSE_RESUME].height);

	if (PTIN_RECT(&_button[PAUSE_RESUME].rc, _ptMouse)) {
		if (KEYMANAGER->isStayKeyDown(VK_LBUTTON)) _pause_resumeBtn = IMAGEMANAGER->findImage("pauseResumeBtn3");
		else
			_pause_resumeBtn = IMAGEMANAGER->findImage("pauseResumeBtn2");

		if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON)) _isPause = false;
	}
	else {
		_pause_resumeBtn = IMAGEMANAGER->findImage("pauseResumeBtn");
	}


	_button[PAUSE_GOHOME].rc = D2DMANAGER->RectMake(_button[PAUSE_GOHOME].x + cam_x, _button[PAUSE_GOHOME].y + cam_y
		, _button[PAUSE_GOHOME].width, _button[PAUSE_GOHOME].height);

	if (PTIN_RECT(&_button[PAUSE_GOHOME].rc, _ptMouse)) {
		if (KEYMANAGER->isStayKeyDown(VK_LBUTTON)) _pause_gohomeBtn = IMAGEMANAGER->findImage("pauseGohomeBtn3");
		else
			_pause_gohomeBtn = IMAGEMANAGER->findImage("pauseGohomeBtn2");

		if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
		{
			SCENEMANAGER->init();
			SCENEMANAGER->changeScene("마을");
		}
	}
	else {
		_pause_gohomeBtn = IMAGEMANAGER->findImage("pauseGohomeBtn");
	}


	_button[PAUSE_SETTING].rc = D2DMANAGER->RectMake(_button[PAUSE_SETTING].x + cam_x, _button[PAUSE_SETTING].y + cam_y
		, _button[PAUSE_SETTING].width, _button[PAUSE_SETTING].height);

	if (PTIN_RECT(&_button[PAUSE_SETTING].rc, _ptMouse)) {
		if (KEYMANAGER->isStayKeyDown(VK_LBUTTON)) _pause_settingBtn = IMAGEMANAGER->findImage("pauseSettingBtn3");
		else
			_pause_settingBtn = IMAGEMANAGER->findImage("pauseSettingBtn2");

		if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON));
	}
	else {
		_pause_settingBtn = IMAGEMANAGER->findImage("pauseSettingBtn");
	}


	_button[PAUSE_EXIT].rc = D2DMANAGER->RectMake(_button[PAUSE_EXIT].x + cam_x, _button[PAUSE_EXIT].y + cam_y
		, _button[PAUSE_EXIT].width, _button[PAUSE_EXIT].height);

	if (PTIN_RECT(&_button[PAUSE_EXIT].rc, _ptMouse)) {
		if (KEYMANAGER->isStayKeyDown(VK_LBUTTON)) _pause_exitBtn = IMAGEMANAGER->findImage("pauseExitBtn3");
		else
			_pause_exitBtn = IMAGEMANAGER->findImage("pauseExitBtn2");

		if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON)) SCENEMANAGER->changeScene("타이틀");
	}
	else {
		_pause_exitBtn = IMAGEMANAGER->findImage("pauseExitBtn");
	}
}

void Ui::pauseUiRender()
{
	_blackBox->render(0 + cam_x, 0 + cam_y, 0.5f);

	//LOGO RENDER
	_logo->render(WINSIZEX / 2 - _logo->getWidth() / 2 + cam_x, WINSIZEY / 2 - 250 + cam_y);

	//BUTTON
	_pause_resumeBtn->render(WINSIZEX / 2 - _pause_gohomeBtn->getWidth() - _pause_resumeBtn->getWidth() - 15 + cam_x, WINSIZEY - 150 + cam_y);
	_pause_gohomeBtn->render(WINSIZEX / 2 - _pause_gohomeBtn->getWidth() - 5 + cam_x, WINSIZEY - 150 + cam_y);
	_pause_settingBtn->render(WINSIZEX / 2 + 5 + cam_x, WINSIZEY - 150 + cam_y);
	_pause_exitBtn->render(WINSIZEX / 2 + _pause_settingBtn->getWidth() + 15 + cam_x, WINSIZEY - 150 + cam_y);
}
#pragma endregion

#pragma region PLAYER INFO UI
void Ui::playerInfoUiUpdate()
{
	//플레이어의 자원 정보 업데이트
	_player_resource = _pl->get_playerResource();

	_button[PLAYER_INFO_MAP].x = 308 + (WINSIZEX / 2 - (_ptMouse.x + cam_x)) / 2 - (WINSIZEX / 2 - (_ptMouse.x + cam_x) - 200) / 2 + cam_x;
	_button[PLAYER_INFO_MAP].y = WINSIZEY / 2 - _playerInfo_window->getHeight() / 2 + 5 + cam_y;
	_button[PLAYER_INFO_MAP].width = WINSIZEX / 2 - _ptMouse.x + 288 + cam_x;
	_button[PLAYER_INFO_MAP].rc = D2DMANAGER->RectMake(_button[PLAYER_INFO_MAP].x, _button[PLAYER_INFO_MAP].y
		, _button[PLAYER_INFO_MAP].width / 2, _button[PLAYER_INFO_MAP].height);

	if (PTIN_RECT(&_button[PLAYER_INFO_MAP].rc, _ptMouse)) {
		if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON)) {
			_isMap = true;
			_isCharacter = false;
			_isEffects = false;
			_isStats = false;
		}

		if (KEYMANAGER->isStayKeyDown(VK_LBUTTON)) _playerInfo_mapBtn = IMAGEMANAGER->findImage("PlayerInfoMapBtn3");
		else if (_isMap) _playerInfo_mapBtn = IMAGEMANAGER->findImage("PlayerInfoMapBtn3");
		else _playerInfo_mapBtn = IMAGEMANAGER->findImage("PlayerInfoMapBtn2");

	}
	else {
		if (_isMap) _playerInfo_mapBtn = IMAGEMANAGER->findImage("PlayerInfoMapBtn3");
		else if (!_isMap) _playerInfo_mapBtn = IMAGEMANAGER->findImage("PlayerInfoMapBtn");
	}


	_button[PLAYER_INFO_CHARACTER].x = _button[PLAYER_INFO_MAP].x + _button[PLAYER_INFO_MAP].width / 2;
	_button[PLAYER_INFO_CHARACTER].y = WINSIZEY / 2 - _playerInfo_window->getHeight() / 2 + 5 + cam_y;
	_button[PLAYER_INFO_CHARACTER].rc = D2DMANAGER->RectMake(_button[PLAYER_INFO_CHARACTER].x, _button[PLAYER_INFO_CHARACTER].y
		, _button[PLAYER_INFO_CHARACTER].width, _button[PLAYER_INFO_CHARACTER].height);

	if (PTIN_RECT(&_button[PLAYER_INFO_CHARACTER].rc, _ptMouse)) {
		if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON)) {
			_isMap = false;
			_isCharacter = true;
			_isEffects = false;
			_isStats = false;
		}

		if (KEYMANAGER->isStayKeyDown(VK_LBUTTON)) _playerInfo_characterBtn = IMAGEMANAGER->findImage("PlayerInfoCharacterBtn3");
		else if (_isCharacter) _playerInfo_characterBtn = IMAGEMANAGER->findImage("PlayerInfoCharacterBtn3");
		else _playerInfo_characterBtn = IMAGEMANAGER->findImage("PlayerInfoCharacterBtn2");

	}
	else {
		if (_isCharacter) _playerInfo_characterBtn = IMAGEMANAGER->findImage("PlayerInfoCharacterBtn3");
		else if (!_isCharacter) _playerInfo_characterBtn = IMAGEMANAGER->findImage("PlayerInfoCharacterBtn");
	}


	_button[PLAYER_INFO_EFFECTS].x = _button[PLAYER_INFO_CHARACTER].x + _button[PLAYER_INFO_CHARACTER].width;
	_button[PLAYER_INFO_EFFECTS].y = WINSIZEY / 2 - _playerInfo_window->getHeight() / 2 + 5 + cam_y;
	_button[PLAYER_INFO_EFFECTS].rc = D2DMANAGER->RectMake(_button[PLAYER_INFO_EFFECTS].x, _button[PLAYER_INFO_EFFECTS].y
		, _button[PLAYER_INFO_EFFECTS].width, _button[PLAYER_INFO_EFFECTS].height);

	if (PTIN_RECT(&_button[PLAYER_INFO_EFFECTS].rc, _ptMouse)) {
		if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON)) {
			_isMap = false;
			_isCharacter = false;
			_isEffects = true;
			_isStats = false;
		}

		if (KEYMANAGER->isStayKeyDown(VK_LBUTTON)) _playerInfo_effectsBtn = IMAGEMANAGER->findImage("PlayerInfoEffectsBtn3");
		else if (_isEffects) _playerInfo_effectsBtn = IMAGEMANAGER->findImage("PlayerInfoEffectsBtn3");
		else _playerInfo_effectsBtn = IMAGEMANAGER->findImage("PlayerInfoEffectsBtn2");

	}
	else {
		if (_isEffects) _playerInfo_effectsBtn = IMAGEMANAGER->findImage("PlayerInfoEffectsBtn3");
		else if (!_isEffects) _playerInfo_effectsBtn = IMAGEMANAGER->findImage("PlayerInfoEffectsBtn");
	}


	_button[PLAYER_INFO_STATS].x = _button[PLAYER_INFO_EFFECTS].x + _button[PLAYER_INFO_EFFECTS].width;
	_button[PLAYER_INFO_STATS].y = WINSIZEY / 2 - _playerInfo_window->getHeight() / 2 + 5 + cam_y;
	_button[PLAYER_INFO_STATS].width = _playerInfo_statsBtn->getWidth() + 39;
	_button[PLAYER_INFO_STATS].rc = D2DMANAGER->RectMake(_button[PLAYER_INFO_STATS].x, _button[PLAYER_INFO_STATS].y
		, _button[PLAYER_INFO_STATS].width, _button[PLAYER_INFO_STATS].height);

	if (PTIN_RECT(&_button[PLAYER_INFO_STATS].rc, _ptMouse)) {
		if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON)) {
			_isMap = false;
			_isCharacter = false;
			_isEffects = false;
			_isStats = true;
		}

		if (KEYMANAGER->isStayKeyDown(VK_LBUTTON)) _playerInfo_statsBtn = IMAGEMANAGER->findImage("PlayerInfoStatsBtn3");
		else if (_isStats) _playerInfo_statsBtn = IMAGEMANAGER->findImage("PlayerInfoStatsBtn3");
		else _playerInfo_statsBtn = IMAGEMANAGER->findImage("PlayerInfoStatsBtn2");

	}
	else {
		if (_isStats) _playerInfo_statsBtn = IMAGEMANAGER->findImage("PlayerInfoStatsBtn3");
		else if (!_isStats) _playerInfo_statsBtn = IMAGEMANAGER->findImage("PlayerInfoStatsBtn");
	}


	_button[PLAYER_INFO_EXIT].rc = D2DMANAGER->RectMake(_button[PLAYER_INFO_EXIT].x + cam_x, _button[PLAYER_INFO_EXIT].y + cam_y
		, _button[PLAYER_INFO_EXIT].width, _button[PLAYER_INFO_EXIT].height);

	if (PTIN_RECT(&_button[PLAYER_INFO_EXIT].rc, _ptMouse)) {
		if (KEYMANAGER->isStayKeyDown(VK_LBUTTON)) _playerInfo_exitBtn = IMAGEMANAGER->findImage("PlayerInfoExitBtn3");
		else
		_playerInfo_exitBtn = IMAGEMANAGER->findImage("PlayerInfoExitBtn2");

		if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON)) _isInfo = false;
	}
	else {
		_playerInfo_exitBtn = IMAGEMANAGER->findImage("PlayerInfoExitBtn");
	}
}

void Ui::playerInfoUiRender()
{
	//CHARACTER INFO(캐릭터 정보창)
	_playerInfo_window->render(
		WINSIZEX / 2 - _playerInfo_window->getWidth() / 2 + cam_x, 
		WINSIZEY / 2 - _playerInfo_window->getHeight() / 2 + cam_y
	);
	_playerInfo_ui->render(
		WINSIZEX / 2 - _playerInfo_window->getWidth() / 2 + 5 + cam_x,
		WINSIZEY / 2 - _playerInfo_window->getHeight() / 2 + 48 + cam_y
	);

	if (_isMap) {
		_playerInfo_ui = IMAGEMANAGER->findImage("PlayerInfoMap");
	}
	else if (_isCharacter) {
		_playerInfo_ui = IMAGEMANAGER->findImage("PlayerInfoCharacter");
		
		WCHAR levelInfo[256];
		//JOB ICON RENDER
		if (_pl->get_playerStatus().player_class == Player_Class::Paladin) {
			
			_paladin_skill1->render(WINSIZEX / 2 - _playerInfo_window->getWidth() / 2 + 124 + cam_x, WINSIZEY / 2 + _playerInfo_window->getHeight() / 2 - 66 + cam_y);
			_paladin_skill2->render(WINSIZEX / 2 - _playerInfo_window->getWidth() / 2 + 191 + cam_x, WINSIZEY / 2 + _playerInfo_window->getHeight() / 2 - 66 + cam_y);

			_playerInfo_paladin->render(WINSIZEX / 2 - _playerInfo_window->getWidth() / 2 + 38 + cam_x,
				WINSIZEY / 2 - _playerInfo_window->getHeight() / 2 + 60 + cam_y);

			swprintf_s(levelInfo, L"Phand the Novice, a level %d paladin ", _pl->get_playerStatus().level);
			D2DMANAGER->DrawTextD2DCenter(D2DMANAGER->CreateBrush(0xffffff), L"DOSGothic", 25.0f, levelInfo, 620, 200, 1100, 300);

		}
		else if (_pl->get_playerStatus().player_class == Player_Class::Ranger) {

			_ranger_skill1->render(WINSIZEX / 2 - _playerInfo_window->getWidth() / 2 + 124 + cam_x, WINSIZEY / 2 + _playerInfo_window->getHeight() / 2 - 66 + cam_y);
			_ranger_skill2->render(WINSIZEX / 2 - _playerInfo_window->getWidth() / 2 + 191 + cam_x, WINSIZEY / 2 + _playerInfo_window->getHeight() / 2 - 66 + cam_y);

			_playerInfo_ranger->render(WINSIZEX / 2 - _playerInfo_window->getWidth() / 2 + 38 + cam_x,
				WINSIZEY / 2 - _playerInfo_window->getHeight() / 2 + 60 + cam_y);

			swprintf_s(levelInfo, L"Aura the Journeyman, a level %d ranger ", _pl->get_playerStatus().level);
			D2DMANAGER->DrawTextD2DCenter(D2DMANAGER->CreateBrush(0xffffff), L"DOSGothic", 25.0f, levelInfo, 620, 200, 1100, 300);
		}
		
		int itemNum = _player_resource.inventory.size();

		if (!_isCharacterInventory) {
			for (int i = 0; i < itemNum; i++)
			{
				int k = i / 4;
				int j = i % 4;
				ITEMMANAGER->addItemCenterInventory(DF_inventoryXInit + cam_x + DF_inventoryX * j, DF_inventoryYInit + cam_y + DF_inventoryY * k, _player_resource.inventory[i], 2);
			}
			_isCharacterInventory = true;
		}


		//POTION
		if (_pl->get_playerResource()._potion.crrentHave == _pl->get_playerResource()._potion.maxHave) _potion->render(WINSIZEX / 2 - _playerInfo_window->getWidth() / 2 + 24 + cam_x, WINSIZEY / 2 + _playerInfo_window->getHeight() / 2 - 66 + cam_y);
		else if (_pl->get_playerResource()._potion.crrentHave > 0) _potion_half->render(WINSIZEX / 2 - _playerInfo_window->getWidth() / 2 + 24 + cam_x, WINSIZEY / 2 + _playerInfo_window->getHeight() / 2 - 66 + cam_y);
		
		switch (_pl->get_playerResource()._potion.maxHave) {
		case 1:
			if (_pl->get_playerResource()._potion.maxHave == _pl->get_playerResource()._potion.crrentHave) _playing_potion_gauge1->render(WINSIZEX / 2 - _playerInfo_window->getWidth() / 2 + 26.5 + cam_x, WINSIZEY / 2 + _playerInfo_window->getHeight() / 2 - 14 + cam_y);
			break;
		}


		//TEXT RENDER
		WCHAR playTime[256];
		WCHAR health[256];
		WCHAR healthRegen[256];
		WCHAR mana[256];
		WCHAR manaRegen[256];
		WCHAR speed[256];
		WCHAR exp[256];
		WCHAR attackDamage[256];
		WCHAR abilityPower[256];
		WCHAR criticalChance[256];
		WCHAR evadeChance[256];
		WCHAR armor[256];
		WCHAR resistance[256];
		WCHAR luck[256];
		WCHAR goldGain[256];
		WCHAR oreGain[256];
		WCHAR gold[256];
		WCHAR ore[256];
		WCHAR bronzeKey[256];
		WCHAR silverKey[256];
		WCHAR goldenKey[256];
		WCHAR redKey[256];

		swprintf_s(levelInfo, L"%d hour, %d minute", (int)_pl->get_playerInfo()._playTime / 3600,  (int)_pl->get_playerInfo()._playTime % 3600 / 60);
		D2DMANAGER->DrawTextD2DCenter(D2DMANAGER->CreateBrush(0xffffff), L"DOSGothic", 25.0f, levelInfo, 620, 228, 1100, 300);

		swprintf_s(health, L"%.0f", _pl->get_playerStatus().hp);
		D2DMANAGER->DrawTextD2DCenter(D2DMANAGER->CreateBrush(0xffffff), L"DOSGothic", 25.0f, health, 455, 320, 585, 500);
		swprintf_s(healthRegen, L"%.2f", _pl->get_playerStatus().hp_regen);
		D2DMANAGER->DrawTextD2DCenter(D2DMANAGER->CreateBrush(0xffffff), L"DOSGothic", 25.0f, healthRegen, 455, 353, 585, 500);
		swprintf_s(mana, L"%.0f", _pl->get_playerStatus().mp);
		D2DMANAGER->DrawTextD2DCenter(D2DMANAGER->CreateBrush(0xffffff), L"DOSGothic", 25.0f, mana, 580, 320, 715, 500);
		swprintf_s(manaRegen, L"%.2f", _pl->get_playerStatus().mp_regen);
		D2DMANAGER->DrawTextD2DCenter(D2DMANAGER->CreateBrush(0xffffff), L"DOSGothic", 25.0f, manaRegen, 585, 353, 715, 500);
		swprintf_s(speed, L"%.2f", _pl->get_playerStatus().move_speed);
		D2DMANAGER->DrawTextD2DCenter(D2DMANAGER->CreateBrush(0xffffff), L"DOSGothic", 25.0f, speed, 750, 338, 880, 500);
		swprintf_s(exp, L"%.0f", _pl->get_playerStatus().exp);
		D2DMANAGER->DrawTextD2DCenter(D2DMANAGER->CreateBrush(0xffffff), L"DOSGothic", 25.0f, exp, 875, 338, 1005, 500);
		swprintf_s(attackDamage, L"%.0f", _pl->get_playerStatus().attack_dmg);
		D2DMANAGER->DrawTextD2DCenter(D2DMANAGER->CreateBrush(0xffffff), L"DOSGothic", 25.0f, attackDamage, 455, 445, 585, 630);
		swprintf_s(abilityPower, L"%.0f", _pl->get_playerStatus().ability_power);
		D2DMANAGER->DrawTextD2DCenter(D2DMANAGER->CreateBrush(0xffffff), L"DOSGothic", 25.0f, abilityPower, 605, 445, 735, 630);
		swprintf_s(criticalChance, L"%.0f", _pl->get_playerStatus().crit);
		D2DMANAGER->DrawTextD2DCenter(D2DMANAGER->CreateBrush(0xffffff), L"DOSGothic", 25.0f, criticalChance, 750, 445, 880, 630);
		swprintf_s(evadeChance, L"%.1f%%", _pl->get_playerStatus().evasion);
		D2DMANAGER->DrawTextD2DCenter(D2DMANAGER->CreateBrush(0xffffff), L"DOSGothic", 25.0f, evadeChance, 885, 445, 1015, 630);
		swprintf_s(armor, L"%.0f", _pl->get_playerStatus().armor);
		D2DMANAGER->DrawTextD2DCenter(D2DMANAGER->CreateBrush(0xffffff), L"DOSGothic", 25.0f, armor, 455, 481, 585, 666);
		swprintf_s(resistance, L"%.0f", _pl->get_playerStatus().resistance);
		D2DMANAGER->DrawTextD2DCenter(D2DMANAGER->CreateBrush(0xffffff), L"DOSGothic", 25.0f, resistance, 605, 481, 735, 666);
		swprintf_s(luck, L"%.0f", _pl->get_playerStatus().luck);
		D2DMANAGER->DrawTextD2DCenter(D2DMANAGER->CreateBrush(0xffffff), L"DOSGothic", 25.0f, luck, 885, 481, 1015, 666);
		
		swprintf_s(goldGain, L"%d", _pl->get_DungeonResource().gold);
		D2DMANAGER->DrawTextD2DCenter(D2DMANAGER->CreateBrush(0xffffff), L"DOSGothic", 25.0f, goldGain, 455, 567, 585, 700);
		swprintf_s(oreGain, L"%d", _pl->get_DungeonResource().ore);
		D2DMANAGER->DrawTextD2DCenter(D2DMANAGER->CreateBrush(0xffffff), L"DOSGothic", 25.0f, oreGain, 580, 567, 735, 700);
		swprintf_s(gold, L"%d", _pl->get_playerResource().gold);
		D2DMANAGER->DrawTextD2DCenter(D2DMANAGER->CreateBrush(0xffffff), L"DOSGothic", 25.0f, gold, 455, 605, 585, 700);
		swprintf_s(ore, L"%d", _pl->get_playerResource().ore);
		D2DMANAGER->DrawTextD2DCenter(D2DMANAGER->CreateBrush(0xffffff), L"DOSGothic", 25.0f, ore, 580, 605, 735, 700);

		swprintf_s(bronzeKey, L"%d", _pl->get_playerResource().bronze_key);
		D2DMANAGER->DrawTextD2DCenter(D2DMANAGER->CreateBrush(0xffffff), L"DOSGothic", 25.0f, bronzeKey, 665, 605, 820, 700);
		swprintf_s(silverKey, L"%d", _pl->get_playerResource().silver_key);
		D2DMANAGER->DrawTextD2DCenter(D2DMANAGER->CreateBrush(0xffffff), L"DOSGothic", 25.0f, silverKey, 735, 605, 895, 700);
		swprintf_s(goldenKey, L"%d", _pl->get_playerResource().gold_key);
		D2DMANAGER->DrawTextD2DCenter(D2DMANAGER->CreateBrush(0xffffff), L"DOSGothic", 25.0f, goldenKey, 807, 605, 972, 700);
		swprintf_s(redKey, L"%d", _pl->get_playerResource().red_key);
		D2DMANAGER->DrawTextD2DCenter(D2DMANAGER->CreateBrush(0xffffff), L"DOSGothic", 25.0f, redKey, 885, 605, 1035, 700);

	}
	else if (_isEffects) {
		_playerInfo_ui = IMAGEMANAGER->findImage("PlayerInfoEffects");
	}
	else if (_isStats) {
		
		_playerInfo_ui = IMAGEMANAGER->findImage("PlayerInfoStats");
		
		WCHAR levelInfo[256];
		WCHAR playTime[256];
		//JOB ICON RENDER
		if (_pl->get_playerStatus().player_class == Player_Class::Paladin) {

			_playerInfo_paladin->render(WINSIZEX / 2 - _playerInfo_window->getWidth() / 2 + 38 + cam_x,
				WINSIZEY / 2 - _playerInfo_window->getHeight() / 2 + 60 + cam_y);

			swprintf_s(levelInfo, L"Phand the Novice, a level %d paladin ", _pl->get_playerStatus().level);
			D2DMANAGER->DrawTextD2DCenter(D2DMANAGER->CreateBrush(0xffffff), L"DOSGothic", 25.0f, levelInfo, 620, 200, 1100, 300);

		}
		else if (_pl->get_playerStatus().player_class == Player_Class::Ranger) {

			_playerInfo_ranger->render(WINSIZEX / 2 - _playerInfo_window->getWidth() / 2 + 38 + cam_x,
				WINSIZEY / 2 - _playerInfo_window->getHeight() / 2 + 60 + cam_y);

			swprintf_s(levelInfo, L"Aura the Journeyman, a level %d ranger ", _pl->get_playerStatus().level);
			D2DMANAGER->DrawTextD2DCenter(D2DMANAGER->CreateBrush(0xffffff), L"DOSGothic", 25.0f, levelInfo, 620, 200, 1100, 300);
		}


		swprintf_s(levelInfo, L"%d hour, %d minute", (int)_pl->get_playerInfo()._playTime / 3600, (int)_pl->get_playerInfo()._playTime % 3600 / 60);
		D2DMANAGER->DrawTextD2DCenter(D2DMANAGER->CreateBrush(0xffffff), L"DOSGothic", 25.0f, levelInfo, 620, 228, 1100, 300);
	}


	//BUTTON
	float mapBtnX_MOVE = 308 + (WINSIZEX / 2 - (_ptMouse.x-cam_x)) / 2;
	float mapBtnX_CUT = -(WINSIZEX / 2 - (_ptMouse.x-cam_x) - 200) / 2;
	if (mapBtnX_CUT < 0) { mapBtnX_CUT = 0; mapBtnX_MOVE = 407; }
	else if (mapBtnX_CUT > _playerInfo_mapBtn->getWidth()-10) { mapBtnX_CUT = _playerInfo_mapBtn->getWidth()-10;  mapBtnX_MOVE = 173; }
	_playerInfo_mapBtn->renderUI(mapBtnX_MOVE + cam_x
								,WINSIZEY / 2 - _playerInfo_window->getHeight() / 2 + 5 + cam_y
								,0 
								,0
								,mapBtnX_CUT
								,0);

	_playerInfo_characterBtn->render(mapBtnX_MOVE + _playerInfo_mapBtn->getWidth() + cam_x, WINSIZEY / 2 - _playerInfo_window->getHeight() / 2 + 5 + cam_y);
	_playerInfo_effectsBtn->render(mapBtnX_MOVE + _playerInfo_mapBtn->getWidth() + _playerInfo_characterBtn->getWidth() + cam_x, WINSIZEY / 2 - _playerInfo_window->getHeight() / 2 + 5 + cam_y);
	
	float statsBtnX_CUT = (WINSIZEX / 2 - (_ptMouse.x-cam_x) + 200) / 2;
	if (statsBtnX_CUT < 0) statsBtnX_CUT = 0;
	else if (statsBtnX_CUT > _playerInfo_statsBtn->getWidth()-10) statsBtnX_CUT = _playerInfo_statsBtn->getWidth() - 10;
	_playerInfo_statsBtn->renderUI(mapBtnX_MOVE + _playerInfo_mapBtn->getWidth() + _playerInfo_characterBtn->getWidth() + _playerInfo_effectsBtn->getWidth() + cam_x
								,WINSIZEY / 2 - _playerInfo_window->getHeight() / 2 + 5 + cam_y
								,statsBtnX_CUT
								,0
								,0
								,0);

	_playerInfo_exitBtn->render(WINSIZEX / 2 + _playerInfo_window->getWidth() / 2 - _playerInfo_exitBtn->getWidth() - 5 + cam_x,
		WINSIZEY / 2 - _playerInfo_window->getHeight() / 2 + 5 + cam_y);
}
#pragma endregion

#pragma region INN UI
void Ui::innUiUpdate()
{

}
void Ui::innUiRender()
{
	_npc_inn_ui->render(WINSIZEX / 2 - _npc_inn_ui->getWidth() / 2 + cam_x, WINSIZEY / 2 - _npc_inn_ui->getHeight() / 2 + cam_y);

}
#pragma endregion

#pragma region SKILL UI
void Ui::skillUiUpdate()
{

}
void Ui::skillUiRender()
{
	_npc_skill_ui->render(WINSIZEX / 2 - _npc_skill_ui->getWidth() / 2, WINSIZEY / 2 - _npc_skill_ui->getHeight() / 2);
}
#pragma endregion

#pragma region BLACKSMITH UI
void Ui::blackSmithUiUpdate()
{

}
void Ui::blackSmithUiRender()
{
	_npc_blackSmith_ui->render(WINSIZEX / 2 - _npc_blackSmith_ui->getWidth() / 2 + cam_x, WINSIZEY / 2 - _npc_blackSmith_ui->getHeight() / 2 + cam_y);

}
#pragma endregion

#pragma region ADD IMAGE
void Ui::addImage()
{
	//============================
	//         TITLE UI
	//============================
	{
		_title_profiles = IMAGEMANAGER->addImage("title_profilesBtn", L"image/ui/TITLE_PROFILES.png", 43, 43);
		IMAGEMANAGER->addImage("title_profilesBtn2", L"image/ui/TITLE_PROFILES2.png", 43, 43);
		IMAGEMANAGER->addImage("title_profilesBtn3", L"image/ui/TITLE_PROFILES3.png", 43, 43);
		_title_play = IMAGEMANAGER->addImage("title_playBtn", L"image/ui/TITLE_SINGLEPLAY.png", 154, 43);
		IMAGEMANAGER->addImage("title_playBtn2", L"image/ui/TITLE_SINGLEPLAY2.png", 154, 43);
		IMAGEMANAGER->addImage("title_playBtn3", L"image/ui/TITLE_SINGLEPLAY3.png", 154, 43);
		_title_option = IMAGEMANAGER->addImage("title_optionBtn", L"image/ui/TITLE_SETTING.png", 154, 43);
		IMAGEMANAGER->addImage("title_optionBtn2", L"image/ui/TITLE_SETTING2.png", 154, 43);
		IMAGEMANAGER->addImage("title_optionBtn3", L"image/ui/TITLE_SETTING3.png", 154, 43);
		_title_exit = IMAGEMANAGER->addImage("title_exitBtn", L"image/ui/TITLE_EXIT.png", 154, 43);
		IMAGEMANAGER->addImage("title_exitBtn2", L"image/ui/TITLE_EXIT2.png", 154, 43);
		IMAGEMANAGER->addImage("title_exitBtn3", L"image/ui/TITLE_EXIT3.png", 154, 43);
		_title_mapEdit = IMAGEMANAGER->addImage("title_mapEditBtn", L"image/ui/TITLE_MAPEDIT.png", 43, 43);
		IMAGEMANAGER->addImage("title_mapEditBtn2", L"image/ui/TITLE_MAPEDIT2.png", 43, 43);
		IMAGEMANAGER->addImage("title_mapEditBtn3", L"image/ui/TITLE_MAPEDIT3.png", 43, 43);
	}

	//============================
	//	   CHARACTER LIST UI
	//============================
	{
		_characterListUi = IMAGEMANAGER->addImage("characterList_UI", L"image/ui/CHARACTERLIST_UI.png", 960, 490);

		_characterListBox[0] = IMAGEMANAGER->addImage("characterList_Box", L"image/ui/CHARACTERLIST_BOX.png", 917, 86);
		IMAGEMANAGER->addImage("characterList_Box2", L"image/ui/CHARACTERLIST_BOX2.png", 917, 86);
		IMAGEMANAGER->addImage("characterList_Box3", L"image/ui/CHARACTERLIST_BOX3.png", 917, 86);

		_characterList_ranger_picture = IMAGEMANAGER->addImage("characterList_ranger_picture", L"image/ui/CHARACTERLIST_RANGER_PICTURE.png", 58, 58);
		_characterList_ranger_icon = IMAGEMANAGER->addImage("characterList_ranger_icon", L"image/ui/CHARACTERLIST_RANGER_ICON.png", 59, 58);
		_characterList_paladin_picture = IMAGEMANAGER->addImage("characterList_paladin_picture", L"image/ui/CHARACTERLIST_PALADIN_PICTURE.png", 58, 58);
		_characterList_paladin_icon = IMAGEMANAGER->addImage("characterList_paladin_icon", L"image/ui/CHARACTERLIST_PALADIN_ICON.png", 59, 58);

		_characterList_new = IMAGEMANAGER->addImage("characterList_new", L"image/ui/CHARACTERLIST_NEW.png", 316, 43);
		IMAGEMANAGER->addImage("characterList_new2", L"image/ui/CHARACTERLIST_NEW2.png", 316, 43);
		IMAGEMANAGER->addImage("characterList_new3", L"image/ui/CHARACTERLIST_NEW3.png", 316, 43);
		_characterList_play = IMAGEMANAGER->addImage("characterList_play", L"image/ui/CHARACTERLIST_PLAY.png", 244, 43);
		IMAGEMANAGER->addImage("characterList_play2", L"image/ui/CHARACTERLIST_PLAY2.png", 244, 43);
		IMAGEMANAGER->addImage("characterList_play3", L"image/ui/CHARACTERLIST_PLAY3.png", 244, 43);
		_characterList_tresh = IMAGEMANAGER->addImage("characterList_tresh", L"image/ui/CHARACTERLIST_TRESH.png", 45, 43);
		IMAGEMANAGER->addImage("characterList_tresh2", L"image/ui/CHARACTERLIST_TRESH2.png", 46, 43);
		IMAGEMANAGER->addImage("characterList_tresh3", L"image/ui/CHARACTERLIST_TRESH3.png", 46, 43);
	}

	//============================
	//    CHARACTER CREATE UI
	//============================
	{
		_characterCreateUi = IMAGEMANAGER->addImage("characterCreate_Ui", L"image/ui/CHARACTERCREATE_UI.png", 672, 252);
		_characterCreate_paladin = IMAGEMANAGER->addImage("characterCreate_paladin", L"image/ui/CHARACTERCREATE_PALADIN.png", 58, 58);
		IMAGEMANAGER->addImage("characterCreate_paladin2", L"image/ui/CHARACTERCREATE_PALADIN2.png", 58, 58);
		IMAGEMANAGER->addImage("characterCreate_paladin3", L"image/ui/CHARACTERCREATE_PALADIN3.png", 58, 58);
		_characterCreate_paladin_skill[0] = IMAGEMANAGER->addImage("characterCreate_paladin_skill1", L"image/ui/CHARACTERCREATE_PALADIN_SKILL1.png", 58, 58);
		_characterCreate_paladin_skill[1] = IMAGEMANAGER->addImage("characterCreate_paladin_skill2", L"image/ui/CHARACTERCREATE_PALADIN_SKILL2.png", 58, 58);
		_characterCreate_paladin_skill[2] = IMAGEMANAGER->addImage("characterCreate_paladin_skill3", L"image/ui/CHARACTERCREATE_PALADIN_SKILL3.png", 58, 58);
		_characterCreate_paladin_skill[3] = IMAGEMANAGER->addImage("characterCreate_paladin_skill4", L"image/ui/CHARACTERCREATE_PALADIN_SKILL4.png", 58, 58);
		_characterCreate_paladin_skill[4] = IMAGEMANAGER->addImage("characterCreate_paladin_skill5", L"image/ui/CHARACTERCREATE_PALADIN_SKILL5.png", 58, 58);
		_characterCreate_paladin_skill[5] = IMAGEMANAGER->addImage("characterCreate_paladin_skill6", L"image/ui/CHARACTERCREATE_PALADIN_SKILL6.png", 58, 58);
		_characterCreate_paladin_skill[6] = IMAGEMANAGER->addImage("characterCreate_paladin_skill7", L"image/ui/CHARACTERCREATE_PALADIN_SKILL7.png", 58, 58);

		_characterCreate_ranger = IMAGEMANAGER->addImage("characterCreate_ranger", L"image/ui/CHARACTERCREATE_RANGER.png", 58, 58);
		IMAGEMANAGER->addImage("characterCreate_ranger2", L"image/ui/CHARACTERCREATE_RANGER2.png", 58, 58);
		IMAGEMANAGER->addImage("characterCreate_ranger3", L"image/ui/CHARACTERCREATE_RANGER3.png", 58, 58);
		_characterCreate_ranger_skill[0] = IMAGEMANAGER->addImage("characterCreate_ranger_skill1", L"image/ui/CHARACTERCREATE_RANGER_SKILL1.png", 58, 58);
		_characterCreate_ranger_skill[1] = IMAGEMANAGER->addImage("characterCreate_ranger_skill2", L"image/ui/CHARACTERCREATE_RANGER_SKILL2.png", 58, 58);
		_characterCreate_ranger_skill[2] = IMAGEMANAGER->addImage("characterCreate_ranger_skill3", L"image/ui/CHARACTERCREATE_RANGER_SKILL3.png", 58, 58);
		_characterCreate_ranger_skill[3] = IMAGEMANAGER->addImage("characterCreate_ranger_skill4", L"image/ui/CHARACTERCREATE_RANGER_SKILL4.png", 58, 58);
		_characterCreate_ranger_skill[4] = IMAGEMANAGER->addImage("characterCreate_ranger_skill5", L"image/ui/CHARACTERCREATE_RANGER_SKILL5.png", 58, 58);
		_characterCreate_ranger_skill[5] = IMAGEMANAGER->addImage("characterCreate_ranger_skill6", L"image/ui/CHARACTERCREATE_RANGER_SKILL6.png", 58, 58);
		_characterCreate_ranger_skill[6] = IMAGEMANAGER->addImage("characterCreate_ranger_skill7", L"image/ui/CHARACTERCREATE_RANGER_SKILL7.png", 58, 58);

		_characterCreate_play = IMAGEMANAGER->addImage("characterCreate_play", L"image/ui/CHARACTERCREATE_PLAY.png", 245, 43);
		IMAGEMANAGER->addImage("characterCreate_play2", L"image/ui/CHARACTERCREATE_PLAY2.png", 245, 43);
		IMAGEMANAGER->addImage("characterCreate_play3", L"image/ui/CHARACTERCREATE_PLAY3.png", 245, 43);
	}

	//============================
	//	    VOLUME SETTING UI
	//============================
	{
		_volumeUi = IMAGEMANAGER->addImage("volume_UI", L"image/ui/VOLUME_UI.png", 727, 144);

		//사운드 조절버튼
		_volume_button = IMAGEMANAGER->addImage("volume_button", L"image/ui/VOLUME_BUTTON.png", 22, 32);
		
		//그 이외의 버튼들
		_volume_reset = IMAGEMANAGER->addImage("volume_reset1", L"image/ui/VOLUME_RESET1.png", 192, 36);
		IMAGEMANAGER->addImage("volume_reset2", L"image/ui/VOLUME_RESET2.png", 192, 36);
		IMAGEMANAGER->addImage("volume_reset3", L"image/ui/VOLUME_RESET3.png", 192, 36);
		_volume_accept = IMAGEMANAGER->addImage("volume_accept1", L"image/ui/VOLUME_ACCEPT1.png", 192, 36);
		IMAGEMANAGER->addImage("volume_accept2", L"image/ui/VOLUME_ACCEPT2.png", 192, 36);
		IMAGEMANAGER->addImage("volume_accept3", L"image/ui/VOLUME_ACCEPT3.png", 192, 36);
		_volume_exit = IMAGEMANAGER->addImage("volume_exit1", L"image/ui/VOLUME_EXIT1.png", 36, 36);
		IMAGEMANAGER->addImage("volume_exit2", L"image/ui/VOLUME_EXIT2.png", 36, 36);
		IMAGEMANAGER->addImage("volume_exit3", L"image/ui/VOLUME_EXIT3.png", 36, 36);
	}

	//============================
	//        PLAYING UI
	//============================
	{
		//BAR (Playing)
		_leftBar = IMAGEMANAGER->addImage("leftBar", L"image/ui/PLAYING_LEFTBAR.png", 134, 442);
		_rightBar = IMAGEMANAGER->addImage("rightBar", L"image/ui/PLAYING_RIGHTBAR.png", 134, 322);
		_upBar = IMAGEMANAGER->addImage("upBar", L"image/ui/PLAYING_UPBAR.png", 490, 46);

		//ICON (Paladin)
		_paladin = IMAGEMANAGER->addImage("paladin_UI", L"image/ui/PLAYING_PALADIN.png", 57, 43);
		_paladin_skill1 = IMAGEMANAGER->addImage("paladin_skill1", L"image/ui/PLAYING_PALADIN_SKILL1.png", 57, 57);
		_paladin_skill1_cooltime = IMAGEMANAGER->addImage("paladin_skill1_cooltime", L"image/ui/PLAYING_PALADIN_SKILL1_COOLTIME.png", 57, 57);
		_paladin_skill2 = IMAGEMANAGER->addImage("paladin_skill2", L"image/ui/PLAYING_PALADIN_SKILL2.png", 57, 57);
		_paladin_skill2_cooltime = IMAGEMANAGER->addImage("paladin_skill2_cooltime", L"image/ui/PLAYING_PALADIN_SKILL2_COOLTIME.png", 57, 57);

		//ICON (Ranger)
		_ranger = IMAGEMANAGER->addImage("ranger_UI", L"image/ui/PLAYING_RANGER.png", 57, 43);
		_ranger_skill1 = IMAGEMANAGER->addImage("ranger_skill1", L"image/ui/PLAYING_RANGER_SKILL1.png", 57, 57);
		_ranger_skill2 = IMAGEMANAGER->addImage("ranger_skill2", L"image/ui/PLAYING_RANGER_SKILL2.png", 57, 57);
		_ranger_skill2_cooltime = IMAGEMANAGER->addImage("ranger_skill2_cooltime", L"image/ui/PLAYING_RANGER_SKILL2_COOLTIME.png", 57, 57);

		//ICON (Cooltime End)
		_playing_cooltime_end = IMAGEMANAGER->addImage("cooltimeEnd", L"image/ui/PLAYING_COOLTIME_END.png", 57, 57);

		//ICON (Potion)
		_potion = IMAGEMANAGER->addImage("potion", L"image/ui/PLAYING_POTION.png", 57, 50);
		_potion_half = IMAGEMANAGER->addImage("potion_half", L"image/ui/PLAYING_POTION_HALF.png", 57, 50);

		//Gauge BAR
		_playing_hpBar = IMAGEMANAGER->addImage("hpBar1", L"image/ui/PLAYING_HP.png", 21, 185);
		_playing_mpBar = IMAGEMANAGER->addImage("mpBar1", L"image/ui/PLAYING_MP.png", 21, 185);
		_playing_hpBar2 = IMAGEMANAGER->addImage("hpBar2", L"image/ui/PLAYING_HP2.png", 53, 2);
		_playing_mpBar2 = IMAGEMANAGER->addImage("mpBar2", L"image/ui/PLAYING_MP2.png", 53, 2);
		_playing_expBar = IMAGEMANAGER->addImage("expBar", L"image/ui/PLAYING_EXPERIENCE.png", 5, 259);

		_playing_potion_gauge1 = IMAGEMANAGER->addImage("potionGauge1", L"image/ui/PLAYING_POTION_GAUGE1.png", 53, 3);
	}

	//============================
	//          PAUSE UI
	//============================
	{
		//LOGO
		_logo = IMAGEMANAGER->addImage("LOGO", L"image/ui/ESC_LOGO.png", 714, 167);

		//BLACK BOX
		_blackBox = IMAGEMANAGER->addImage("BLACKBOX", L"image/ui/ESC_BLACK.png", 1600, 900);

		//BUTTON
		_pause_resumeBtn = IMAGEMANAGER->addImage("pauseResumeBtn", L"image/ui/PAUSE_RESUME_BUTTON.png", 128, 36);
		IMAGEMANAGER->addImage("pauseResumeBtn2", L"image/ui/PAUSE_RESUME_BUTTON2.png", 128, 36);
		IMAGEMANAGER->addImage("pauseResumeBtn3", L"image/ui/PAUSE_RESUME_BUTTON3.png", 128, 36);

		_pause_gohomeBtn = IMAGEMANAGER->addImage("pauseGohomeBtn", L"image/ui/PAUSE_GOHOME_BUTTON.png", 128, 36);
		IMAGEMANAGER->addImage("pauseGohomeBtn2", L"image/ui/PAUSE_GOHOME_BUTTON2.png", 128, 36);
		IMAGEMANAGER->addImage("pauseGohomeBtn3", L"image/ui/PAUSE_GOHOME_BUTTON3.png", 128, 36);

		_pause_settingBtn = IMAGEMANAGER->addImage("pauseSettingBtn", L"image/ui/PAUSE_SETTING_BUTTON.png", 128, 36);
		IMAGEMANAGER->addImage("pauseSettingBtn2", L"image/ui/PAUSE_SETTING_BUTTON2.png", 128, 36);
		IMAGEMANAGER->addImage("pauseSettingBtn3", L"image/ui/PAUSE_SETTING_BUTTON3.png", 128, 36);

		_pause_exitBtn = IMAGEMANAGER->addImage("pauseExitBtn", L"image/ui/PAUSE_EXIT_BUTTON.png", 128, 36);
		IMAGEMANAGER->addImage("pauseExitBtn2", L"image/ui/PAUSE_EXIT_BUTTON2.png", 128, 36);
		IMAGEMANAGER->addImage("pauseExitBtn3", L"image/ui/PAUSE_EXIT_BUTTON3.png", 128, 36);
	}

	//=============================
	//       PLAYER INFO UI
	//=============================
	{
		//WINDOW
		_playerInfo_window = IMAGEMANAGER->addImage("PlayerInfoWindow", L"image/ui/PLAYERINFO_WINDOW.png", 796, 619);
		_playerInfo_ui = IMAGEMANAGER->addImage("PlayerInfoCharacter", L"image/ui/PLAYERINFO_CHARACTER.png", 786, 566);
		IMAGEMANAGER->addImage("PlayerInfoMap", L"image/ui/PLAYERINFO_MAP.png", 786, 566);
		IMAGEMANAGER->addImage("PlayerInfoEffects", L"image/ui/PLAYERINFO_EFFECTS.png", 786, 566);
		IMAGEMANAGER->addImage("PlayerInfoStats", L"image/ui/PLAYERINFO_STATS.png", 786, 566);

		//BUTTONS
		_playerInfo_mapBtn = IMAGEMANAGER->addImage("PlayerInfoMapBtn", L"image/ui/PLAYERINFO_MAPBUTTON.png", 245, 43);
		IMAGEMANAGER->addImage("PlayerInfoMapBtn2", L"image/ui/PLAYERINFO_MAPBUTTON2.png", 245, 43);
		IMAGEMANAGER->addImage("PlayerInfoMapBtn3", L"image/ui/PLAYERINFO_MAPBUTTON3.png", 245, 43);

		_playerInfo_characterBtn = IMAGEMANAGER->addImage("PlayerInfoCharacterBtn", L"image/ui/PLAYERINFO_CHARACTERBUTTON.png", 245, 43);
		IMAGEMANAGER->addImage("PlayerInfoCharacterBtn2", L"image/ui/PLAYERINFO_CHARACTERBUTTON2.png", 245, 43);
		IMAGEMANAGER->addImage("PlayerInfoCharacterBtn3", L"image/ui/PLAYERINFO_CHARACTERBUTTON3.png", 245, 43);

		_playerInfo_effectsBtn = IMAGEMANAGER->addImage("PlayerInfoEffectsBtn", L"image/ui/PLAYERINFO_EFFECTSBUTTON.png", 245, 43);
		IMAGEMANAGER->addImage("PlayerInfoEffectsBtn2", L"image/ui/PLAYERINFO_EFFECTSBUTTON2.png", 245, 43);
		IMAGEMANAGER->addImage("PlayerInfoEffectsBtn3", L"image/ui/PLAYERINFO_EFFECTSBUTTON3.png", 245, 43);

		_playerInfo_statsBtn = IMAGEMANAGER->addImage("PlayerInfoStatsBtn", L"image/ui/PLAYERINFO_STATSBUTTON.png", 245, 43);
		IMAGEMANAGER->addImage("PlayerInfoStatsBtn2", L"image/ui/PLAYERINFO_STATSBUTTON2.png", 245, 43);
		IMAGEMANAGER->addImage("PlayerInfoStatsBtn3", L"image/ui/PLAYERINFO_STATSBUTTON3.png", 245, 43);


		_playerInfo_exitBtn = IMAGEMANAGER->addImage("PlayerInfoExitBtn", L"image/ui/PLAYERINFO_EXIT.png", 43, 43);
		IMAGEMANAGER->addImage("PlayerInfoExitBtn2", L"image/ui/PLAYERINFO_EXIT2.png", 43, 43);
		IMAGEMANAGER->addImage("PlayerInfoExitBtn3", L"image/ui/PLAYERINFO_EXIT3.png", 43, 43);

		//ICON (Paladin)
		_playerInfo_paladin = IMAGEMANAGER->addImage("PlayerInfoPaladin", L"image/ui/PLAYERINFO_PALADIN.png", 58, 58);

		//ICON (Ranger)
		_playerInfo_ranger = IMAGEMANAGER->addImage("PlayerInfoRanger", L"image/ui/PLAYERINFO_RANGER.png", 58, 58);
	}

	//=============================
	//         INN NPC UI
	//=============================
	{
		_npc_inn_ui = IMAGEMANAGER->addImage("NpcInnUi1", L"image/ui/NPC1_LEVEL1_UI.png", 970, 528);
	}

	//=============================
	//        SKILL NPC UI
	//=============================
	{
		_npc_skill_ui = IMAGEMANAGER->addImage("NpcSkillUi1", L"image/ui/NPC2_LEVEL1_UI.png", 780, 571);
	}

	//=============================
	//        SKILL NPC UI
	//=============================
	{
		_npc_blackSmith_ui = IMAGEMANAGER->addImage("NpcBlakcSmithUi1", L"image/ui/NPC3_LEVEL1_UI.png", 658, 415);
	}
}
#pragma endregion

#pragma region ADD BUTTON
void Ui::addButton()
{
	//TITLE UI
	_button[TITLE_PROFILES].x = WINSIZEX / 2 - 235;
	_button[TITLE_PROFILES].y = WINSIZEY - 200;
	_button[TITLE_PROFILES].width = 43;
	_button[TITLE_PROFILES].height = 43;

	_button[TITLE_SINGLEPLAY].x = WINSIZEX / 2 - 185;
	_button[TITLE_SINGLEPLAY].y = WINSIZEY - 200;
	_button[TITLE_SINGLEPLAY].width = 154;
	_button[TITLE_SINGLEPLAY].height = 43;
	
	_button[TITLE_SETTING].x = WINSIZEX / 2 - 25;
	_button[TITLE_SETTING].y = WINSIZEY - 200;
	_button[TITLE_SETTING].width = 154;
	_button[TITLE_SETTING].height = 43;

	_button[TITLE_EXIT].x = WINSIZEX / 2 + 135;
	_button[TITLE_EXIT].y = WINSIZEY - 200;
	_button[TITLE_EXIT].width = 154;
	_button[TITLE_EXIT].height = 43;

	_button[TITLE_MAPEDIT].x = WINSIZEX - 50;
	_button[TITLE_MAPEDIT].y = 10;
	_button[TITLE_MAPEDIT].width = 43;
	_button[TITLE_MAPEDIT].height = 43;

	//CHARACTER LIST UI

	_button[CHARACTER_LIST_BOX1].x = 325;
	_button[CHARACTER_LIST_BOX1].y = 260;
	_button[CHARACTER_LIST_BOX1].width = 917;
	_button[CHARACTER_LIST_BOX1].height = 86;

	_button[CHARACTER_LIST_BOX2].x = 325;
	_button[CHARACTER_LIST_BOX2].y = 260 + 86 * 1;
	_button[CHARACTER_LIST_BOX2].width = 917;
	_button[CHARACTER_LIST_BOX2].height = 86;

	_button[CHARACTER_LIST_BOX3].x = 325;
	_button[CHARACTER_LIST_BOX3].y = 260 + 86 * 2;
	_button[CHARACTER_LIST_BOX3].width = 917;
	_button[CHARACTER_LIST_BOX3].height = 86;

	_button[CHARACTER_LIST_BOX4].x = 325;
	_button[CHARACTER_LIST_BOX4].y = 260 + 86 * 3;
	_button[CHARACTER_LIST_BOX4].width = 917;
	_button[CHARACTER_LIST_BOX4].height = 86;

	_button[CHARACTER_LIST_BOX5].x = 325;
	_button[CHARACTER_LIST_BOX5].y = 260 + 86 * 4;
	_button[CHARACTER_LIST_BOX5].width = 917;
	_button[CHARACTER_LIST_BOX5].height = 86;
	
	_button[CHARACTER_LIST_NEW].x = 498;
	_button[CHARACTER_LIST_NEW].y = 647;
	_button[CHARACTER_LIST_NEW].width = 316;
	_button[CHARACTER_LIST_NEW].height = 43;

	_button[CHARACTER_LIST_PLAY].x = 822;
	_button[CHARACTER_LIST_PLAY].y = 647;
	_button[CHARACTER_LIST_PLAY].width = 244;
	_button[CHARACTER_LIST_PLAY].height = 43;

	_button[CHARACTER_LIST_TRESH].x = 1074;
	_button[CHARACTER_LIST_TRESH].y = 647;
	_button[CHARACTER_LIST_TRESH].width = 46;
	_button[CHARACTER_LIST_TRESH].height = 43;

	_button[CHARACTER_LIST_EXIT].x = 1233;
	_button[CHARACTER_LIST_EXIT].y = 210;
	_button[CHARACTER_LIST_EXIT].width = 43;
	_button[CHARACTER_LIST_EXIT].height = 43;

	//CHARACTER CREATE UI

	_button[CHARACTER_CREATE_PALADIN].x = 734;
	_button[CHARACTER_CREATE_PALADIN].y = 384;
	_button[CHARACTER_CREATE_PALADIN].width = 58;
	_button[CHARACTER_CREATE_PALADIN].height = 58;

	_button[CHARACTER_CREATE_RANGER].x = 808;
	_button[CHARACTER_CREATE_RANGER].y = 384;
	_button[CHARACTER_CREATE_RANGER].width = 58;
	_button[CHARACTER_CREATE_RANGER].height = 58;

	_button[CHARACTER_CREATE_PLAY].x = WINSIZEX / 2 - _characterCreate_play->getWidth() / 2;
	_button[CHARACTER_CREATE_PLAY].y = 528;
	_button[CHARACTER_CREATE_PLAY].width = 245;
	_button[CHARACTER_CREATE_PLAY].height = 43;

	_button[CHARACTER_CREATE_EXIT].x = 1088;
	_button[CHARACTER_CREATE_EXIT].y = 328;
	_button[CHARACTER_CREATE_EXIT].width = 43;
	_button[CHARACTER_CREATE_EXIT].height = 43;

	//VOLUME UI

	_button[VOLUME_RESET].x = 595;
	_button[VOLUME_RESET].y = 483;
	_button[VOLUME_RESET].width = 192;
	_button[VOLUME_RESET].height = 36;

	_button[VOLUME_ACCEPT].x = 872;
	_button[VOLUME_ACCEPT].y = 483;
	_button[VOLUME_ACCEPT].width = 192;
	_button[VOLUME_ACCEPT].height = 36;

	_button[VOLUME_EXIT].x = 1154;
	_button[VOLUME_EXIT].y = 380;
	_button[VOLUME_EXIT].width = 36;
	_button[VOLUME_EXIT].height = 36;

	//PAUSE UI
	_button[PAUSE_RESUME].x = WINSIZEX / 2 - _pause_gohomeBtn->getWidth() - _pause_resumeBtn->getWidth() - 15;
	_button[PAUSE_RESUME].y = WINSIZEY - 150;
	_button[PAUSE_RESUME].width = _pause_resumeBtn->getWidth();
	_button[PAUSE_RESUME].height = _pause_resumeBtn->getHeight();

	_button[PAUSE_GOHOME].x = WINSIZEX / 2 - _pause_gohomeBtn->getWidth() - 5;
	_button[PAUSE_GOHOME].y = WINSIZEY - 150;
	_button[PAUSE_GOHOME].width = _pause_gohomeBtn->getWidth();
	_button[PAUSE_GOHOME].height = _pause_gohomeBtn->getHeight();

	_button[PAUSE_SETTING].x = WINSIZEX / 2 + 5;
	_button[PAUSE_SETTING].y = WINSIZEY - 150;
	_button[PAUSE_SETTING].width = _pause_settingBtn->getWidth();
	_button[PAUSE_SETTING].height = _pause_settingBtn->getHeight();

	_button[PAUSE_EXIT].x = WINSIZEX / 2 + _pause_exitBtn->getWidth() + 15;
	_button[PAUSE_EXIT].y = WINSIZEY - 150;
	_button[PAUSE_EXIT].width = _pause_exitBtn->getWidth();
	_button[PAUSE_EXIT].height = _pause_exitBtn->getHeight();

	//INFO UI
	_button[PLAYER_INFO_MAP].x = 0;
	_button[PLAYER_INFO_MAP].y = WINSIZEY / 2 - _playerInfo_window->getHeight() / 2 + 5;
	_button[PLAYER_INFO_MAP].width = 0;
	_button[PLAYER_INFO_MAP].height = _playerInfo_mapBtn->getHeight();

	_button[PLAYER_INFO_CHARACTER].x = 0;
	_button[PLAYER_INFO_CHARACTER].y = WINSIZEY / 2 - _playerInfo_window->getHeight() / 2 + 5;
	_button[PLAYER_INFO_CHARACTER].width = 245;
	_button[PLAYER_INFO_CHARACTER].height = _playerInfo_characterBtn->getHeight();

	_button[PLAYER_INFO_EFFECTS].x = 0;
	_button[PLAYER_INFO_EFFECTS].y = WINSIZEY / 2 - _playerInfo_window->getHeight() / 2 + 5;
	_button[PLAYER_INFO_EFFECTS].width = 245;
	_button[PLAYER_INFO_EFFECTS].height = _playerInfo_characterBtn->getHeight();

	_button[PLAYER_INFO_STATS].x = 0;
	_button[PLAYER_INFO_STATS].y = WINSIZEY / 2 - _playerInfo_window->getHeight() / 2 + 5;
	_button[PLAYER_INFO_STATS].width = 0;
	_button[PLAYER_INFO_STATS].height = _playerInfo_statsBtn->getHeight();

	_button[PLAYER_INFO_EXIT].x = WINSIZEX / 2 + _playerInfo_window->getWidth() / 2 - _playerInfo_exitBtn->getWidth() - 5;
	_button[PLAYER_INFO_EXIT].y = WINSIZEY / 2 - _playerInfo_window->getHeight() / 2 + 5;
	_button[PLAYER_INFO_EXIT].width = _playerInfo_exitBtn->getWidth();
	_button[PLAYER_INFO_EXIT].height = _playerInfo_exitBtn->getHeight();
}
#pragma endregion

#pragma region PLAYER SAVE
void Ui::playerSAVE()
{
	INIDATA->updateData(INIDATA->currentDataNum(), "LEVEL", _pl->get_playerStatus().level);
	INIDATA->updateData(INIDATA->currentDataNum(), "MAX HP", _pl->get_playerStatus().max_hp);
	INIDATA->updateData(INIDATA->currentDataNum(), "HP", _pl->get_playerStatus().hp);
	INIDATA->updateData(INIDATA->currentDataNum(), "MAX MP", _pl->get_playerStatus().max_mp);
	INIDATA->updateData(INIDATA->currentDataNum(), "MP", _pl->get_playerStatus().mp);
	INIDATA->updateData(INIDATA->currentDataNum(), "MAX EXP", _pl->get_playerStatus().max_exp);
	INIDATA->updateData(INIDATA->currentDataNum(), "EXP", _pl->get_playerStatus().exp);
	INIDATA->updateData(INIDATA->currentDataNum(), "X coordinate", _pl->get_playerInfo().x);
	INIDATA->updateData(INIDATA->currentDataNum(), "Y coordinate", _pl->get_playerInfo().y);
	INIDATA->updateData(INIDATA->currentDataNum(), "SKILL POINT", _pl->get_playerStatus().skill_point);
	INIDATA->updateData(INIDATA->currentDataNum(), "HP REGEN", _pl->get_playerStatus().hp_regen);
	INIDATA->updateData(INIDATA->currentDataNum(), "MP REGEN", _pl->get_playerStatus().mp_regen);
	INIDATA->updateData(INIDATA->currentDataNum(), "DAMAGE", _pl->get_playerStatus().damage);
	INIDATA->updateData(INIDATA->currentDataNum(), "ATTACK DAMAGE", _pl->get_playerStatus().attack_dmg);
	INIDATA->updateData(INIDATA->currentDataNum(), "ABILITY POWER", _pl->get_playerStatus().ability_power);
	INIDATA->updateData(INIDATA->currentDataNum(), "ARMOR", _pl->get_playerStatus().armor);
	INIDATA->updateData(INIDATA->currentDataNum(), "MAGIC RESIST", _pl->get_playerStatus().magic_regist);
	INIDATA->updateData(INIDATA->currentDataNum(), "CRITICAL", _pl->get_playerStatus().crit);
	INIDATA->updateData(INIDATA->currentDataNum(), "MOVE SPEED", _pl->get_playerStatus().move_speed);
	INIDATA->updateData(INIDATA->currentDataNum(), "DASH SPEED", _pl->get_playerStatus().dash_speed);
	INIDATA->updateData(INIDATA->currentDataNum(), "EVASION", _pl->get_playerStatus().evasion);
	INIDATA->updateData(INIDATA->currentDataNum(), "RESISTANCE", _pl->get_playerStatus().resistance);
	INIDATA->updateData(INIDATA->currentDataNum(), "LUCK", _pl->get_playerStatus().luck);
	INIDATA->updateData(INIDATA->currentDataNum(), "GOLD", _pl->get_playerResource().gold);
	INIDATA->updateData(INIDATA->currentDataNum(), "ORE", _pl->get_playerResource().ore);
	INIDATA->updateData(INIDATA->currentDataNum(), "POTION MAX", _pl->get_playerResource()._potion.maxHave);
	INIDATA->updateData(INIDATA->currentDataNum(), "POTION", _pl->get_playerResource()._potion.crrentHave);
	INIDATA->updateData(INIDATA->currentDataNum(), "bronzeKey", _pl->get_playerResource().bronze_key);
	INIDATA->updateData(INIDATA->currentDataNum(), "silverKey", _pl->get_playerResource().silver_key);
	INIDATA->updateData(INIDATA->currentDataNum(), "goldKey", _pl->get_playerResource().gold_key);
	INIDATA->updateData(INIDATA->currentDataNum(), "redKey", _pl->get_playerResource().red_key);

	if (_pl->get_playerInfo()._endTime - _pl->get_playerInfo()._startTime > 10)
	{
		float Timecalcul = _pl->playTimeCalcul();
		float saveTime = _pl->get_playerInfo()._playTime;

		saveTime += Timecalcul;

		INIDATA->updateData(INIDATA->currentDataNum(), "PLAY TIME", saveTime);


		_pl->playTimeReset();
	}
}
#pragma endregion

void Ui::volumeInit()
{
	_volume_button_x = 950;
	_volume_button_y = 434;
}