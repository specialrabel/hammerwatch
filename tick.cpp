#include "stdafx.h"
#include "tick.h"

HRESULT tick::init(float x, float y)
{
	IMAGEMANAGER->addFrameImage("ticks", L"monster/tick.png", 480, 240, 12, 6);

	animation_init();
	enemy_img = IMAGEMANAGER->findImage("ticks");
	enemy_body = KEYANIMANAGER->findAnimation("right_idle_tick");
	enemy_body->start();

	_rc = D2DMANAGER->RectMakeCenter(x, y,
		30, 30);

	max_hp = hp = 20;

	_x = x;
	_y = y;
	_width = _rc.right - _rc.left;
	_height = _rc.bottom - _rc.top;

	_speed = 1.5f;
	_angle = 0.0f;

	_state = enemy_state::IDLE;
	_direction = enemy_direction::RIGHT;
	_kind = enemy_kind::TICKS;

	_elapsedSec = 0;
	_frameUpdateSec = 1.0f / 60;

	_index = 0;
	count = 0;
	acition_count = 0;

	is_find = false;
	is_arrived = false;
	is_done = false;

	return S_OK;
}

void tick::release()
{
}

void tick::update()
{
	past_direction = _direction;

	state_action();

	update_direction();

	if (past_direction != _direction)
	{
		animation_setting();
	}

	if (is_arrived)
	{
		count += TIMEMANAGER->getElapsedTime();
	}

	if (count > 1.0f)
	{
		_state = enemy_state::ATTACK;
		//_hitBox = D2D1::RectF(_list[_index].left - 10, _list[_index].top - 10, _list[_index].left + 32, _list[_index].top + 32);
		//_hitBox = new D2D1_RECT_F(D2D1::RectF(_list[_index].left - 10, _list[_index].top - 10, _list[_index].left + 32, _list[_index].top + 32));
		animation_setting();
		count = 0;
	}

	if (is_find && _state == enemy_state::IDLE)
	{
		_state = enemy_state::RUN;
		animation_setting();
	}
	else if (!is_find && _state == enemy_state::RUN)
	{
		_state = enemy_state::IDLE;
		animation_setting();
	}

}

void tick::render()
{
	enemy_img->aniRender(_rc.left, _rc.top, enemy_body);

	//D2DMANAGER->Rectangle(_rc);
}

void tick::move()
{
	float enemy_x = (_rc.left + _rc.right) / 2;
	float enemy_y = (_rc.top + _rc.bottom) / 2;

	D2D1_RECT_F temp = _list[_index];

	float dest_x = (temp.left + temp.right) / 2;
	float dest_y = (temp.top + temp.bottom) / 2;

	float distance = getDistance(enemy_x, enemy_y, dest_x, dest_y);
	float angle = getAngle(enemy_x, enemy_y, dest_x, dest_y);

	_angle = angle;

	if (distance > 3 && !is_arrived)
	{
		_rc.left += _speed * cosf(angle)* TIMEMANAGER->getElapsedTime() * 60;
		_rc.right = _rc.left + _width;

		_rc.top += RND->getFromFloatTo(0.0f, 2.0f) * -sinf(angle)* TIMEMANAGER->getElapsedTime() * 60;
		_rc.bottom = _rc.top + _height;
	}
	else
	{
		is_done = true;
	}

	if (is_done)
	{
		_index -= 1;
		is_done = false;
	}

	if (_index <= 0)
	{
		_index = 0;
		is_arrived = true;
	}

}

void tick::attack()
{
	acition_count += TIMEMANAGER->getElapsedTime();

	float enemy_x = (_rc.left + _rc.right) / 2;
	float enemy_y = (_rc.top + _rc.bottom) / 2;

	float dest_x = (_destination.left + _destination.right) / 2;
	float dest_y = (_destination.top + _destination.bottom) / 2;

	_angle = getAngle(enemy_x, enemy_y, dest_x, dest_y);

	if (acition_count > 0.5f)
	{
		acition_count = 0;

		_hitBox = { _destination.left - 10, _destination.top - 10, _destination.left + 32, _destination.top + 32 };
		_state = enemy_state::RUN;
		animation_setting();

		is_arrived = false;
	}

}

void tick::state_action()
{
	switch (_state)
	{
	case enemy_state::RUN:
		move();
		break;
	case enemy_state::ATTACK:
		attack();
		break;
	}
}

void tick::update_direction()
{
	if (_angle >= PI2) _angle -= PI2;
	if (_angle <= 0) _angle += PI2;

	if (_angle > 0 && _angle <= PI8)
	{
		_direction = enemy_direction::RIGHT;
	}
	else if (_angle > PI8 && _angle <= 3 * PI8)
	{
		_direction = enemy_direction::RIGHT_TOP;
	}
	else if (_angle > 3 * PI8 && _angle <= 5 * PI8)
	{
		_direction = enemy_direction::TOP;
	}
	else if (_angle > 5 * PI8 && _angle <= 7 * PI8)
	{
		_direction = enemy_direction::LEFT_TOP;
	}
	else if (_angle > 7 * PI8 && _angle <= 9 * PI8)
	{
		_direction = enemy_direction::LEFT;
	}
	else if (_angle > 9 * PI8 && _angle <= 11 * PI8)
	{
		_direction = enemy_direction::LEFT_BOTTOM;
	}
	else if (_angle > 11 * PI8 && _angle <= 13 * PI8)
	{
		_direction = enemy_direction::BOTTOM;
	}
	else if (_angle > 13 * PI8 && _angle <= 15 * PI8)
	{
		_direction = enemy_direction::RIGHT_BOTTOM;
	}
	else
	{
		_direction = enemy_direction::RIGHT;
	}
}

void tick::animation_init()
{
	int left_idle[] = { 12, 15 };
	KEYANIMANAGER->addArrayFrameAnimation("left_idle_tick", "ticks", left_idle, 2, 4.0, true);
	int left_run[] = { 18, 21 };
	KEYANIMANAGER->addArrayFrameAnimation("left_run_tick", "ticks", left_run, 2, 4.0, true);
	int left_attack[] = { 48, 51 };
	KEYANIMANAGER->addArrayFrameAnimation("left_attack_tick", "ticks", left_attack, 2, 10.0, false);

	int left_top_idle[] = { 0, 3 };
	KEYANIMANAGER->addArrayFrameAnimation("left_top_idle_tick", "ticks", left_top_idle, 2, 4.0, true);
	int left_top_run[] = { 6, 9 };
	KEYANIMANAGER->addArrayFrameAnimation("left_top_run_tick", "ticks", left_top_run, 2, 4.0, true);
	int left_top_attack[] = { 36, 39 };
	KEYANIMANAGER->addArrayFrameAnimation("left_top_attack_tick", "ticks", left_top_attack, 2, 10.0, false);

	int top_idle[] = { 1, 4 };
	KEYANIMANAGER->addArrayFrameAnimation("top_idle_tick", "ticks", top_idle, 2, 4.0, true);
	int top_run[] = { 7, 10 };
	KEYANIMANAGER->addArrayFrameAnimation("top_run_tick", "ticks", top_run, 2, 4.0, true);
	int top_attack[] = { 37, 40 };
	KEYANIMANAGER->addArrayFrameAnimation("top_attack_tick", "ticks", top_attack, 2, 10.0, false);

	int right_top_idle[] = { 2, 5 };
	KEYANIMANAGER->addArrayFrameAnimation("right_top_idle_tick", "ticks", right_top_idle, 2, 4.0, true);
	int right_top_run[] = { 8, 11 };
	KEYANIMANAGER->addArrayFrameAnimation("right_top_run_tick", "ticks", right_top_run, 2, 4.0, true);
	int right_top_attack[] = { 38, 41 };
	KEYANIMANAGER->addArrayFrameAnimation("right_top_attack_tick", "ticks", right_top_attack, 2, 10.0, false);

	int right_idle[] = { 14, 17 };
	KEYANIMANAGER->addArrayFrameAnimation("right_idle_tick", "ticks", right_idle, 2, 4.0, true);
	int right_run[] = { 20, 23 };
	KEYANIMANAGER->addArrayFrameAnimation("right_run_tick", "ticks", right_run, 2, 4.0, true);
	int right_attack[] = { 50, 53 };
	KEYANIMANAGER->addArrayFrameAnimation("right_attack_tick", "ticks", right_attack, 2, 10.0, false);

	int left_bottom_idle[] = { 24, 27 };
	KEYANIMANAGER->addArrayFrameAnimation("left_bottom_idle_tick", "ticks", left_bottom_idle, 2, 4.0, true);
	int left_bottom_run[] = { 30, 33 };
	KEYANIMANAGER->addArrayFrameAnimation("left_bottom_run_tick", "ticks", left_bottom_run, 2, 4.0, true);
	int left_bottom_attack[] = { 60, 63 };
	KEYANIMANAGER->addArrayFrameAnimation("left_bottom_attack_tick", "ticks", left_bottom_attack, 2, 10.0, false);

	int bottom_idle[] = { 25, 28 };
	KEYANIMANAGER->addArrayFrameAnimation("bottom_idle_tick", "ticks", bottom_idle, 2, 4.0, true);
	int bottom_run[] = { 31, 34 };
	KEYANIMANAGER->addArrayFrameAnimation("bottom_run_tick", "ticks", bottom_run, 2, 4.0, true);
	int bottom_attack[] = { 61, 64 };
	KEYANIMANAGER->addArrayFrameAnimation("bottom_attack_tick", "ticks", bottom_attack, 2, 10.0, false);

	int right_bottom_idle[] = { 26, 29 };
	KEYANIMANAGER->addArrayFrameAnimation("right_bottom_idle_tick", "ticks", right_bottom_idle, 2, 4.0, true);
	int right_bottom_run[] = { 32, 35 };
	KEYANIMANAGER->addArrayFrameAnimation("right_bottom_run_tick", "ticks", right_bottom_run, 2, 4.0, true);
	int right_bottom_attack[] = { 62, 65 };
	KEYANIMANAGER->addArrayFrameAnimation("right_bottom_attack_tick", "ticks", right_bottom_attack, 2, 10.0, false);

}

void tick::animation_setting()
{
	switch (_direction)
	{
	case enemy_direction::LEFT:
		if (_state == enemy_state::IDLE)
		{
			enemy_body = KEYANIMANAGER->findAnimation("left_idle_tick");
			enemy_body->start();
		}
		if (_state == enemy_state::RUN)
		{
			enemy_body = KEYANIMANAGER->findAnimation("left_run_tick");
			enemy_body->start();
		}
		if (_state == enemy_state::ATTACK)
		{
			enemy_body = KEYANIMANAGER->findAnimation("left_attack_tick");
			enemy_body->start();

		}
		break;
	case enemy_direction::TOP:
		if (_state == enemy_state::IDLE)
		{
			enemy_body = KEYANIMANAGER->findAnimation("top_idle_tick");
			enemy_body->start();
		}
		if (_state == enemy_state::RUN)
		{
			enemy_body = KEYANIMANAGER->findAnimation("top_run_tick");
			enemy_body->start();
		}
		if (_state == enemy_state::ATTACK)
		{
			enemy_body = KEYANIMANAGER->findAnimation("top_attack_tick");
			enemy_body->start();

		}
		break;

	case enemy_direction::RIGHT:
		if (_state == enemy_state::IDLE)
		{
			enemy_body = KEYANIMANAGER->findAnimation("right_idle_tick");
			enemy_body->start();
		}
		if (_state == enemy_state::RUN)
		{
			enemy_body = KEYANIMANAGER->findAnimation("right_run_tick");
			enemy_body->start();
		}
		if (_state == enemy_state::ATTACK)
		{
			enemy_body = KEYANIMANAGER->findAnimation("right_attack_tick");
			enemy_body->start();
		}
		break;

	case enemy_direction::BOTTOM:
		if (_state == enemy_state::IDLE)
		{
			enemy_body = KEYANIMANAGER->findAnimation("bottom_idle_tick");
			enemy_body->start();
		}
		if (_state == enemy_state::RUN)
		{
			enemy_body = KEYANIMANAGER->findAnimation("bottom_run_tick");
			enemy_body->start();
		}
		if (_state == enemy_state::ATTACK)
		{
			enemy_body = KEYANIMANAGER->findAnimation("bottom_attack_tick");
			enemy_body->start();
		}
		break;

	case enemy_direction::LEFT_TOP:
		if (_state == enemy_state::IDLE)
		{
			enemy_body = KEYANIMANAGER->findAnimation("left_top_idle_tick");
			enemy_body->start();
		}
		if (_state == enemy_state::RUN)
		{
			enemy_body = KEYANIMANAGER->findAnimation("left_top_run_tick");
			enemy_body->start();
		}
		if (_state == enemy_state::ATTACK)
		{
			enemy_body = KEYANIMANAGER->findAnimation("left_top_attack_tick");
			enemy_body->start();
		}
		break;
	case enemy_direction::RIGHT_TOP:
		if (_state == enemy_state::IDLE)
		{
			enemy_body = KEYANIMANAGER->findAnimation("right_top_idle_tick");
			enemy_body->start();
		}
		if (_state == enemy_state::RUN)
		{
			enemy_body = KEYANIMANAGER->findAnimation("right_top_run_tick");
			enemy_body->start();
		}
		if (_state == enemy_state::ATTACK)
		{
			enemy_body = KEYANIMANAGER->findAnimation("right_top_attack_tick");
			enemy_body->start();
		}
		break;

	case enemy_direction::LEFT_BOTTOM:
		if (_state == enemy_state::IDLE)
		{
			enemy_body = KEYANIMANAGER->findAnimation("left_bottom_idle_tick");
			enemy_body->start();
		}
		if (_state == enemy_state::RUN)
		{
			enemy_body = KEYANIMANAGER->findAnimation("left_bottom_run_tick");
			enemy_body->start();
		}
		if (_state == enemy_state::ATTACK)
		{
			enemy_body = KEYANIMANAGER->findAnimation("left_bottom_attack_tick");
			enemy_body->start();
		}
		break;
	case enemy_direction::RIGHT_BOTTOM:
		if (_state == enemy_state::IDLE)
		{
			enemy_body = KEYANIMANAGER->findAnimation("right_bottom_idle_tick");
			enemy_body->start();
		}
		if (_state == enemy_state::RUN)
		{
			enemy_body = KEYANIMANAGER->findAnimation("right_bottom_run_tick");
			enemy_body->start();
		}
		if (_state == enemy_state::ATTACK)
		{
			enemy_body = KEYANIMANAGER->findAnimation("right_bottom_attack_tick");
			enemy_body->start();
		}
	}
}
