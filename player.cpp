#include "stdafx.h"
#include "player.h"

HRESULT player::init()
{
	IMAGEMANAGER->addFrameImage("paladin", L"image/Paladin3.png", 720, 360, 10, 5);
	IMAGEMANAGER->addFrameImage("ranger", L"image/Ranger2.png", 720, 504, 10, 7);
	IMAGEMANAGER->addFrameImage("smash_effect", L"effect/smash_effect2.png", 294, 50, 7, 1);
	IMAGEMANAGER->addFrameImage("dash_effect", L"effect/dash_effect2.png", 80, 18, 4, 1);
	IMAGEMANAGER->addFrameImage("arrow_effect", L"effect/arrow_hit.png", 256, 32, 8, 1);

	EFFECTMANAGER->addEffect("smash", "smash_effect", 294, 50, 42, 50, 1, 0.7, 1);
	EFFECTMANAGER->addEffect("dash", "dash_effect", 80, 18, 20, 18, 1, 0.2, 10);
	EFFECTMANAGER->addEffect("arrow", "arrow_effect", 256, 32, 32, 32, 1, 1, 30);

	smash_effect = new effect;
	_arrow = new Player_bullet;
	_hitbox = new hitBox;

	playerInitData();

	for (int i = 0; i < (int)Player_State::NUM; i++)
	{
		interval[i] = 0;
	}

	_player.state = Player_State::IDLE;
	_player.direction = Player_Direction::RIGHT;
	_player.moving_direction = Player_Direction::RIGHT;

	player_action = KEYANIMANAGER->findAnimation("right_idle");
	player_action->start();

	action_done = true;
	effect_done = true;
	is_hit = false;
	end = false;

	effect_interval = 0;
	count = 0;
	return S_OK;
}

void player::release()
{
	delete player_action;
	delete smash_effect;
}

void player::update()
{
	_player._endTime = TIMEMANAGER->getWorldTime();

	if (!end)
	{
		Player_Direction temp = _player.direction;

		wait_process();
		playerUsePotion();

		// 상태 패턴처럼 각 상태에는 다른 행동만 할수있도록 함수로 나눠서 업데이트에서 실행함.
		switch (_player.state)
		{
		case Player_State::IDLE:
			key_setting_idle();
			break;

		case Player_State::RUN:
			key_setting_run();
			break;

		case Player_State::ATTACK:
			key_setting_attack();
			break;

		case Player_State::SKILL:
			key_setting_skill();
			break;
		}

		// 행동이 끝나기 전에는 플레이어의 방향을 못바꾸도록 함
		if (action_done)
			update_direction();

		// 행동이 끝났다면, 마우스가 있는 방향을 쳐다보도록 애니매이션 업데이트
		if (_player.direction != temp)
		{
			animation_setting();
		}
	}

	if (_status.hp <= 0 && !end)
	{
		_player.state == Player_State::DEAD;
		player_action = KEYANIMANAGER->findAnimation("dead");
		player_action->start();

		end = true;
	}
	if (end)
	{

	}

	// 이펙트 업데이트
	smash_effect->update();
	_arrow->update();
	_hitbox->update();
	KEYANIMANAGER->update();
	EFFECTMANAGER->update();
}

void player::render()
{
	//_player.img->Frame_scale_start(_player.rc.left, _player.rc.top, 1.0f, 1.0f);
	_player.img->aniRender(_player.rc.left - 20, _player.rc.top - 20, player_action);
	//_player.img->scale_end();
	D2DMANAGER->Rectangle(_player.rc);

	D2DMANAGER->pRenderTarget->SetTransform(rotation_mat);
	smash_effect->render();
	D2DMANAGER->pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

	_arrow->render();
	_hitbox->render();

	EFFECTMANAGER->render();
	WCHAR str[128];
	swprintf_s(str, L"Direction is : %.1f,  %.1f", _player.x, _status.hp);
	D2DMANAGER->DrawTextD2D(D2DMANAGER->defaultBrush, L"메이플스토리", 17.0f, str, _player.rc.left - 40 - CAMERAMANAGER->get_camera_x(), _player.rc.top - 40 - CAMERAMANAGER->get_camera_y(), _player.rc.left + 100, _player.rc.top + 100);
}


// 마우스 위치에 따라 플레이어가 바라보는 방향을 바꾸는 함수
void player::update_direction()
{
	_player.angle = getAngle(_player.x, _player.y, _ptMouse.x, _ptMouse.y);

	if (_player.angle >= PI2) _player.angle -= PI2;
	if (_player.angle <= 0) _player.angle += PI2;

	if (_player.angle > 0 && _player.angle <= PI8)
	{
		_player.direction = Player_Direction::RIGHT;
	}
	else if (_player.angle > PI8 && _player.angle <= 3* PI8)
	{
		_player.direction = Player_Direction::RIGHT_TOP;
	}
	else if (_player.angle > 3* PI8 && _player.angle <= 5* PI8)
	{
		_player.direction = Player_Direction::TOP;
	}
	else if (_player.angle > 5 * PI8 && _player.angle <= 7 * PI8)
	{
		_player.direction = Player_Direction::LEFT_TOP;
	}
	else if (_player.angle > 7 * PI8 && _player.angle <= 9 * PI8)
	{
		_player.direction = Player_Direction::LEFT;
	}
	else if (_player.angle > 9 * PI8 && _player.angle <= 11 * PI8)
	{
		_player.direction = Player_Direction::LEFT_BOTTOM;
	}
	else if (_player.angle > 11 * PI8 && _player.angle <= 13 * PI8)
	{
		_player.direction = Player_Direction::BOTTOM;
	}
	else if (_player.angle > 13 * PI8 && _player.angle <= 15 * PI8)
	{
		_player.direction = Player_Direction::RIGHT_BOTTOM;
	}
	else
	{
		_player.direction = Player_Direction::RIGHT;
	}
}

// 플레이어의 행동이 끝나는지 안끝나는지 불값을 받는 함수
void player::wait_process()
{
	if (_player.state == Player_State::ATTACK)
	{
		count += TIMEMANAGER->getElapsedTime();
	}

	if (count > 0.2f)
	{
		action_done = true;
		count = 0;
	}
}

// 플레이어 상태에 따라 이미지를 바꿔주는 함수
void player::animation_setting()
{
	switch (_player.direction)
	{
	case Player_Direction::LEFT:
		if (_player.state == Player_State::IDLE)
		{
			player_action = KEYANIMANAGER->findAnimation("left_idle");
			player_action->start();
		}
		if (_player.state == Player_State::RUN)
		{
			player_action = KEYANIMANAGER->findAnimation("left_run");
			player_action->start();
		}
		if (_player.state == Player_State::ATTACK)
		{
			player_action = KEYANIMANAGER->findAnimation("left_attack");
			player_action->start();

			switch (_status.player_class)
			{
			case Player_Class::Paladin:
				attack_paladin();
				break;

			case Player_Class::Ranger:
				attack_ranger();
				break;
			}
		}
		if (_player.state == Player_State::SKILL)
		{
			switch (_status.player_class)
			{
			case Player_Class::Paladin:
				skillAnimation_paladin();
				break;

			case Player_Class::Ranger:
				skillAnimation_ranger();
				break;
			}
		}
		break;
	case Player_Direction::TOP:
		if (_player.state == Player_State::IDLE)
		{
			player_action = KEYANIMANAGER->findAnimation("top_idle");
			player_action->start();
		}
		if (_player.state == Player_State::RUN)
		{
			player_action = KEYANIMANAGER->findAnimation("top_run");
			player_action->start();
		}
		if (_player.state == Player_State::ATTACK)
		{
			player_action = KEYANIMANAGER->findAnimation("top_attack");
			player_action->start();

			switch (_status.player_class)
			{
			case Player_Class::Paladin:
				attack_paladin();
				break;

			case Player_Class::Ranger:
				attack_ranger();
				break;
			}
		}
		if (_player.state == Player_State::SKILL)
		{
			switch (_status.player_class)
			{
			case Player_Class::Paladin:
				skillAnimation_paladin();
				break;

			case Player_Class::Ranger:
				skillAnimation_ranger();
				break;
			}
		}
		break;

	case Player_Direction::RIGHT:
		if (_player.state == Player_State::IDLE)
		{
			player_action = KEYANIMANAGER->findAnimation("right_idle");
			player_action->start();
		}
		if (_player.state == Player_State::RUN)
		{
			player_action = KEYANIMANAGER->findAnimation("right_run");
			player_action->start();
		}
		if (_player.state == Player_State::ATTACK)
		{
			player_action = KEYANIMANAGER->findAnimation("right_attack");
			player_action->start();

			switch (_status.player_class)
			{
			case Player_Class::Paladin:
				attack_paladin();
				break;

			case Player_Class::Ranger:
				attack_ranger();
				break;
			}
		}
		if (_player.state == Player_State::SKILL)
		{
			switch (_status.player_class)
			{
			case Player_Class::Paladin:
				skillAnimation_paladin();
				break;

			case Player_Class::Ranger:
				skillAnimation_ranger();
				break;
			}
		}
		break;

	case Player_Direction::BOTTOM:
		if (_player.state == Player_State::IDLE)
		{
			player_action = KEYANIMANAGER->findAnimation("bottom_idle");
			player_action->start();
		}
		if (_player.state == Player_State::RUN)
		{
			player_action = KEYANIMANAGER->findAnimation("bottom_run");
			player_action->start();
		}
		if (_player.state == Player_State::ATTACK)
		{
			player_action = KEYANIMANAGER->findAnimation("bottom_attack");
			player_action->start();

			switch (_status.player_class)
			{
			case Player_Class::Paladin:
				attack_paladin();
				break;

			case Player_Class::Ranger:
				attack_ranger();
				break;
			}
		}
		if (_player.state == Player_State::SKILL)
		{
			switch (_status.player_class)
			{
			case Player_Class::Paladin:
				skillAnimation_paladin();
				break;

			case Player_Class::Ranger:
				skillAnimation_ranger();
				break;
			}
		}
		break;

	case Player_Direction::LEFT_TOP:
		if (_player.state == Player_State::IDLE)
		{
			player_action = KEYANIMANAGER->findAnimation("left_top_idle");
			player_action->start();
		}
		if (_player.state == Player_State::RUN)
		{
			player_action = KEYANIMANAGER->findAnimation("left_top_run");
			player_action->start();
		}
		if (_player.state == Player_State::ATTACK)
		{
			player_action = KEYANIMANAGER->findAnimation("left_top_attack");
			player_action->start();

			switch (_status.player_class)
			{
			case Player_Class::Paladin:
				attack_paladin();
				break;

			case Player_Class::Ranger:
				attack_ranger();
				break;
			}
		}
		if (_player.state == Player_State::SKILL)
		{
			switch (_status.player_class)
			{
			case Player_Class::Paladin:
				skillAnimation_paladin();
				break;

			case Player_Class::Ranger:
				skillAnimation_ranger();
				break;
			}
		}
		break;
	case Player_Direction::RIGHT_TOP:
		if (_player.state == Player_State::IDLE)
		{
			player_action = KEYANIMANAGER->findAnimation("right_top_idle");
			player_action->start();
		}
		if (_player.state == Player_State::RUN)
		{
			player_action = KEYANIMANAGER->findAnimation("right_top_run");
			player_action->start();
		}
		if (_player.state == Player_State::ATTACK)
		{
			player_action = KEYANIMANAGER->findAnimation("right_top_attack");
			player_action->start();

			switch (_status.player_class)
			{
			case Player_Class::Paladin:
				attack_paladin();
				break;

			case Player_Class::Ranger:
				attack_ranger();
				break;
			}
		}
		if (_player.state == Player_State::SKILL)
		{
			switch (_status.player_class)
			{
			case Player_Class::Paladin:
				skillAnimation_paladin();
				break;

			case Player_Class::Ranger:
				skillAnimation_ranger();
				break;
			}
		}
		break;

	case Player_Direction::LEFT_BOTTOM:
		if (_player.state == Player_State::IDLE)
		{
			player_action = KEYANIMANAGER->findAnimation("left_bottom_idle");
			player_action->start();
		}
		if (_player.state == Player_State::RUN)
		{
			player_action = KEYANIMANAGER->findAnimation("left_bottom_run");
			player_action->start();
		}
		if (_player.state == Player_State::ATTACK)
		{
			player_action = KEYANIMANAGER->findAnimation("left_bottom_attack");
			player_action->start();

			switch (_status.player_class)
			{
			case Player_Class::Paladin:
				attack_paladin();
				break;

			case Player_Class::Ranger:
				attack_ranger();
				break;
			}
		}
		if (_player.state == Player_State::SKILL)
		{
			switch (_status.player_class)
			{
			case Player_Class::Paladin:
				skillAnimation_paladin();
				break;

			case Player_Class::Ranger:
				skillAnimation_ranger();
				break;
			}
		}
		break;
	case Player_Direction::RIGHT_BOTTOM:
		if (_player.state == Player_State::IDLE)
		{
			player_action = KEYANIMANAGER->findAnimation("right_bottom_idle");
			player_action->start();
		}
		if (_player.state == Player_State::RUN)
		{
			player_action = KEYANIMANAGER->findAnimation("right_bottom_run");
			player_action->start();
		}
		if (_player.state == Player_State::ATTACK)
		{
			player_action = KEYANIMANAGER->findAnimation("right_bottom_attack");
			player_action->start();

			switch (_status.player_class)
			{
			case Player_Class::Paladin:
				attack_paladin();
				break;

			case Player_Class::Ranger:
				attack_ranger();
				break;
			}
		}
		if (_player.state == Player_State::SKILL)
		{
			switch (_status.player_class)
			{
			case Player_Class::Paladin:
				skillAnimation_paladin();
				break;

			case Player_Class::Ranger:
				skillAnimation_ranger();
				break;
			}
		}
		break;
	}
}

void player::set_item(itemData item)
{

	_player_resource.inventory.push_back(item);

	_status.max_hp += item.max_hp;
	_status.hp += item.max_hp;
	_status.max_mp += item.max_mp;
	_status.mp += item.max_mp;
	_status.hp_regen += item.hp_regen;
	_status.attack_dmg += item.attack_dmg;
	_status.armor += item.armor;
	_status.magic_regist += item.magic_regist;

	ITEMMANAGER->deletAllItemInventory();

}

bool player::check_and_aoto_pickup_item(itemData item)
{
	switch (item.kind)
	{
	case HP:
		//현재 체력이 최대면 먹지 않음
		if (_status.hp >= _status.max_hp)
			return false;
		//현재 체력을 회복하고 최대체력을 넘지 않게 함
		_status.hp += item.value;
		if (_status.hp > _status.max_hp) _status.hp = _status.max_hp;
		return true;

		break;
	case MP:
		//현재 마력이 최대면 먹지 않음
		if (_status.mp >= _status.max_mp)
			return false;
		//현재 마력을 회복하고 최대마력을 넘지 않게 함
		_status.mp += item.value;
		if (_status.mp > _status.max_mp) _status.mp = _status.max_mp;
		return true;

		break;
	case GOLD:
		//던전 골드 증가
		_dungeon_resource.gold += item.value;
		return true;

		break;
	case ORE:
		//던전 광석 증가
		_dungeon_resource.ore += item.value;
		return true;

		break;
	case KEY:
		//키 자원 증가
		if (item.value == 1) _player_resource.bronze_key += 1;
		if (item.value == 2) _player_resource.silver_key += 1;
		if (item.value == 3) _player_resource.gold_key += 1;
		if (item.value == 4) _player_resource.red_key += 1;
		return true;

		break;
	case POSION:
		if (_player_resource._potion.crrentHave == _player_resource._potion.maxHave) return false;
		//포션 최대치 회복
		_player_resource._potion.crrentHave = _player_resource._potion.maxHave ;
		//포션회복량 만큼 체력 마나 회복
		_status.hp += _player_resource._potion.recovreyValueHP;
		if (_status.hp > _status.max_hp) _status.hp = _status.max_hp;
		_status.mp += _player_resource._potion.recovreyValueMP;
		if (_status.mp > _status.max_mp) _status.mp = _status.max_mp;
		return true;
		break;
	}

	return false;
}

void player::playerInitData()
{
	// 직업에 따라서 다른 초기화를 합니다
	switch ((Player_Class)(int)INIDATA->readData(INIDATA->currentDataNum(), "CLASS"))
	{
	case Player_Class::Paladin:
		_player.img = IMAGEMANAGER->findImage("paladin");
		_status.player_class = Player_Class::Paladin;
		animation_init_paladin();

		smash_effect->init(IMAGEMANAGER->findImage("smash_effect"), 42, 50, 1, 0.7);
		break;

	case Player_Class::Ranger:
		_player.img = IMAGEMANAGER->findImage("ranger");
		_status.player_class = Player_Class::Ranger;
		animation_init_ranger();

		_arrow->init(400);
		break;
	}

	playerStatInit();

	// 플레이어 위치, 렉트, 상태 등등 정의
	_player.x = INIDATA->readData(INIDATA->currentDataNum(), "X coordinate");
	_player.y = INIDATA->readData(INIDATA->currentDataNum(), "Y coordinate");
	_player.width = 32;
	_player.height = 32;
	_player.rc = D2DMANAGER->RectMakeCenter(_player.x, _player.y, _player.width, _player.height);
}

void player::playerStatInit()
{
	_status.level = INIDATA->readData(INIDATA->currentDataNum(), "LEVEL");
	_status.hp = INIDATA->readData(INIDATA->currentDataNum(), "HP");
	_status.mp = INIDATA->readData(INIDATA->currentDataNum(), "MP");
	_status.max_hp = INIDATA->readData(INIDATA->currentDataNum(), "MAX HP");
	_status.max_mp = INIDATA->readData(INIDATA->currentDataNum(), "MAX MP");
	_status.hp_regen = INIDATA->readData(INIDATA->currentDataNum(), "HP REGEN");
	_status.mp_regen = INIDATA->readData(INIDATA->currentDataNum(), "MP REGEN");
	_status.move_speed = INIDATA->readData(INIDATA->currentDataNum(), "MOVE SPEED");
	_status.max_exp = INIDATA->readData(INIDATA->currentDataNum(), "MAX EXP");
	_status.exp = INIDATA->readData(INIDATA->currentDataNum(), "EXP");
	_player_resource.ore = INIDATA->readData(INIDATA->currentDataNum(), "ORE");
	_player_resource.gold = INIDATA->readData(INIDATA->currentDataNum(), "GOLD");
	_player_resource.bronze_key = INIDATA->readData(INIDATA->currentDataNum(), "bronzeKey");
	_player_resource.silver_key = INIDATA->readData(INIDATA->currentDataNum(), "silverKey");
	_player_resource.gold_key = INIDATA->readData(INIDATA->currentDataNum(), "goldKey");
	_player_resource.red_key = INIDATA->readData(INIDATA->currentDataNum(), "redKey");
	_player_resource._potion.maxHave = INIDATA->readData(INIDATA->currentDataNum(), "POTION MAX");
	_player_resource._potion.crrentHave = INIDATA->readData(INIDATA->currentDataNum(), "POTION");

	_status.damage = INIDATA->readData(INIDATA->currentDataNum(), "DAMAGE");
	_status.attack_dmg = INIDATA->readData(INIDATA->currentDataNum(), "ATTACK DAMAGE");
	_status.ability_power = INIDATA->readData(INIDATA->currentDataNum(), "ABILITY POWER");
	_status.magic_regist = INIDATA->readData(INIDATA->currentDataNum(), "MAGIC RESIST");
	_status.crit = INIDATA->readData(INIDATA->currentDataNum(), "CRITICAL");
	_status.evasion = INIDATA->readData(INIDATA->currentDataNum(), "EVASION");
	_status.armor = INIDATA->readData(INIDATA->currentDataNum(), "ARMOR");
	_status.resistance = INIDATA->readData(INIDATA->currentDataNum(), "RESISTANCE");
	_status.luck = INIDATA->readData(INIDATA->currentDataNum(), "LUCK");

	_status.dash_speed = INIDATA->readData(INIDATA->currentDataNum(), "DASH SPEED");
	_status.skill_point = INIDATA->readData(INIDATA->currentDataNum(), "SKILL POINT");
	_status.skill_cd = 0.8f;

	_player._playTime = INIDATA->readData(INIDATA->currentDataNum(), "PLAY TIME");

	_player._startTime = _player._endTime = TIMEMANAGER->getWorldTime();
}

void player::playerCoordinates(int x, int y)
{
	_player.x = x;
	_player.y = y;
}

void player::playerUsePotion()
{
	if (KEYMANAGER->isOnceKeyDown('R'))
	{
		if(_status.max_hp != _status.hp || _status.max_mp != _status.mp)
		_player_resource._potion.crrentHave -= 1;
	}
}

float player::playTimeCalcul()
{
	float playTime;

	playTime = _player._endTime - _player._startTime;

	return playTime;
}

void player::playTimeReset()
{
	_player._startTime = _player._endTime = TIMEMANAGER->getWorldTime();

	_player._playTime = INIDATA->readData(INIDATA->currentDataNum(), "PLAY TIME");
}
