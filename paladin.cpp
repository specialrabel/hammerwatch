#include "stdafx.h"
#include "player.h"

void player::animation_init_paladin()
{
	int left_idle[] = { 4 };
	KEYANIMANAGER->addArrayFrameAnimation("left_idle", "paladin", left_idle, 1, 4.0, true);
	int left_run[] = { 4, 24 };
	KEYANIMANAGER->addArrayFrameAnimation("left_run", "paladin", left_run, 2, 4.0, true);
	int left_attack[] = { 24, 34, 44 };
	KEYANIMANAGER->addArrayFrameAnimation("left_attack", "paladin", left_attack, 3, 10.0, false);

	int left_top_idle[] = { 3 };
	KEYANIMANAGER->addArrayFrameAnimation("left_top_idle", "paladin", left_top_idle, 1, 4.0, true);
	int left_top_run[] = { 3, 13 };
	KEYANIMANAGER->addArrayFrameAnimation("left_top_run", "paladin", left_top_run, 2, 4.0, true);
	int left_top_attack[] = { 23, 33, 43 };
	KEYANIMANAGER->addArrayFrameAnimation("left_top_attack", "paladin", left_top_attack, 3, 10.0, false);

	int top_idle[] = { 2 };
	KEYANIMANAGER->addArrayFrameAnimation("top_idle", "paladin", top_idle, 1, 4.0, true);
	int top_run[] = { 2, 12 };
	KEYANIMANAGER->addArrayFrameAnimation("top_run", "paladin", top_run, 2, 4.0, true);
	int top_attack[] = { 22, 32, 42 };
	KEYANIMANAGER->addArrayFrameAnimation("top_attack", "paladin", top_attack, 3, 10.0, false);

	int right_top_idle[] = { 1 };
	KEYANIMANAGER->addArrayFrameAnimation("right_top_idle", "paladin", right_top_idle, 1, 4.0, true);
	int right_top_run[] = { 1, 11 };
	KEYANIMANAGER->addArrayFrameAnimation("right_top_run", "paladin", right_top_run, 2, 4.0, true);
	int right_top_attack[] = { 21, 31, 41 };
	KEYANIMANAGER->addArrayFrameAnimation("right_top_attack", "paladin", right_top_attack, 3, 10.0, false);

	int right_idle[] = { 0 };
	KEYANIMANAGER->addArrayFrameAnimation("right_idle", "paladin", right_idle, 1, 4.0, true);
	int right_run[] = { 10, 20 };
	KEYANIMANAGER->addArrayFrameAnimation("right_run", "paladin", right_run, 2, 4.0, true);
	int right_attack[] = { 20, 30, 40 };
	KEYANIMANAGER->addArrayFrameAnimation("right_attack", "paladin", right_attack, 3, 10.0, false);

	int left_bottom_idle[] = { 5 };
	KEYANIMANAGER->addArrayFrameAnimation("left_bottom_idle", "paladin", left_bottom_idle, 1, 4.0, true);
	int left_bottom_run[] = { 5, 15 };
	KEYANIMANAGER->addArrayFrameAnimation("left_bottom_run", "paladin", left_bottom_run, 2, 4.0, true);
	int left_bottom_attack[] = { 25, 35, 45 };
	KEYANIMANAGER->addArrayFrameAnimation("left_bottom_attack", "paladin", left_bottom_attack, 3, 10.0, false);

	int bottom_idle[] = { 6 };
	KEYANIMANAGER->addArrayFrameAnimation("bottom_idle", "paladin", bottom_idle, 1, 4.0, true);
	int bottom_run[] = { 6, 16 };
	KEYANIMANAGER->addArrayFrameAnimation("bottom_run", "paladin", bottom_run, 2, 4.0, true);
	int bottom_attack[] = { 26, 36, 46 };
	KEYANIMANAGER->addArrayFrameAnimation("bottom_attack", "paladin", bottom_attack, 3, 10.0, false);

	int right_bottom_idle[] = { 7 };
	KEYANIMANAGER->addArrayFrameAnimation("right_bottom_idle", "paladin", right_bottom_idle, 1, 4.0, true);
	int right_bottom_run[] = { 7, 17 };
	KEYANIMANAGER->addArrayFrameAnimation("right_bottom_run", "paladin", right_bottom_run, 2, 4.0, true);
	int right_bottom_attack[] = { 27, 37, 47 };
	KEYANIMANAGER->addArrayFrameAnimation("right_bottom_attack", "paladin", right_bottom_attack, 3, 10.0, false);

	int dead[] = { 8, 9, 18, 19, 28, 29, 38, 39 };
	KEYANIMANAGER->addArrayFrameAnimation("dead", "ranger", dead, 8, 10.0, false);
}

void player::status_init_paladin()
{
	_status.level = 1;
	_status.hp = 75;
	_status.mp = 50;
	_status.max_hp = 75;
	_status.max_mp = 50;
	_status.hp_regen = 0.0f;
	_status.mp_regen = 0.40f;
	_status.move_speed = 2.0f;
	_status.exp = 0.0f;

	_status.damage = 16;
	_status.attack_dmg = 0;
	_status.ability_power = 0;
	_status.crit = 0;
	_status.evasion = 0;
	_status.armor = 10;
	_status.resistance = 0;
	_status.luck = 0;

	_status.dash_speed = 4.0f;
	_status.skill_cd = 0.316f;

	// ½ºÅ³ µ¥¹ÌÁö, ¸Æ½º ÄðÅ¸ÀÓ, ÇöÀç ÄðÅ¸ÀÓ
}

void player::attack_paladin()
{
	if (_player.direction == Player_Direction::LEFT)
	{
		rotation_mat = IMAGEMANAGER->findImage("smash_effect")->Frame_rotation_matrix(_player.rc.left - 40, _player.rc.top - 15, 180.0f);
		smash_effect->startEffect(_player.x - 40, _player.y - 15);
		_hitbox->fire(_player.x - 40, _player.y - 15, 40, 40);
	}
	if (_player.direction == Player_Direction::TOP)
	{
		rotation_mat = IMAGEMANAGER->findImage("smash_effect")->Frame_rotation_matrix(_player.rc.left + 5, _player.rc.top - 30, -90.0f);
		smash_effect->startEffect(_player.x + 5, _player.y - 30);
		_hitbox->fire(_player.x - 20, _player.y - 30, 40, 40);
	}
	if (_player.direction == Player_Direction::RIGHT)
	{
		rotation_mat = IMAGEMANAGER->findImage("smash_effect")->Frame_rotation_matrix(_player.x + 30, _player.y + 5, 0.0f);
		smash_effect->startEffect(_player.x + 30, _player.y + 5);
		_hitbox->fire(_player.x, _player.y - 15, 40, 40);
	}
	if (_player.direction == Player_Direction::BOTTOM)
	{
		rotation_mat = IMAGEMANAGER->findImage("smash_effect")->Frame_rotation_matrix(_player.rc.left - 15, _player.rc.top + 20, 90.0f);
		smash_effect->startEffect(_player.x - 15, _player.y + 20);
		_hitbox->fire(_player.x - 15, _player.y, 40, 40);
	}
	if (_player.direction == Player_Direction::LEFT_TOP)
	{
		rotation_mat = IMAGEMANAGER->findImage("smash_effect")->Frame_rotation_matrix(_player.rc.left - 15, _player.rc.top - 40, 225.0f);
		smash_effect->startEffect(_player.x - 15, _player.y - 40);
		_hitbox->fire(_player.x - 30, _player.y - 35, 40, 40);
	}
	if (_player.direction == Player_Direction::RIGHT_TOP)
	{
		rotation_mat = IMAGEMANAGER->findImage("smash_effect")->Frame_rotation_matrix(_player.rc.left + 20, _player.rc.top - 25, 315.0f);
		smash_effect->startEffect(_player.x + 20, _player.y - 25);
		_hitbox->fire(_player.x - 10, _player.y - 25, 40, 40);
	}
	if (_player.direction == Player_Direction::LEFT_BOTTOM)
	{
		rotation_mat = IMAGEMANAGER->findImage("smash_effect")->Frame_rotation_matrix(_player.rc.left - 35, _player.rc.top + 10, 135.0f);
		smash_effect->startEffect(_player.x - 35, _player.y + 10);
		_hitbox->fire(_player.x - 35, _player.y, 40, 40);
	}
	if (_player.direction == Player_Direction::RIGHT_BOTTOM)
	{
		rotation_mat = IMAGEMANAGER->findImage("smash_effect")->Frame_rotation_matrix(_player.rc.left + 15, _player.rc.top + 20, 45.0f);
		smash_effect->startEffect(_player.x + 15, _player.y + 20);
		_hitbox->fire(_player.x, _player.y, 40, 40);
	}
}

void player::skillAnimation_paladin()
{
	if (_player.direction == Player_Direction::LEFT)
	{
		player_action = KEYANIMANAGER->findAnimation("left_run");
		player_action->start();

		rotation_mat = IMAGEMANAGER->findImage("smash_effect")->Frame_rotation_matrix(_player.rc.left, _player.rc.top, 0.0f);
	}
	if (_player.direction == Player_Direction::TOP)
	{
		player_action = KEYANIMANAGER->findAnimation("top_run");
		player_action->start();

		rotation_mat = IMAGEMANAGER->findImage("smash_effect")->Frame_rotation_matrix(_player.rc.left, _player.rc.top, 0.0f);
	}
	if (_player.direction == Player_Direction::RIGHT)
	{
		player_action = KEYANIMANAGER->findAnimation("right_run");
		player_action->start();

		rotation_mat = IMAGEMANAGER->findImage("smash_effect")->Frame_rotation_matrix(_player.rc.left, _player.rc.top, 0.0f);
	}
	if (_player.direction == Player_Direction::BOTTOM)
	{
		player_action = KEYANIMANAGER->findAnimation("bottom_run");
		player_action->start();

		rotation_mat = IMAGEMANAGER->findImage("smash_effect")->Frame_rotation_matrix(_player.rc.left, _player.rc.top, 0.0f);
	}
	if (_player.direction == Player_Direction::LEFT_TOP)
	{
		player_action = KEYANIMANAGER->findAnimation("left_top_run");
		player_action->start();

		rotation_mat = IMAGEMANAGER->findImage("smash_effect")->Frame_rotation_matrix(_player.rc.left, _player.rc.top, 0.0f);
	}
	if (_player.direction == Player_Direction::RIGHT_TOP)
	{
		player_action = KEYANIMANAGER->findAnimation("right_top_run");
		player_action->start();

		rotation_mat = IMAGEMANAGER->findImage("smash_effect")->Frame_rotation_matrix(_player.rc.left, _player.rc.top, 0.0f);
	}
	if (_player.direction == Player_Direction::LEFT_BOTTOM)
	{
		player_action = KEYANIMANAGER->findAnimation("left_bottom_run");
		player_action->start();

		rotation_mat = IMAGEMANAGER->findImage("smash_effect")->Frame_rotation_matrix(_player.rc.left, _player.rc.top, 0.0f);
	}
	if (_player.direction == Player_Direction::RIGHT_BOTTOM)
	{
		player_action = KEYANIMANAGER->findAnimation("right_bottom_run");
		player_action->start();

		rotation_mat = IMAGEMANAGER->findImage("smash_effect")->Frame_rotation_matrix(_player.rc.left, _player.rc.top, 0.0f);
	}

}

void player::skillAction_paladin()
{
	effect_interval += TIMEMANAGER->getElapsedTime();

	if (_player.direction == Player_Direction::TOP)
	{
		EFFECTMANAGER->play("dash", _player.x + RND->getFromFloatTo(0, 20), _player.rc.bottom);
		_player.angle = PI / 2;
		if (effect_interval > 0.1 && effect_interval < 0.15)
		{
			_hitbox->fire(_player.rc.left, _player.rc.top, 40, 40);
		}
	}
	else if (_player.direction == Player_Direction::BOTTOM)
	{
		EFFECTMANAGER->play("dash", _player.x + RND->getFromFloatTo(0, 20), _player.rc.top);
		_player.angle = PI + PI / 2;
		if (effect_interval > 0.1 && effect_interval < 0.15)
		{
			_hitbox->fire(_player.rc.left, _player.rc.top, 40, 40);
		}
	}
	else if (_player.direction == Player_Direction::LEFT)
	{
		EFFECTMANAGER->play("dash", _player.x + RND->getFromFloatTo(0, 20), _player.y + RND->getFromFloatTo(15, 25));
		_player.angle = PI;
		if (effect_interval > 0.1 && effect_interval < 0.15)
		{
			_hitbox->fire(_player.rc.left, _player.rc.top, 40, 40);
		}
	}
	else if (_player.direction == Player_Direction::RIGHT)
	{
		EFFECTMANAGER->play("dash", _player.x - RND->getFromFloatTo(0, 20), _player.y + RND->getFromFloatTo(15, 25));
		_player.angle = 0.0f;
		if (effect_interval > 0.1 && effect_interval < 0.15)
		{
			_hitbox->fire(_player.rc.left, _player.rc.top, 40, 40);
		}
	}
	else if (_player.direction == Player_Direction::LEFT_TOP || _player.direction == Player_Direction::LEFT_BOTTOM)
	{
		EFFECTMANAGER->play("dash", _player.x + RND->getFromFloatTo(0, 20), _player.rc.bottom);
		if (effect_interval > 0.1 && effect_interval < 0.15)
		{
			_hitbox->fire(_player.rc.left, _player.rc.top, 40, 40);
		}
	}
	else
	{
		EFFECTMANAGER->play("dash", _player.x - RND->getFromFloatTo(0, 20), _player.rc.bottom);
		if (effect_interval > 0.1 && effect_interval < 0.15)
		{
			_hitbox->fire(_player.rc.left, _player.rc.top, 40, 40);
		}
	}

	_player.x += _status.dash_speed * cos(_player.angle);
	_player.y += _status.dash_speed * -sin(_player.angle);

	_player.moving_direction = _player.direction;

	_player.rc = D2DMANAGER->RectMakeCenter(_player.x, _player.y, _player.width, _player.height);

	if (getDistance(_player.start_xPos, _player.start_yPos, _player.x, _player.y) > 75 || is_hit)
	{
		action_done = true;
		effect_interval = 0;
	}

	if (action_done)
	{
		_player.state = Player_State::RUN;
		animation_setting();
	}
}
