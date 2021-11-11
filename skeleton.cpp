#include "stdafx.h"
#include "skeleton.h"

HRESULT skeleton::init(float x, float y)
{
	IMAGEMANAGER->addFrameImage("skeletons", L"monster/skeleton.png", 480, 240, 10, 5);

	animation_init();
	enemy_img = IMAGEMANAGER->findImage("skeletons");
	enemy_body = KEYANIMANAGER->findAnimation("right_idle_skeleton");
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
	_kind = enemy_kind::SKELETON;

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

void skeleton::release()
{
}

void skeleton::update()
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

void skeleton::render()
{
	enemy_img->aniRender(_rc.left - 10, _rc.top - 8, enemy_body);

	//D2DMANAGER->Rectangle(_rc);
}

void skeleton::idle()
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

void skeleton::idle_run()
{
	idle_count += TIMEMANAGER->getElapsedTime();

	_rc.left += _speed * 0.5 * cosf(_angle)* TIMEMANAGER->getElapsedTime() * 60;
	_rc.right = _rc.left + _width;

	_rc.top += RND->getFromFloatTo(0.0f, 2.0f) * -sinf(_angle)* TIMEMANAGER->getElapsedTime() * 60;
	_rc.bottom = _rc.top + _height;

	if (idle_count > 1.5f)
	{
		_state = enemy_state::IDLE;
		animation_setting();
		idle_count = 0;
	}
}

void skeleton::move()
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

		_rc.top += _speed * 0.5 * -sinf(angle)* TIMEMANAGER->getElapsedTime() * 60;
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

void skeleton::attack()
{
	acition_count += TIMEMANAGER->getElapsedTime();

	float enemy_x = (_rc.left + _rc.right) / 2;
	float enemy_y = (_rc.top + _rc.bottom) / 2;

	float dest_x = (_destination.left + _destination.right) / 2;
	float dest_y = (_destination.top + _destination.bottom) / 2;

	_angle = getAngle(enemy_x, enemy_y, dest_x, dest_y);

	if (acition_count > 0.5f)
	{
		_hitBox = { _destination.left - 10, _destination.top - 10, _destination.left + 32, _destination.top + 32 };

		_state = enemy_state::IDLE;
		acition_count = 0;
		animation_setting();

		is_arrived = false;
	}
}

void skeleton::state_action()
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

void skeleton::update_direction()
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

void skeleton::animation_init()
{
	int left_idle[] = { 4 };
	KEYANIMANAGER->addArrayFrameAnimation("left_idle_skeleton", "skeletons", left_idle, 1, 4.0, true);
	int left_run[] = { 4, 14, 24 };
	KEYANIMANAGER->addArrayFrameAnimation("left_run_skeleton", "skeletons", left_run, 3, 4.0, true);
	int left_attack[] = { 34, 44 };
	KEYANIMANAGER->addArrayFrameAnimation("left_attack_skeleton", "skeletons", left_attack, 2, 10.0, false);

	int left_top_idle[] = { 3 };
	KEYANIMANAGER->addArrayFrameAnimation("left_top_idle_skeleton", "skeletons", left_top_idle, 1, 4.0, true);
	int left_top_run[] = { 3, 13, 23 };
	KEYANIMANAGER->addArrayFrameAnimation("left_top_run_skeleton", "skeletons", left_top_run, 3, 4.0, true);
	int left_top_attack[] = { 33, 43 };
	KEYANIMANAGER->addArrayFrameAnimation("left_top_attack_skeleton", "skeletons", left_top_attack, 2, 10.0, false);

	int top_idle[] = { 2 };
	KEYANIMANAGER->addArrayFrameAnimation("top_idle_skeleton", "skeletons", top_idle, 1, 4.0, true);
	int top_run[] = { 2, 12, 22 };
	KEYANIMANAGER->addArrayFrameAnimation("top_run_skeleton", "skeletons", top_run, 3, 4.0, true);
	int top_attack[] = { 32, 42 };
	KEYANIMANAGER->addArrayFrameAnimation("top_attack_skeleton", "skeletons", top_attack, 2, 10.0, false);

	int right_top_idle[] = { 1 };
	KEYANIMANAGER->addArrayFrameAnimation("right_top_idle_skeleton", "skeletons", right_top_idle, 1, 4.0, true);
	int right_top_run[] = { 1, 11, 21 };
	KEYANIMANAGER->addArrayFrameAnimation("right_top_run_skeleton", "skeletons", right_top_run, 3, 4.0, true);
	int right_top_attack[] = { 31, 41 };
	KEYANIMANAGER->addArrayFrameAnimation("right_top_attack_skeleton", "skeletons", right_top_attack, 2, 10.0, false);

	int right_idle[] = { 0 };
	KEYANIMANAGER->addArrayFrameAnimation("right_idle_skeleton", "skeletons", right_idle, 1, 4.0, true);
	int right_run[] = { 0, 10, 20 };
	KEYANIMANAGER->addArrayFrameAnimation("right_run_skeleton", "skeletons", right_run, 3, 4.0, true);
	int right_attack[] = { 30, 40 };
	KEYANIMANAGER->addArrayFrameAnimation("right_attack_skeleton", "skeletons", right_attack, 2, 10.0, false);

	int left_bottom_idle[] = { 5 };
	KEYANIMANAGER->addArrayFrameAnimation("left_bottom_idle_skeleton", "skeletons", left_bottom_idle, 1, 4.0, true);
	int left_bottom_run[] = { 5, 15, 25 };
	KEYANIMANAGER->addArrayFrameAnimation("left_bottom_run_skeleton", "skeletons", left_bottom_run, 3, 4.0, true);
	int left_bottom_attack[] = { 35, 45 };
	KEYANIMANAGER->addArrayFrameAnimation("left_bottom_attack_skeleton", "skeletons", left_bottom_attack, 2, 10.0, false);

	int bottom_idle[] = { 6 };
	KEYANIMANAGER->addArrayFrameAnimation("bottom_idle_skeleton", "skeletons", bottom_idle, 1, 4.0, true);
	int bottom_run[] = { 6, 16, 26 };
	KEYANIMANAGER->addArrayFrameAnimation("bottom_run_skeleton", "skeletons", bottom_run, 3, 4.0, true);
	int bottom_attack[] = { 36, 46 };
	KEYANIMANAGER->addArrayFrameAnimation("bottom_attack_skeleton", "skeletons", bottom_attack, 2, 10.0, false);

	int right_bottom_idle[] = { 7 };
	KEYANIMANAGER->addArrayFrameAnimation("right_bottom_idle_skeleton", "skeletons", right_bottom_idle, 1, 4.0, true);
	int right_bottom_run[] = { 7, 17, 27 };
	KEYANIMANAGER->addArrayFrameAnimation("right_bottom_run_skeleton", "skeletons", right_bottom_run, 3, 4.0, true);
	int right_bottom_attack[] = { 37, 47 };
	KEYANIMANAGER->addArrayFrameAnimation("right_bottom_attack_skeleton", "skeletons", right_bottom_attack, 2, 10.0, false);

}

void skeleton::animation_setting()
{
	switch (_direction)
	{
	case enemy_direction::LEFT:
		if (_state == enemy_state::IDLE)
		{
			enemy_body = KEYANIMANAGER->findAnimation("left_idle_skeleton");
			enemy_body->start();
		}
		if (_state == enemy_state::IDLE_RUN)
		{
			enemy_body = KEYANIMANAGER->findAnimation("left_run_skeleton");
			enemy_body->start();
		}
		if (_state == enemy_state::RUN)
		{
			enemy_body = KEYANIMANAGER->findAnimation("left_run_skeleton");
			enemy_body->start();
		}
		if (_state == enemy_state::ATTACK)
		{
			enemy_body = KEYANIMANAGER->findAnimation("left_attack_skeleton");
			enemy_body->start();

		}
		break;
	case enemy_direction::TOP:
		if (_state == enemy_state::IDLE)
		{
			enemy_body = KEYANIMANAGER->findAnimation("top_idle_skeleton");
			enemy_body->start();
		}
		if (_state == enemy_state::IDLE_RUN)
		{
			enemy_body = KEYANIMANAGER->findAnimation("top_run_skeleton");
			enemy_body->start();
		}
		if (_state == enemy_state::RUN)
		{
			enemy_body = KEYANIMANAGER->findAnimation("top_run_skeleton");
			enemy_body->start();
		}
		if (_state == enemy_state::ATTACK)
		{
			enemy_body = KEYANIMANAGER->findAnimation("top_attack_skeleton");
			enemy_body->start();

		}
		break;

	case enemy_direction::RIGHT:
		if (_state == enemy_state::IDLE)
		{
			enemy_body = KEYANIMANAGER->findAnimation("right_idle_skeleton");
			enemy_body->start();
		}
		if (_state == enemy_state::IDLE_RUN)
		{
			enemy_body = KEYANIMANAGER->findAnimation("right_run_skeleton");
			enemy_body->start();
		}
		if (_state == enemy_state::RUN)
		{
			enemy_body = KEYANIMANAGER->findAnimation("right_run_skeleton");
			enemy_body->start();
		}
		if (_state == enemy_state::ATTACK)
		{
			enemy_body = KEYANIMANAGER->findAnimation("right_attack_skeleton");
			enemy_body->start();
		}
		break;

	case enemy_direction::BOTTOM:
		if (_state == enemy_state::IDLE)
		{
			enemy_body = KEYANIMANAGER->findAnimation("bottom_idle_skeleton");
			enemy_body->start();
		}
		if (_state == enemy_state::IDLE_RUN)
		{
			enemy_body = KEYANIMANAGER->findAnimation("bottom_run_skeleton");
			enemy_body->start();
		}
		if (_state == enemy_state::RUN)
		{
			enemy_body = KEYANIMANAGER->findAnimation("bottom_run_skeleton");
			enemy_body->start();
		}
		if (_state == enemy_state::ATTACK)
		{
			enemy_body = KEYANIMANAGER->findAnimation("bottom_attack_skeleton");
			enemy_body->start();
		}
		break;

	case enemy_direction::LEFT_TOP:
		if (_state == enemy_state::IDLE)
		{
			enemy_body = KEYANIMANAGER->findAnimation("left_top_idle_skeleton");
			enemy_body->start();
		}
		if (_state == enemy_state::IDLE_RUN)
		{
			enemy_body = KEYANIMANAGER->findAnimation("left_top_run_skeleton");
			enemy_body->start();
		}
		if (_state == enemy_state::RUN)
		{
			enemy_body = KEYANIMANAGER->findAnimation("left_top_run_skeleton");
			enemy_body->start();
		}
		if (_state == enemy_state::ATTACK)
		{
			enemy_body = KEYANIMANAGER->findAnimation("left_top_attack_skeleton");
			enemy_body->start();
		}
		break;
	case enemy_direction::RIGHT_TOP:
		if (_state == enemy_state::IDLE)
		{
			enemy_body = KEYANIMANAGER->findAnimation("right_top_idle_skeleton");
			enemy_body->start();
		}
		if (_state == enemy_state::IDLE_RUN)
		{
			enemy_body = KEYANIMANAGER->findAnimation("right_top_run_skeleton");
			enemy_body->start();
		}
		if (_state == enemy_state::RUN)
		{
			enemy_body = KEYANIMANAGER->findAnimation("right_top_run_skeleton");
			enemy_body->start();
		}
		if (_state == enemy_state::ATTACK)
		{
			enemy_body = KEYANIMANAGER->findAnimation("right_top_attack_skeleton");
			enemy_body->start();
		}
		break;

	case enemy_direction::LEFT_BOTTOM:
		if (_state == enemy_state::IDLE)
		{
			enemy_body = KEYANIMANAGER->findAnimation("left_bottom_idle_skeleton");
			enemy_body->start();
		}
		if (_state == enemy_state::IDLE_RUN)
		{
			enemy_body = KEYANIMANAGER->findAnimation("left_bottom_run_skeleton");
			enemy_body->start();
		}
		if (_state == enemy_state::RUN)
		{
			enemy_body = KEYANIMANAGER->findAnimation("left_bottom_run_skeleton");
			enemy_body->start();
		}
		if (_state == enemy_state::ATTACK)
		{
			enemy_body = KEYANIMANAGER->findAnimation("left_bottom_attack_skeleton");
			enemy_body->start();
		}
		break;
	case enemy_direction::RIGHT_BOTTOM:
		if (_state == enemy_state::IDLE)
		{
			enemy_body = KEYANIMANAGER->findAnimation("right_bottom_idle_skeleton");
			enemy_body->start();
		}
		if (_state == enemy_state::IDLE_RUN)
		{
			enemy_body = KEYANIMANAGER->findAnimation("right_bottom_run_skeleton");
			enemy_body->start();
		}
		if (_state == enemy_state::RUN)
		{
			enemy_body = KEYANIMANAGER->findAnimation("right_bottom_run_skeleton");
			enemy_body->start();
		}
		if (_state == enemy_state::ATTACK)
		{
			enemy_body = KEYANIMANAGER->findAnimation("right_bottom_attack_skeleton");
			enemy_body->start();
		}
	}
}
