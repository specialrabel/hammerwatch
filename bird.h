#pragma once
#include "gameNode.h"
#include "item.h"

#define DfBirdMoveSpeed			3
#define DfFrameTime				5
#define DfPIHalf				PI/2
#define DfBulletMoveSpeed		5

class player;
struct PLAYER;

enum {
	LEFT_bird,
	RIGHT_bird,
	BAGGAGE_LEFT,
	BAGGAGE_RIGHT
};


class bird :
	public gameNode
{

private:
	//�÷��̾� ����
	player* _player;

	float _x, _y;

	PLAYER* _playerData;



	/*enum ITEMCOLOR
	{
		GREEN,
		GOLD,
		COLOREND
	};*/

	//�̹���
	image* _birdImage;
	int _frameTime;
	int _indexX, _indexY;

	//���� ��ġ
	float _birdX, _birdY;
	float _oldBirdX;
	float _angle, _oldAngle;
	float _moveSpeed;
	float _up, _down;
	int _eggHaving;
	image* _eggImage;

	D2D1_RECT_F _birdRect;

	//�� �߻�
	image* _bulletBirdImage;

	bool _bulletBirdShot;

	struct BulletBird
	{
		D2D1_RECT_F bulletBirdRect;
		bool bulletBirdShot;
		bool bulletDestroy;
		float traceX, traceY;
		float oldTraceX;
		float traceAngle;
		int direction;
		int timer;
		int bulletFrameTime;
		int bulletIndexX, bulletIndexY;
		int helmetColor;

	};

	BulletBird _bB[20];
	int _bBIndex;
	int _shotTimer;

	//���� ����
	float _valueX, _valueY;
	float _distance;
	bool _moveValue;
	bool _moveStop;
	int _tickTime;
	bool _debugMod;

public:

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
	////////////////////////////////

	void linkPlayerClass(player* player) { _player = player; }

	//�κ��丮 ��
	void birdMove();
	void birdRender();
	//�Ѿ� ��
	void bulletBirdMove();
	void bulletBirdRender();
	void makeBulletBird();

	//���
	void eggRender();

	D2D1_RECT_F getBirdRC(int index) { return _bB[index].bulletBirdRect; }
	bool getRcBirdShot(int index) { return _bB[index].bulletBirdShot; }
	void setBirdDistory(int index) { _bB[index].bulletDestroy = true; }

};

