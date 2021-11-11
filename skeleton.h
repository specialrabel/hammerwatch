#pragma once
#include "enemy.h"


class skeleton : public enemy
{
private:
	bool is_done;
	float count;
	float acition_count;
	float idle_count;

	enemy_direction past_direction;

public:

	virtual HRESULT init(float x, float y);

	virtual void release();
	virtual void update();
	virtual void render();

	virtual void idle();
	virtual void idle_run();
	virtual void move();
	virtual void attack();

	virtual void state_action();
	virtual void update_direction();

	void animation_init();
	void animation_setting();
};

