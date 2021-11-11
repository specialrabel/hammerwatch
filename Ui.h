#pragma once
#include "player.h"
#include "Data.h"

#define DF_inventoryXInit	1032
#define DF_inventoryYInit	334
#define DF_inventoryX		39
#define DF_inventoryY		38


class player;

enum ButtonNum
{
	TITLE_PROFILES,
	TITLE_SINGLEPLAY,
	TITLE_SETTING,
	TITLE_EXIT,
	TITLE_MAPEDIT,

	CHARACTER_LIST_BOX1,
	CHARACTER_LIST_BOX2,
	CHARACTER_LIST_BOX3,
	CHARACTER_LIST_BOX4,
	CHARACTER_LIST_BOX5,
	CHARACTER_LIST_NEW,
	CHARACTER_LIST_PLAY,
	CHARACTER_LIST_TRESH,
	CHARACTER_LIST_EXIT,

	CHARACTER_CREATE_PALADIN,
	CHARACTER_CREATE_RANGER,
	CHARACTER_CREATE_PLAY,
	CHARACTER_CREATE_EXIT,

	VOLUME_RESET,
	VOLUME_ACCEPT,
	VOLUME_EXIT,
	VOLUME_BUTTON,

	PLAYER_INFO_MAP,
	PLAYER_INFO_CHARACTER,
	PLAYER_INFO_EFFECTS,
	PLAYER_INFO_STATS,
	PLAYER_INFO_EXIT,

	PAUSE_RESUME,
	PAUSE_GOHOME,
	PAUSE_SETTING,
	PAUSE_EXIT,

	BUTTON_NUM
};

struct BUTTON
{
	D2D1_RECT_F rc;
	float x, y;
	float width, height;
};

class Ui
{
private:

	player* _pl;
	Data* _data;
	Player_Resource _player_resource;
	BUTTON _button[BUTTON_NUM];

	float cam_x;
	float cam_y;
	int _updateTime;

	int _listNum;
	bool _isList[5];

	bool _isPause;		// 일시정지를 눌렀는지.(ESC를 눌렀을 때)
	bool _isInfo;		// 플레이어 정보창을 띄웠는지.(C키를 눌렀을 때)
	bool _isMap;		//
	bool _isCharacter;
	bool _isCharacterInventory;		
	bool _isEffects;
	bool _isStats;
	bool _isCharacterList;
	bool _isCharacterCreate;
	bool _isSetting;
	bool _isPaladin;
	bool _isRanger;
	bool _isInnNpc;
	bool _isSkillNpc;
	bool _isBlackSmithNpc;
	bool _isNpcUi;

	//==============================
	//            TITLE
	//==============================

	//TITLE 이미지
	image* _title_profiles;
	image* _title_play;
	image* _title_option;
	image* _title_exit;
	image* _title_mapEdit;

	//==============================
	//		  CHARACTER LIST
	//==============================

	//UI 이미지
	image* _characterListUi;
	image* _characterListBox[5];

	//UI 버튼 이미지
	image* _characterList_new;
	image* _characterList_play;
	image* _characterList_tresh;
	image* _characterList_exit;

	//CLASS 이미지
	image* _characterList_paladin_picture;
	image* _characterList_paladin_icon;
	image* _characterList_ranger_picture;
	image* _characterList_ranger_icon;


	//==============================
	//		 CHARACTER CREATE
	//==============================

	//UI 이미지
	image* _characterCreateUi;

	//UI 버튼 이미지
	image* _characterCreate_paladin;
	image* _characterCreate_paladin_skill[7];
	image* _characterCreate_ranger;
	image* _characterCreate_ranger_skill[7];
	image* _characterCreate_play;
	image* _characterCreate_exit;

	//==============================
	//	     VOLUME SETTING
	//==============================

	//UI 이미지
	image* _volumeUi;
	
	image* _volume_button;
	float _volume_button_x, _volume_button_y;

	//UI 버튼 이미지
	image* _volume_reset;
	image* _volume_accept;
	image* _volume_exit;

	//==============================
	//           PLAYING
	//==============================

	//UI 이미지
	image* _leftBar;
	image* _rightBar;
	image* _upBar;

	//UI 아이콘 이미지
	image* _potion;
	image* _potion_half;

	//팔라딘
	image* _paladin;
	image* _paladin_skill1;
	image* _paladin_skill1_cooltime;
	image* _paladin_skill2;
	image* _paladin_skill2_cooltime;

	//레인저
	image* _ranger;
	image* _ranger_skill1;
	image* _ranger_skill1_cooltime;
	image* _ranger_skill2;
	image* _ranger_skill2_cooltime;

	//쿨타임 끝나갈 때
	image* _playing_cooltime_end;

	//큰 게이지 바
	image* _playing_hpBar;
	image* _playing_mpBar;
	//작은 게이지 바
	image* _playing_hpBar2;
	image* _playing_mpBar2;
	//경험치 게이지 바
	image* _playing_expBar;
	//포션 게이지 바
	image* _playing_potion_gauge1;


	//==============================
	//            PAUSE
	//==============================

	//BLACK BOX
	image* _blackBox;

	//LOGO
	image* _logo;

	//UI 버튼 이미지
	image* _pause_resumeBtn;
	image* _pause_gohomeBtn;
	image* _pause_settingBtn;
	image* _pause_exitBtn;


	//==============================
	//         PLAYER INFO
	//==============================

	//CHARACTER
	image* _playerInfo_window;
	image* _playerInfo_ui;

	//팔라딘
	image* _playerInfo_paladin;

	//레인저
	image* _playerInfo_ranger;

	//UI 버튼 이미지
	image* _playerInfo_mapBtn;
	image* _playerInfo_characterBtn;
	image* _playerInfo_effectsBtn;
	image* _playerInfo_statsBtn;
	image* _playerInfo_exitBtn;


	//==============================
	//           INN NPC
	//==============================

	//UI
	image* _npc_inn_ui;

	//==============================
	//          SKILL NPC
	//==============================

	//UI
	image* _npc_skill_ui;


	//==============================
	//        BLACKSMITH NPC
	//==============================

	//UI
	image* _npc_blackSmith_ui;


public:
	Ui();
	~Ui();

	HRESULT init();
	void release();
	void update();
	void render();

	void titleUiUpdate();
	void titleUiRender();
	void characterListUiUpdate();
	void characterListUiRender();
	void characterCreateUiUpdate();
	void characterCreateUiRender();
	void volumeUiUpdate();
	void volumeUiRender();
	void playingUiUpdate();
	void playingUiRender();
	void pauseUiUpdate();
	void pauseUiRender();
	void playerInfoUiUpdate();
	void playerInfoUiRender();
	void innUiUpdate();
	void innUiRender();
	void skillUiUpdate();
	void skillUiRender();
	void blackSmithUiUpdate();
	void blackSmithUiRender();

	void addImage();
	void addButton();

	void setPlayerMemoryAdressLink(player* player) { _pl = player; }
	bool getPause() { return _isPause; }							// 플레이어에서 받을 정보
	bool getIsCharacterCreate() { return _isCharacterCreate; }		// 캐릭터 생성			*(title SCENE에서 사용)
	bool getIsInfo() { return _isInfo; }							// 플레이어 정보창 UI		*(플레이어 UPDATE막는 용도)
	bool getIsPause() { return _isPause; }							// 일시정지 화면 UI		*(플레이어 UPDATE막는 용도)
	bool getIsInnUI() { return _isInnNpc; }							// NPC UI (마을 강화)	*(충돌처리 용도)
	bool getIsSkillUI() { return _isSkillNpc; }						// NPC UI (스킬 강화)	*(충돌처리 용도)
	bool getIsBlackSmithUi() { return _isBlackSmithNpc; }			// NPC UI (대장간)		*(충돌처리 용도)

	void playerSAVE();	//플레이어정보 세이브

	//외부 클래스에서 Ui 설정
	bool getNpcUi() { if (_isBlackSmithNpc || _isInnNpc || _isSkillNpc) return false; return true; }
	void setIsBlackSmithUi(bool b = false) { _isBlackSmithNpc = b; }
	void setIsInnUi(bool b = false) { _isInnNpc = b; }

	void volumeInit();
};