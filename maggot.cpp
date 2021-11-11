#include "stdafx.h"
#include "maggot.h"

HRESULT maggot::init(float x, float y)
{
	IMAGEMANAGER->addFrameImage("maggots", L"monster/maggot.png", 580, 380, 9, 6);

	animation_init();
	enemy_img = IMAGEMANAGER->findImage("maggots");
	enemy_body = KEYANIMANAGER->findAnimation("right_run_maggot");
	enemy_body->start();

	_rc = D2DMANAGER->RectMakeCenter(x, y,
		30, 30);

	max_hp = hp = 20;

	_x = x;
	_y = y;
	_width = _rc.right - _rc.left;
	_height = _rc.bottom - _rc.top;

	_speed = 1.0f;
	_angle = 0.0f;

	_state = enemy_state::IDLE;
	_direction = enemy_direction::RIGHT;
	_kind = enemy_kind::MAGGOT;

	maggot_bullet = new Player_bullet;
	maggot_bullet->init(300);

	_elapsedSec = 0;
	_frameUpdateSec = 1.0f / 60;

	_index = 0;
	count = 0;
	idle_count = 0;
	acition_count = 0;

	is_find = false;
	is_arrived = false;
	is_done = false;

	return S_OK;
}

void maggot::release()
{
}

void maggot::update()
{
	past_direction = _direction;

	state_action();

	update_direction();

	if (past_direction != _direction)
	{
		animation_setting();
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

	maggot_bullet->update();

}

void maggot::render()
{
	enemy_img->aniRender(_rc.left - 10, _rc.top - 8, enemy_body);

	maggot_bullet->render();
	//D2DMANAGER->Rectangle(_rc);
}

void maggot::idle()
{
	idle_count += TIMEMANAGER->getElapsedTime();

	if (idle_count > 1.0f)
	{
		_angle = RND->getFromFloatTo(-PI * 2, PI * 2);
		update_direction();
		_state = enemy_state::IDLE_RUN;
		animation_setting();
		idle_count = 0;
	}
}

void maggot::idle_run()
{
	idle_count += TIMEMANAGER->getElapsedTime();

	_rc.left += _speed * 0.5 * cosf(_angle)* TIMEMANAGER->getElapsedTime() * 60;
	_rc.right = _rc.left + _width;

	_rc.top += _speed * 0.5 * -sinf(_angle)* TIMEMANAGER->getElapsedTime() * 60;
	_rc.bottom = _rc.top + _height;

	if (idle_count > 1.5f)
	{
		_state = enemy_state::IDLE;
		animation_setting();
		idle_count = 0;
	}
}

void maggot::move()
{
	float enemy_x = (_rc.left + _rc.right) / 2;
	float enemy_y = (_rc.top + _rc.bottom) / 2;

	D2D1_RECT_F temp = _list[_index];

	float dest_x = (temp.left + temp.right) / 2;
	float dest_y = (temp.top + temp.bottom) / 2;

	float distance = getDistance(enemy_x, enemy_y, dest_x, dest_y);
	float distance2 = getDistance(enemy_x, enemy_y, (_destination.left + _destination.right) / 2, (_destination.top + _destination.bottom) / 2);
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

	if (distance2 < 100)
	{
		is_arrived = true;

		_state = enemy_state::ATTACK;
		animation_setting();
	}
}

void maggot::attack()
{
	acition_count += TIMEMANAGER->getElapsedTime();

	float enemy_x = (_rc.left + _rc.right) / 2;
	float enemy_y = (_rc.top + _rc.bottom) / 2;

	float dest_x = (_destination.left + _destination.right) / 2;
	float dest_y = (_destination.top + _destination.bottom) / 2;

	_angle = getAngle(enemy_x, enemy_y, dest_x, dest_y);

	if (acition_count > 1.0f)
	{
		maggot_bullet->fire(L"effect/maggot_bullet.png", enemy_x, enemy_y, 15, 9, _angle, 4.0f);

		_state = enemy_state::IDLE;
		acition_count = 0;
		animation_setting();

		is_arrived = false;
	}
}

void maggot::state_action()
{
	switch (_state)
	{
	case enemy_state::IDLE:
		idle();
		break;
	case enemy_state::IDLE_RUN:
		idle_run();
		break;
	case enemy_state::RUN:
		move();
		break;
	case enemy_state::ATTACK:
		attack();
		break;
	}

}

void maggot::update_direction()
{
	if (_angle >= PI2) _angle -= PI2;
	if (_angle <= 0) _angle += PI2;

	if (_angle > 0 && _angle <= PI8)
	{
		_direction = enemy_direction::RIGHT;
		_angle = 0.0f;
	}
	else if (_angle > PI8 && _angle <= 3 * PI8)
	{
		_direction = enemy_direction::RIGHT_TOP;
	}
	else if (_angle > 3 * PI8 && _angle <= 5 * PI8)
	{
		_direction = enemy_direction::TOP;
		_angle = PI / 2;
	}
	else if (_angle > 5 * PI8 && _angle <= 7 * PI8)
	{
		_direction = enemy_direction::LEFT_TOP;
	}
	else if (_angle > 7 * PI8 && _angle <= 9 * PI8)
	{
		_direction = enemy_direction::LEFT;
		_angle = PI;
	}
	else if (_angle > 9 * PI8 && _angle <= 11 * PI8)
	{
		_direction = enemy_direction::LEFT_BOTTOM;
	}
	else if (_angle > 11 * PI8 && _angle <= 13 * PI8)
	{
		_direction = enemy_direction::BOTTOM;
		_angle = PI + PI / 2;
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

void maggot::animation_init()
{
	int left_idle[] = { 9 };
	KEYANIMANAGER->addArrayFrameAnimation("left_idle_maggot", "maggots", left_idle, 1, 4.0, true);
	int left_run[] = { 9, 12, 15 };
	KEYANIMANAGER->addArrayFrameAnimation("left_run_maggot", "maggots", left_run, 3, 4.0, true);
	int left_attack[] = { 36, 39, 42 };
	KEYANIMANAGER->addArrayFrameAnimation("left_attack_maggot", "maggots", left_attack, 3, 10, false);

	int left_top_idle[] = { 0 };
	KEYANIMANAGER->addArrayFrameAnimation("left_top_idle_maggot", "maggots", left_top_idle, 1, 4.0, true);
	int left_top_run[] = { 0, 3, 6 };
	KEYANIMANAGER->addArrayFrameAnimation("left_top_run_maggot", "maggots", left_top_run, 3, 4.0, true);
	int left_top_attack[] = { 27, 30, 33 };
	KEYANIMANAGER->addArrayFrameAnimation("left_top_attack_maggot", "maggots", left_top_attack, 3, 10, false);

	int top_idle[] = { 1 };
	KEYANIMANAGER->addArrayFrameAnimation("top_idle_maggot", "maggots", top_idle, 1, 4.0, true);
	int top_run[] = { 1, 4, 7 };
	KEYANIMANAGER->addArrayFrameAnimation("top_run_maggot", "maggots", top_run, 3, 4.0, true);
	int top_attack[] = { 28, 31, 34 };
	KEYANIMANAGER->addArrayFrameAnimation("top_attack_maggot", "maggots", top_attack, 3, 10, false);

	int right_top_idle[] = { 2 };
	KEYANIMANAGER->addArrayFrameAnimation("right_top_idle_maggot", "maggots", right_top_idle, 1, 4.0, true);
	int right_top_run[] = { 2, 5, 8 };
	KEYANIMANAGER->addArrayFrameAnimation("right_top_run_maggot", "maggots", right_top_run, 3, 4.0, true);
	int right_top_attack[] = { 29, 32, 35 };
	KEYANIMANAGER->addArrayFrameAnimation("right_top_attack_maggot", "maggots", right_top_attack, 3, 10, false);

	int right_idle[] = { 11 };
	KEYANIMANAGER->addArrayFrameAnimation("right_idle_maggot", "maggots", right_idle, 1, 4.0, true);
	int right_run[] = { 11, 14, 17 };
	KEYANIMANAGER->addArrayFrameAnimation("right_run_maggot", "maggots", right_run, 3, 4.0, true);
	int right_attack[] = { 38, 41, 44 };
	KEYANIMANAGER->addArrayFrameAnimation("right_attack_maggot", "maggots", right_attack, 3, 10, false);

	int left_bottom_idle[] = { 18 };
	KEYANIMANAGER->addArrayFrameAnimation("left_bottom_idle_maggot", "maggots", left_bottom_idle, 1, 4.0, true);
	int left_bottom_run[] = { 18, 21, 24 };
	KEYANIMANAGER->addArrayFrameAnimation("left_bottom_run_maggot", "maggots", left_bottom_run, 3, 4.0, true);
	int left_bottom_attack[] = { 45, 48, 51 };
	KEYANIMANAGER->addArrayFrameAnimation("left_bottom_attack_maggot", "maggots", left_bottom_attack, 3, 10, false);

	int bottom_idle[] = { 19 };
	KEYANIMANAGER->addArrayFrameAnimation("bottom_idle_maggot", "maggots", bottom_idle, 1, 4.0, true);
	int bottom_run[] = { 19, 22, 25 };
	KEYANIMANAGER->addArrayFrameAnimation("bottom_run_maggot", "maggots", bottom_run, 3, 4.0, true);
	int bottom_attack[] = { 46, 49, 52 };
	KEYANIMANAGER->addArrayFrameAnimation("bottom_attack_maggot", "maggots", bottom_attack, 3, 10, false);

	int right_bottom_idle[] = { 20 };
	KEYANIMANAGER->addArrayFrameAnimation("right_bottom_idle_maggot", "maggots", right_bottom_idle, 1, 4.0, true);
	int right_bottom_run[] = { 20, 23, 26 };
	KEYANIMANAGER->addArrayFrameAnimation("right_bottom_run_maggot", "maggots", right_bottom_run, 3, 4.0, true);
	int right_bottom_attack[] = { 47, 50, 53 };
	KEYANIMANAGER->addArrayFrameAnimation("right_bottom_attack_maggot", "maggots", right_bottom_attack, 3, 10, false);

}

void maggot::animation_setting()
{
	switch (_direction)
	{
	case enemy_direction::LEFT:
		if (_state == enemy_state::IDLE)
		{
			enemy_body = KEYANIMANAGER->findAnimation("left_idle_maggot");
			enemy_body->start();
		}
		if (_state == enemy_state::IDLE_RUN)
		{
			enemy_body = KEYANIMANAGER->findAnimation("left_run_maggot");
			enemy_body->start();
		}
		if (_state == enemy_state::RUN)
		{
			enemy_body = KEYANIMANAGER->findAnimation("left_run_maggot");
			enemy_body->start();
		}
		if (_state == enemy_state::ATTACK)
		{
			enemy_body = KEYANIMANAGER->findAnimation("left_attack_maggot");
			enemy_body->start();

		}
		break;
	case enemy_direction::TOP:
		if (_state == enemy_state::IDLE)
		{
			enemy_body = KEYANIMANAGER->findAnimation("top_idle_maggot");
			enemy_body->start();
		}
		if (_state == enemy_state::IDLE_RUN)
		{
			enemy_body = KEYANIMANAGER->findAnimation("top_run_maggot");
			enemy_body->start();
		}
		if (_state == enemy_state::RUN)
		{
			enemy_body = KEYANIMANAGER->findAnimation("top_run_maggot");
			enemy_body->start();
		}
		if (_state == enemy_state::ATTACK)
		{
			enemy_body = KEYANIMANAGER->findAnimation("top_attack_maggot");
			enemy_body->start();

		}
		break;

	case enemy_direction::RIGHT:
		if (_state == enemy_state::IDLE)
		{
			enemy_body = KEYANIMANAGER->findAnimation("right_idle_maggot");
			enemy_body->start();
		}
		if (_state == enemy_state::IDLE_RUN)
		{
			enemy_body = KEYANIMANAGER->findAnimation("right_run_maggot");
			enemy_body->start();
		}
		if (_state == enemy_state::RUN)
		{
			enemy_body = KEYANIMANAGER->findAnimation("right_run_maggot");
			enemy_body->start();
		}
		if (_state == enemy_state::ATTACK)
		{
			enemy_body = KEYANIMANAGER->findAnimation("right_attack_maggot");
			enemy_body->start();
		}
		break;

	case enemy_direction::BOTTOM:
		if (_state == enemy_state::IDLE)
		{
			enemy_body = KEYANIMANAGER->findAnimation("bottom_idle_maggot");
			enemy_body->start();
		}
		if (_state == enemy_state::IDLE_RUN)
		{
			enemy_body = KEYANIMANAGER->findAnimation("bottom_run_maggot");
			enemy_body->start();
		}
		if (_state == enemy_state::RUN)
		{
			enemy_body = KEYANIMANAGER->findAnimation("bottom_run_maggot");
			enemy_body->start();
		}
		if (_state == enemy_state::ATTACK)
		{
			enemy_body = KEYANIMANAGER->findAnimation("bottom_attack_maggot");
			enemy_body->start();
		}
		break;

	case enemy_direction::LEFT_TOP:
		if (_state == enemy_state::IDLE)
		{
			enemy_body = KEYANIMANAGER->findAnimation("left_top_idle_maggot");
			enemy_body->start();
		}
		if (_state == enemy_state::IDLE_RUN)
		{
			enemy_body = KEYANIMANAGER->findAnimation("left_top_run_maggot");
			enemy_body->start();
		}
		if (_state == enemy_state::RUN)
		{
			enemy_body = KEYANIMANAGER->findAnimation("left_top_run_maggot");
			enemy_body->start();
		}
		if (_state == enemy_state::ATTACK)
		{
			enemy_body = KEYANIMANAGER->findAnimation("left_top_attack_maggot");
			enemy_body->start();
		}
		break;
	case enemy_direction::RIGHT_TOP:
		if (_state == enemy_state::IDLE)
		{
			enemy_body = KEYANIMANAGER->findAnimation("right_top_idle_maggot");
			enemy_body->start();
		}
		if (_state == enemy_state::IDLE_RUN)
		{
			enemy_body = KEYANIMANAGER->findAnimation("right_top_run_maggot");
			enemy_body->start();
		}
		if (_state == enemy_state::RUN)
		{
			enemy_body = KEYANIMANAGER->findAnimation("right_top_run_maggot");
			enemy_body->start();
		}
		if (_state == enemy_state::ATTACK)
		{
			enemy_body = KEYANIMANAGER->findAnimation("right_top_attack_maggot");
			enemy_body->start();
		}
		break;

	case enemy_direction::LEFT_BOTTOM:
		if (_state == enemy_state::IDLE)
		{
			enemy_body = KEYANIMANAGER->findAnimation("left_bottom_idle_maggot");
			enemy_body->start();
		}
		if (_state == enemy_state::IDLE_RUN)
		{
			enemy_body = KEYANIMANAGER->findAnimation("left_bottom_run_maggot");
			enemy_body->start();
		}
		if (_state == enemy_state::RUN)
		{
			enemy_body = KEYANIMANAGER->findAnimation("left_bottom_run_maggot");
			enemy_body->start();
		}
		if (_state == enemy_state::ATTACK)
		{
			enemy_body = KEYANIMANAGER->findAnimation("left_bottom_attack_maggot");
			enemy_body->start();
		}
		break;
	case enemy_direction::RIGHT_BOTTOM:
		if (_state == enemy_state::IDLE)
		{
			enemy_body = KEYANIMANAGER->findAnimation("right_bottom_idle_maggot");
			enemy_body->start();
		}
		if (_state == enemy_state::IDLE_RUN)
		{
			enemy_body = KEYANIMANAGER->findAnimation("right_bottom_run_maggot");
			enemy_body->start();
		}
		if (_state == enemy_state::RUN)
		{
			enemy_body = KEYANIMANAGER->findAnimation("right_bottom_run_maggot");
			enemy_body->start();
		}
		if (_state == enemy_state::ATTACK)
		{
			enemy_body = KEYANIMANAGER->findAnimation("right_bottom_attack_maggot");
			enemy_body->start();
		}
	}
}
