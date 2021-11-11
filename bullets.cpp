#include "stdafx.h"
#include "bullets.h"

HRESULT hitBox::init()
{
	return S_OK;
}

void hitBox::release()
{
}

void hitBox::update()
{
	for (int i = 0; i < _vBullet.size(); i++)
	{
		_vBullet[i].interval += TIMEMANAGER->getElapsedTime();

		if (_vBullet[i].interval > 0.1f && &_vBullet[i] != NULL)
		{
			removeBullet(i);
		}
	}
}

void hitBox::render()
{
	for (int i = 0; i < _vBullet.size(); i++)
	{
		D2DMANAGER->Rectangle(_vBullet[i].rc);
	}
}

void hitBox::fire(float x, float y, float width, float height)
{
	tagBullet bullet;
	ZeroMemory(&bullet, sizeof(tagBullet));
	bullet.interval = 0;
	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;

	bullet.rc = D2DMANAGER->RectMake(bullet.x, bullet.y, width, height);

	_vBullet.push_back(bullet);

}

void hitBox::move()
{

}

void hitBox::removeBullet(int arrNum)
{
	//벡터의 값을 지울떈  erase()
	_vBullet.erase(_vBullet.begin() + arrNum);
}

/**************************************** 갑옷이나 양이 조각날때 사용하는 불렛 *******************************************************/

HRESULT fragment::init(int bulletMax, float range)
{
	_bulletMax = bulletMax;
	_range = range;

	return S_OK;
}

void fragment::release()
{
}

void fragment::update()
{
	move();
}

void fragment::render()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();)
	{
		// 렌더
		_viBullet->bulletImage->render(
			_viBullet->rc.left,
			_viBullet->rc.top,
			_viBullet->opacity);

		_viBullet->opacity -= 0.007f;

		if (_viBullet->opacity <= 0.0f)
		{
			_viBullet = _vBullet.erase(_viBullet);
		}
		else
			_viBullet++;
	}
}

void fragment::fire(LPCWSTR filename, float x, float y, float width, float height, int _direction)
{
	//최대갯수보다 더 생성되려고 하면 하지않는다
	if (_bulletMax < _vBullet.size()) return;

	tagBullet bullet;
	ZeroMemory(&bullet, sizeof(tagBullet));
	bullet.bulletImage = new image;
	bullet.bulletImage->D_Init(filename, width, height);
	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;
	bullet.speed = 3.0f;
	bullet.opacity = 1.0f;
	bullet.rc = D2DMANAGER->RectMake(bullet.x, bullet.y,
		bullet.bulletImage->getWidth(),
		bullet.bulletImage->getHeight());
	bullet.width = bullet.rc.right - bullet.rc.left;
	bullet.height = bullet.rc.bottom - bullet.rc.top;
	bullet.direction = _direction;

	bullet.jump_power = RND->getFromFloatTo(0.0f, 6.0f);
	bullet.gravity = 0.2f;

	_vBullet.push_back(bullet);
}

void fragment::move()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); _viBullet++)
	{
		_viBullet->x += _viBullet->speed * _viBullet->direction;
		_viBullet->y -= _viBullet->jump_power - _viBullet->gravity;

		_viBullet->gravity += 0.2f;

		_viBullet->rc = D2DMANAGER->RectMakeCenter(_viBullet->x, _viBullet->y,
			_viBullet->bulletImage->getWidth(),
			_viBullet->bulletImage->getHeight());
	}
}

void fragment::removeMissile(int arrNum)
{
	_vBullet[arrNum].bulletImage->release();
	_vBullet.erase(_vBullet.begin() + arrNum);
}

void fragment::set_rect(int num, float val)
{
	_vBullet[num].rc.bottom = val;
	_vBullet[num].rc.top = _vBullet[num].rc.bottom - _vBullet[num].height;
}

void fragment::set_gravity(int num)
{
	_vBullet[num].gravity = 0.0f;
	_vBullet[num].speed = 0.0f;
	_vBullet[num].jump_power = 0.0f;
}

void fragment::set_direction(int num)
{
	_vBullet[num].direction = _vBullet[num].direction * -1;
}

/**************************************** 레인저 화살 *******************************************************/

HRESULT Player_bullet::init(float range)
{
	_range = range;

	return S_OK;
}

void Player_bullet::release()
{
}

void Player_bullet::update()
{
	move();
}

void Player_bullet::render()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); _viBullet++)
	{
		_viBullet->bulletImage->rotation_start(_viBullet->rc.left, _viBullet->rc.top, -_viBullet->angle * 180/PI);
		_viBullet->bulletImage->render(_viBullet->rc.left, _viBullet->rc.top);
		_viBullet->bulletImage->rotation_end();

		//D2DMANAGER->Rectangle(_viBullet->rc);
	}
}

void Player_bullet::fire(LPCWSTR imagename, float x, float y, float width, float height, float angle, float speed)
{
	tagBullet bullet;
	ZeroMemory(&bullet, sizeof(tagBullet));
	bullet.bulletImage = new image;
	bullet.bulletImage->D_Init(imagename, width, height);
	bullet.speed = speed;
	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;
	bullet.angle = angle;
	
	bullet.rc = D2DMANAGER->RectMakeCenter(bullet.x, bullet.y,
		bullet.bulletImage->getWidth(),
		bullet.bulletImage->getHeight());

	_vBullet.push_back(bullet);
}

void Player_bullet::move()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();)
	{
		_viBullet->x += cosf(_viBullet->angle) * _viBullet->speed;
		_viBullet->y += -sinf(_viBullet->angle) * _viBullet->speed;

		_viBullet->rc = D2DMANAGER->RectMakeCenter(_viBullet->x, _viBullet->y,
			_viBullet->bulletImage->getWidth(),
			_viBullet->bulletImage->getHeight());

		if (_range < getDistance(_viBullet->x, _viBullet->y, _viBullet->fireX, _viBullet->fireY))
		{
			_viBullet = _vBullet.erase(_viBullet);
		}
		else ++_viBullet;
	}
}

void Player_bullet::removeBullet(int arrNum)
{
	_vBullet[arrNum].bulletImage->release();
	_vBullet.erase(_vBullet.begin() + arrNum);
}
