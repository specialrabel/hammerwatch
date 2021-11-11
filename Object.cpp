#include "stdafx.h"
#include "Object.h"

HRESULT Object::init()
{
	_arrow = new Arrow;
	IMAGEMANAGER->addFrameImage("branch", L"image/treetrap.png", 53, 90, 1, 6);

	return S_OK;
}

void Object::update()
{
	for (int i = 0; i < object.size(); i++)
	{
		if (object[i].type != object_type::BRANCH) continue;

		if (object[i].is_touched)
		{
			object[i].count++;
		}

		if (object[i].is_broken && object[i].count > 60)
		{
			object[i].count = 1;
			object[i].is_broken = false;
			object[i].is_touched = false;
			object[i].width = object[i].img->getFrameWidth();
			object[i].height = object[i].img->getFrameHeight();
			object[i].rc = D2DMANAGER->RectMake(object[i].rc.left, object[i].rc.top, object[i].width, object[i].height);

			object[i]._currentFrameY = 0;
		}

		if (object[i].count % 5 == 0 && !object[i].is_broken)
		{
			object[i]._currentFrameY += 1;
			object[i].img->setFrameY(object[i]._currentFrameY);
			
			if (object[i]._currentFrameY > object[i].img->getMaxFrameY())
			{
				object[i]._currentFrameY = 0;
				object[i].is_broken = true;
				object[i].count = 0;
				object[i].width = 0;
				object[i].height = 0;
				object[i].rc = D2DMANAGER->RectMake(object[i].rc.left, object[i].rc.top, object[i].width, object[i].height);
			}
		}
	}

	
	if (KEYMANAGER->isOnceKeyDown(VK_F1))
	{
		_arrow->fire();
	}
	
	_arrow->update();
}

void Object::render()
{
	for (int i = 0; i < object.size(); i++)
	{
		if (object[i].is_broken) continue;
		if (object[i].type != object_type::BRANCH) continue;

		if (object[i].reverse)
		{
			object[i].img->scale_start(object[i].rc.left, object[i].rc.top, -1.0f, 1.0f);
			object[i].img->FrameRender(object[i].rc.left, object[i].rc.top, object[i]._currentFrameX, object[i]._currentFrameY);
			object[i].img->scale_end();
		}
		else
			object[i].img->FrameRender(object[i].rc.left, object[i].rc.top, object[i]._currentFrameX, object[i]._currentFrameY);

		//D2DMANAGER->Rectangle(object[i].rc);
	}

	for (int i = 0; i < object.size(); i++)
	{
		if (object[i].type != object_type::GATE) continue;

		object[i].img->render(object[i].rc.left, object[i].rc.top);
	}

	_arrow->render();
}

void Object::set_is_touched(int num)
{
	object[num].is_touched = true;
}

void Object::set_branch(float destX, float destY, bool reverse)
{
	object_info obj;
	ZeroMemory(&obj, sizeof(obj));
	obj.img = new image;
	obj.img->D_Init(L"image/treetrap.png", 53, 90, 1, 6);
	obj.x = destX;
	obj.y = destY;
	obj.width = obj.img->getFrameWidth();
	obj.height = obj.img->getFrameHeight();
	obj.is_touched = false;
	obj.is_broken = false;
	obj.reverse = reverse;
	obj.count = 1;
	obj.type = object_type::BRANCH;
	obj._currentFrameX = 0;
	obj._currentFrameY = 0;

	if (reverse)
	{
		obj.rc = D2DMANAGER->RectMake(obj.x, obj.y, obj.width, obj.height);
	}
	else
		obj.rc = D2DMANAGER->RectMake(obj.x - obj.width, obj.y, obj.width, obj.height);

	object.push_back(obj);
}

void Object::set_gate(float destX, float destY)
{
	object_info obj;
	ZeroMemory(&obj, sizeof(obj));
	obj.img = new image;
	obj.img->D_Init(L"image/gate.png", 14, 88);
	obj.x = destX;
	obj.y = destY;
	obj.width = obj.img->getWidth();
	obj.height = obj.img->getHeight();
	obj.is_touched = false;
	obj.is_broken = false;
	obj.type = object_type::GATE;

	obj.rc = D2DMANAGER->RectMake(obj.x, obj.y, obj.width, obj.height);

	object.push_back(obj);
}

void Object::set_arrow(float destX, float destY, int direction, bool reverse)
{
	_arrow->init(destX, destY, direction, reverse);
}

void Object::remove_object(int num)
{
	object.erase(object.begin() + num);
}
