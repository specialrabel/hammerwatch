#pragma once
#include "enemy.h"

class bat : public enemy
{
private:
	bool is_done;
	float count;

	float idle_count;

public:

	virtual HRESULT init(float x, float y);

	virtual void release();
	virtual void update();
	virtual void render();

	virtual void move();
	virtual void attack();
	virtual void idle();
	virtual void idle_run();

	virtual void state_action();
	virtual void update_direction();
};

