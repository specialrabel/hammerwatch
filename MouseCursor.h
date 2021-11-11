#pragma once
#include "Ui.h"
#include "player.h"

class MouseCursor
{
private:
	Ui* _ui;
	player* _pl;
	image* _cursor;
	
	UINT iMsg;

	float _currentX;
	float _currentY;

	bool _isMoveX;
	bool _isMoveY;

	float cam_x;
	float cam_y;

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void setUiMemoryAdressLink(Ui* ui) { _ui = ui; }
	void setPlayerMemoryAdressLink(player* pl) { _pl = pl; }
};

