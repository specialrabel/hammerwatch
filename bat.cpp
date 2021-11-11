#include "stdafx.h"
#include "bat.h"

HRESULT bat::init(float x, float y)
{
	IMAGEMANAGER->addFrameImage("bats", L"monster/bat.png", 156, 14, 6, 1);

	enemy_img = IMAGEMANAGER->findImage("bats");

	_rc = D2DMANAGER->RectMakeCenter(x, y,
		enemy_img->getFrameWidth(), enemy_img->getFrameHeight());

	max_hp = hp = 20;

	_x = x;
	_y = y;

	_width = _rc.right - _rc.left;
	_height = _rc.bottom - _rc.top;

	_currentFrameX = _currentFrameY = 0;

	_speed = 1.5f;
	_angle = 0.0f;

	_state = enemy_state::IDLE;
	_direction = enemy_direction::RIGHT;
	_kind = enemy_kind::BATS;

	_elapsedSec = 0;
	_frameUpdateSec = 1.0f / 60;

	_index = 0;
	count = 0;

	is_find = false;
	is_arrived = false;
	is_done = false;

	return S_OK;
}

void bat::release()
{
}

void bat::update()
{
	_elapsedSec += TIMEMANAGER->getElapsedTime() * 0.3;

	if (_elapsedSec >= _frameUpdateSec)
	{
		_elapsedSec -= _frameUpdateSec;
		_currentFrameX++;
	}
	if (_currentFrameX > enemy_img->getMaxFrameX())
	{
		_currentFrameX = 0;
	}

	update_direction();

	state_action();

	if (is_arrived)
	{
		count += TIMEMANAGER->getElapsedTime();
	}

	if (count > 1.0f)
	{
		_state = enemy_state::ATTACK;
		_hitBox = { _destination.left - 10, _destination.top - 10, _destination.left + 32, _destination.top + 32 };
		count = 0;
	}
	if (is_find && _state == enemy_state::IDLE)
	{
		_state = enemy_state::RUN;
	}
	else if (!is_find && _state == enemy_state::RUN)
	{
		_state = enemy_state::IDLE;
	}

}

void bat::render()
{
	enemy_img->FrameRender(_rc.left, _rc.top, _currentFrameX, _currentFrameY);
}

void bat::move()
{
	float enemy_x = (_rc.left + _rc.right) / 2;
	float enemy_y = (_rc.top + _rc.bottom) / 2;

	float dest_x = (_destination.left + _destination.right) / 2;
	float dest_y = (_destination.top + _destination.bottom) / 2;

	float angle = getAngle(enemy_x, enemy_y, dest_x, dest_y);

	if (!is_arrived)
	{
		_rc.left += _speed * cosf(angle)* TIMEMANAGER->getElapsedTime() * 60;
		_rc.right = _rc.left + _width;

		_rc.top += RND->getFromFloatTo(0.0f, 2.0f) * -sinf(angle)* TIMEMANAGER->getElapsedTime() * 60;
		_rc.bottom = _rc.top + _height;
	}

}

void bat::attack()
{
	_state = enemy_state::RUN;
	is_arrived = false;
}

void bat::idle()
{
	idle_count += TIMEMANAGER->getElapsedTime();

	if (idle_count > 5.0f)
	{
		_angle = RND->getFromFloatTo(-PI * 2, PI * 2);
		update_direction();
		_state = enemy_state::IDLE_RUN;
		idle_count = 0;
	}
}

void bat::idle_run()
{
	idle_count += TIMEMANAGER->getElapsedTime();

	_rc.left += _speed * 0.5 * cosf(_angle)* TIMEMANAGER->getElapsedTime() * 60;
	_rc.right = _rc.left + _width;

	_rc.top += RND->getFromFloatTo(0.0f, 2.0f) * -sinf(_angle)* TIMEMANAGER->getElapsedTime() * 60;
	_rc.bottom = _rc.top + _height;

	if (idle_count > 0.5f)
	{
		_state = enemy_state::IDLE;
		idle_count = 0;
	}
}

void bat::state_action()
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

void bat::update_direction()
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
