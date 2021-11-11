#pragma once
#include "gameNode.h"
#include <vector>

struct tagBullet
{
	image* bulletImage;		//총알 이미지 
	D2D1_RECT_F rc;				//총알 렉트
	float x, y;				//총알 좌표(실시간)
	float angle;			//총알 각도
	float interval, interval2;			//총알 반지름
	float speed;			//총알 스피드
	float width;
	float height;
	float jump_power;
	float gravity;
	float opacity;
	float fireX, fireY;		//총알 발사시 처음 좌표(발사된 좌표)
	bool isFire;			//발사됐누?
	bool isGround;
	bool is_hit;
	int count;				//총알 프레임카운트용
	int direction;
	int durability;
};

/******************************************* 에너미 불렛 *****************************************************/
class hitBox : public gameNode
{
private:
	vector<tagBullet>			_vBullet;
	vector<tagBullet>::iterator _viBullet;

	const char* _imageName;

public:
	hitBox() {};
	~hitBox() {};

	HRESULT init();
	void release();
	void update();
	void render();

	void fire(float x, float y, float width, float height);

	void move();

	//총알을 지워달라고 소통하는 함수
	void removeBullet(int arrNum);


	vector<tagBullet> getVBullet() { return _vBullet; }
	vector<tagBullet>::iterator getViBullet() { return _viBullet; }

};


/**************************************** 양이나 갑옷 터질때 조각나는것들 *******************************************************/

class fragment : public gameNode
{
private:
	vector<tagBullet>			_vBullet;
	vector<tagBullet>::iterator _viBullet;

	float _range;
	int _bulletMax;

public:
	fragment() {};
	~fragment() {};

	HRESULT init(int bulletMax, float range);
	void release();
	void update();
	void render();

	//총알 발사함수(생성될 좌표)
	void fire(LPCWSTR filename, float x, float y, float width, float height, int _direction);

	//총알 움직여줍시다
	void move();
	void removeMissile(int arrNum);
	void set_rect(int num, float val);
	void set_gravity(int num);
	void set_direction(int num);

	vector<tagBullet> get_bullet() { return _vBullet; }
	vector<tagBullet>::iterator get_VI_bullet() { return _viBullet; }
};

/**************************************** 레인저 화살  *******************************************************/

class Player_bullet : public gameNode
{
private:
	vector<tagBullet>			_vBullet;
	vector<tagBullet>::iterator _viBullet;

	const char* _imageName;
	float _range;
	int _bulletMax;

public:
	Player_bullet() {};
	~Player_bullet() {};

	HRESULT init(float range);
	void release();
	void update();
	void render();

	void fire(LPCWSTR imagename, float x, float y, float width, float height, float angle, float speed);

	void move();

	//총알을 지워달라고 소통하는 함수
	void removeBullet(int arrNum);


	vector<tagBullet> getVBullet() { return _vBullet; }
	vector<tagBullet>::iterator getViBullet() { return _viBullet; }

};