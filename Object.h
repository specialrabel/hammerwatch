#pragma once
#include "gameNode.h"
#include "bullets.h"

enum class object_type
{
	BRANCH,
	GATE,
	ARROW,

	type_num
};

struct object_info
{
	image* img;
	D2D1_RECT_F rc;
	object_type type;
	float width;
	float height;
	float x, y;
	int count;
	int _currentFrameX;
	int _currentFrameY;
	bool is_touched;
	bool is_broken;
	bool reverse;
};

class Object
{
private:
	vector<object_info> object;
	Arrow* _arrow;

public:
	Object(){};
	~Object(){};

	virtual HRESULT init();
	virtual void update();
	virtual void render();

	void set_is_touched(int num);
	void set_branch(float destX, float destY, bool reverse);
	void set_gate(float destX, float destY);
	void set_arrow(float destX, float destY, int direction, bool reverse);
	void remove_object(int num);

	vector<object_info> get_object() { return object; }
	Arrow* get_arrow(){ return _arrow; }

};

