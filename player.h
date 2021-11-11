#pragma once
#include "gameNode.h"
#include "animation.h"
#include "effect.h"
#include "bullets.h"
#include "mapTool.h"


// �÷��̾� ����
enum class Player_Class
{
	Paladin,
	Ranger,

	END
};

// �÷��̾� ����
enum class Player_State
{
	IDLE,
	RUN,
	ATTACK,
	SKILL,
	SKILL2,
	DEAD,

	NUM
};

// �÷��̾� ����
enum class Player_Direction
{
	LEFT,
	TOP,
	RIGHT,
	BOTTOM,

	LEFT_TOP,
	RIGHT_TOP,
	LEFT_BOTTOM,
	RIGHT_BOTTOM,

	DIRECTION_NUM
};

// �÷��̾� ��ġ ����
struct Player_Info
{
	D2D1_RECT_F rc;
	image* img;

	float x, y;
	float width, height;
	float start_xPos, start_yPos;
	float angle;
	Player_Direction direction;
	Player_Direction moving_direction;
	Player_State state;

	float _playTime;
	float _startTime, _endTime;
};

// �÷��̾� �ɷ�ġ ����
struct Player_Status
{
	Player_Class player_class;
	int level;
	float skill_point;
	float skill_cd;
	float max_exp, exp;

	float hp, mp;
	float max_hp, max_mp;
	float hp_regen, mp_regen;

	float damage;
	float attack_dmg;
	float ability_power;
	
	float armor;
	float magic_regist;

	float crit;
	float speed;
	float evasion;
	float resistance;
	float luck;

	float move_speed;
	float dash_speed;
};

// �÷��̾� �ڿ� -> �������� ���̴� ����
struct Player_Resource
{
	vector<itemData> inventory;
	potion _potion;
	int gold;
	int ore;
	int bronze_key;
	int silver_key;
	int gold_key;
	int red_key;
	int potion;
};

// �÷��̾� �ڿ� -> �������� ���̴� ����
struct Dungeon_Resource
{
	int gold;
	int ore;
	
	int damage_taken;
	int distance;
	float playtime;
};

class player
{

private:
	Player_Info _player;
	Player_Status _status;
	Player_Resource _player_resource;
	Dungeon_Resource _dungeon_resource;

	mapTool* _mt;

	Player_bullet* _arrow;
	hitBox* _hitbox;
	animation* player_action;
	effect* smash_effect;
	D2D1_MATRIX_3X2_F scale_mat;
	D2D1_MATRIX_3X2_F rotation_mat;

	int interval[(int)Player_State::NUM];
	bool current_direction[(int)Player_Direction::DIRECTION_NUM];
	float effect_interval = 0;
	float count;

	bool action_done;
	bool effect_done;
	bool is_hit;
	bool end;

public:

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	// �÷��̾� ��ǥ, ��Ʈ, ����, ����(IDLE, ATTACK) ���� ��ȯ
	inline Player_Info get_playerInfo() { return _player; }

	// �÷��̾� ����(����, HP, ���ݷ�, ���ǵ� ....) ���� ��ȯ
	inline Player_Status get_playerStatus() { return _status; }

	// �÷��̾� ������, ���� ���� ��ȯ
	inline Player_Resource get_playerResource() { return _player_resource; }

	// �÷��̾ �������� ȹ���� ���, ���� ���� ��ȯ
	inline Dungeon_Resource get_DungeonResource() { return _dungeon_resource; }

	inline Player_bullet* get_arrow() { return _arrow; }
	inline hitBox* get_hitBox() { return _hitbox; }
	inline float get_currentCD() { return effect_interval; }

	inline void set_x(float _x) { _player.x = _x; }
	inline void set_y(float _y) { _player.y = _y; }

	inline void set_hp(float hp) { _status.hp += hp; }
	inline void set_exp(float exp) { _status.exp += exp; }
	inline void set_skillPoint(float sp) { _status.skill_point += sp; }
	inline void set_dashSpeed(float spd) { _status.dash_speed += spd; }

	inline void set_hit(bool hit) { is_hit = hit; }
	inline void set_rect()
	{
		_player.rc = D2DMANAGER->RectMakeCenter(_player.x, _player.y, _player.width, _player.height);
	}
	inline void put_rect(D2D1_RECT_F temp) { _player.rc = temp; }

	// �������� �ٸ� �ִϸ��̼� ���
	void animation_init_paladin();
	void animation_init_ranger();
	void animation_setting();
	
	// �������� �ٸ� �ʱ� ���Ȱ� �ο� 
	void status_init_paladin();
	void status_init_ranger();

	// �������� �ٸ� ���� �ൿ
	void attack_paladin();
	void attack_ranger();

	// �������� ���� ��ų �̹��� ��ȯ
	void skillAnimation_paladin();
	void skillAnimation_ranger();

	//�������� ���� ��ų �ൿ ����
	void skillAction_paladin();
	void skillAction_ranger();

	// ĳ���Ͱ� �ٶ󺸴� ������ ���콺 ������ ������Ʈ ���ִ� �Լ�
	void update_direction();
	
	// ������ ���������� ĳ���͸� ��ٸ��� ����� �Լ�
	void wait_process();

	// �� ���¸��� �ٸ� �ൿ�� �ϱ����� �Լ��� ����
	void key_setting_idle();
	void key_setting_run();
	void key_setting_attack();
	void key_setting_skill();

	void setMapToolMemoryAddressLink(mapTool* mt) { _mt = mt; }

	//������ ȹ��
	void set_item(itemData item);
	bool check_and_aoto_pickup_item(itemData item);
	//���尣 ��ȭ
	void set_upgrade_attack(float data) { _status.attack_dmg += data; }
	void set_upgrade_armor(float data) { _status.armor += data; }
	void set_upgrade_crit(float data) { _status.crit += data; }
	void set_upgrade_speed(float data) { _status.move_speed += data; }
	//���Ž�
	void set_gold(int gold) { _player_resource.gold += gold; }
	void set_ore(int ore) { _player_resource.ore = ore; }

	//�÷��̾� ������
	void playerInitData();
	//�ʱ� ���� ����
	void playerStatInit();
	//�� �̵��� �ʸ��� �������� ��ǥ
	void playerCoordinates(int x, int y);
	//�÷��̾� ������
	void playerUsePotion();
	//�÷���Ÿ��
	float playTimeCalcul();
	void playTimeReset();
};

