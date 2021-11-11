#include "stdafx.h"
#include "player.h"

void player::key_setting_idle()
{
	if (KEYMANAGER->isOnceKeyDown('A'))
	{
		_player.state = Player_State::RUN;
		animation_setting();
	}

	if (KEYMANAGER->isOnceKeyDown('W'))
	{
		_player.state = Player_State::RUN;
		animation_setting();
	}

	if (KEYMANAGER->isOnceKeyDown('D'))
	{
		_player.state = Player_State::RUN;
		animation_setting();
	}

	if (KEYMANAGER->isOnceKeyDown('S'))
	{
		_player.state = Player_State::RUN;
		animation_setting();
	}

	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON) && action_done)
	{
		_player.state = Player_State::ATTACK;
		animation_setting();
		action_done = false;
	}

	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON) && action_done)
	{
		_player.state = Player_State::SKILL;
		animation_setting();
		
		_player.start_xPos = _player.x;
		_player.start_yPos = _player.y;
		action_done = false;
	}
}

void player::key_setting_run()
{
	float speed = _status.move_speed * TIMEMANAGER->getElapsedTime() * 60;

	if (KEYMANAGER->isOnceKeyUp('A'))
	{
		current_direction[(int)Player_Direction::LEFT] = false;
	}

	if (KEYMANAGER->isOnceKeyUp('D'))
	{
		current_direction[(int)Player_Direction::RIGHT] = false;
	}

	if (KEYMANAGER->isOnceKeyUp('W'))
	{
		current_direction[(int)Player_Direction::TOP] = false;
	}

	if (KEYMANAGER->isOnceKeyUp('S'))
	{
		current_direction[(int)Player_Direction::BOTTOM] = false;
	}
	
	if (KEYMANAGER->isStayKeyDown('W'))
	{
		_player.y -= speed;
		_player.rc = D2DMANAGER->RectMakeCenter(_player.x, _player.y, _player.width, _player.height);
		_player.moving_direction = Player_Direction::TOP;
		current_direction[(int)Player_Direction::TOP] = true;
	}

	if (KEYMANAGER->isStayKeyDown('S'))
	{
		_player.y += speed;
		_player.rc = D2DMANAGER->RectMakeCenter(_player.x, _player.y, _player.width, _player.height);
		_player.moving_direction = Player_Direction::BOTTOM;
		current_direction[(int)Player_Direction::BOTTOM] = true;
	}

	if (KEYMANAGER->isStayKeyDown('A'))
	{
		_player.x -= speed;
		_player.rc = D2DMANAGER->RectMakeCenter(_player.x, _player.y, _player.width, _player.height);
		_player.moving_direction = Player_Direction::LEFT;
		current_direction[(int)Player_Direction::LEFT] = true;
	}

	if (KEYMANAGER->isStayKeyDown('D'))
	{
		_player.x += speed;
		_player.rc = D2DMANAGER->RectMakeCenter(_player.x, _player.y, _player.width, _player.height);
		_player.moving_direction = Player_Direction::RIGHT;
		current_direction[(int)Player_Direction::RIGHT] = true;
	}

	if (current_direction[(int)Player_Direction::LEFT] == true && current_direction[(int)Player_Direction::TOP] == true)
	{
		_player.moving_direction = Player_Direction::LEFT_TOP;
	}
	if (current_direction[(int)Player_Direction::LEFT] == true && current_direction[(int)Player_Direction::BOTTOM] == true)
	{
		_player.moving_direction = Player_Direction::LEFT_BOTTOM;
	}
	if (current_direction[(int)Player_Direction::RIGHT] == true && current_direction[(int)Player_Direction::TOP] == true)
	{
		_player.moving_direction = Player_Direction::RIGHT_TOP;
	}
	if (current_direction[(int)Player_Direction::RIGHT] == true && current_direction[(int)Player_Direction::BOTTOM] == true)
	{
		_player.moving_direction = Player_Direction::RIGHT_BOTTOM;
	}

	if (current_direction[(int)Player_Direction::LEFT] == false && current_direction[(int)Player_Direction::TOP] == false &&
		current_direction[(int)Player_Direction::RIGHT] == false && current_direction[(int)Player_Direction::BOTTOM] == false)
	{
		_player.state = Player_State::IDLE;
		animation_setting();
	}

	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON) && action_done)
	{
		_player.state = Player_State::ATTACK;
		animation_setting();
		action_done = false;
	}

	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON) && action_done)
	{
		_player.state = Player_State::SKILL;
		animation_setting();

		_player.start_xPos = _player.x;
		_player.start_yPos = _player.y;
		action_done = false;
	}
}

void player::key_setting_attack()
{
	float speed = _status.move_speed * TIMEMANAGER->getElapsedTime() * 60;

	if (action_done && _status.player_class == Player_Class::Paladin)
	{
		if (KEYMANAGER->isStayKeyDown('W'))
		{
			_player.y -= speed * 2.5;
			_player.rc = D2DMANAGER->RectMakeCenter(_player.x, _player.y, _player.width, _player.height);
			_player.moving_direction = Player_Direction::TOP;
			current_direction[(int)Player_Direction::TOP] == true;
		}

		if (KEYMANAGER->isStayKeyDown('S'))
		{
			_player.y += speed * 2.5;
			_player.rc = D2DMANAGER->RectMakeCenter(_player.x, _player.y, _player.width, _player.height);
			_player.moving_direction = Player_Direction::BOTTOM;
			current_direction[(int)Player_Direction::BOTTOM] == true;
		}

		if (KEYMANAGER->isStayKeyDown('A'))
		{
			_player.x -= speed * 2.5;
			_player.rc = D2DMANAGER->RectMakeCenter(_player.x, _player.y, _player.width, _player.height);
			_player.moving_direction = Player_Direction::LEFT;
			current_direction[(int)Player_Direction::LEFT] == true;
		}

		if (KEYMANAGER->isStayKeyDown('D'))
		{
			_player.x += speed * 2.5;
			_player.rc = D2DMANAGER->RectMakeCenter(_player.x, _player.y, _player.width, _player.height);
			_player.moving_direction = Player_Direction::RIGHT;
			current_direction[(int)Player_Direction::RIGHT] == true;
		}
	}

	if (_status.player_class == Player_Class::Ranger)
	{
		if (KEYMANAGER->isStayKeyDown('W'))
		{
			_player.y -= speed * 0.5;
			_player.rc = D2DMANAGER->RectMakeCenter(_player.x, _player.y, _player.width, _player.height);
			_player.moving_direction = Player_Direction::TOP;
			current_direction[(int)Player_Direction::TOP] == true;
		}

		if (KEYMANAGER->isStayKeyDown('S'))
		{
			_player.y += speed * 0.5;
			_player.rc = D2DMANAGER->RectMakeCenter(_player.x, _player.y, _player.width, _player.height);
			_player.moving_direction = Player_Direction::BOTTOM;
			current_direction[(int)Player_Direction::BOTTOM] == true;
		}

		if (KEYMANAGER->isStayKeyDown('A'))
		{
			_player.x -= speed * 0.5;
			_player.rc = D2DMANAGER->RectMakeCenter(_player.x, _player.y, _player.width, _player.height);
			_player.moving_direction = Player_Direction::LEFT;
			current_direction[(int)Player_Direction::LEFT] == true;
		}

		if (KEYMANAGER->isStayKeyDown('D'))
		{
			_player.x += speed * 0.5;
			_player.rc = D2DMANAGER->RectMakeCenter(_player.x, _player.y, _player.width, _player.height);
			_player.moving_direction = Player_Direction::RIGHT;
			current_direction[(int)Player_Direction::RIGHT] == true;
		}
	}

	if (current_direction[(int)Player_Direction::LEFT] == true && current_direction[(int)Player_Direction::TOP] == true)
	{
		_player.moving_direction = Player_Direction::LEFT_TOP;
	}
	if (current_direction[(int)Player_Direction::LEFT] == true && current_direction[(int)Player_Direction::BOTTOM] == true)
	{
		_player.moving_direction = Player_Direction::LEFT_BOTTOM;
	}
	if (current_direction[(int)Player_Direction::RIGHT] == true && current_direction[(int)Player_Direction::TOP] == true)
	{
		_player.moving_direction = Player_Direction::RIGHT_TOP;
	}
	if (current_direction[(int)Player_Direction::RIGHT] == true && current_direction[(int)Player_Direction::BOTTOM] == true)
	{
		_player.moving_direction = Player_Direction::RIGHT_BOTTOM;
	}

	if (KEYMANAGER->isOnceKeyUp('A'))
	{
		current_direction[(int)Player_Direction::LEFT] = false;
	}

	if (KEYMANAGER->isOnceKeyUp('D'))
	{
		current_direction[(int)Player_Direction::RIGHT] = false;
	}

	if (KEYMANAGER->isOnceKeyUp('W'))
	{
		current_direction[(int)Player_Direction::TOP] = false;
	}

	if (KEYMANAGER->isOnceKeyUp('S'))
	{
		current_direction[(int)Player_Direction::BOTTOM] = false;
	}

	if (action_done)
	{
		//rotation_mat = { 0, 0, 0, 0, 0, 0};
		_player.state = Player_State::RUN;
		animation_setting();
	}
}

void player::key_setting_skill()
{
	switch (_status.player_class)
	{
	case Player_Class::Paladin:
		skillAction_paladin();
		break;

	case Player_Class::Ranger:
		skillAction_ranger();
		break;
	}
}
