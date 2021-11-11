#pragma once
#include "gameNode.h"
#include <vector>

struct tagBullet
{
	image* bulletImage;		//�Ѿ� �̹��� 
	D2D1_RECT_F rc;				//�Ѿ� ��Ʈ
	float x, y;				//�Ѿ� ��ǥ(�ǽð�)
	float angle;			//�Ѿ� ����
	float interval, interval2;			//�Ѿ� ������
	float speed;			//�Ѿ� ���ǵ�
	float width;
	float height;
	float jump_power;
	float gravity;
	float opacity;
	float fireX, fireY;		//�Ѿ� �߻�� ó�� ��ǥ(�߻�� ��ǥ)
	bool isFire;			//�߻�ƴ�?
	bool isGround;
	bool is_hit;
	int count;				//�Ѿ� ������ī��Ʈ��
	int direction;
	int durability;
};

/******************************************* ���ʹ� �ҷ� *****************************************************/
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

	//�Ѿ��� �����޶�� �����ϴ� �Լ�
	void removeBullet(int arrNum);


	vector<tagBullet> getVBullet() { return _vBullet; }
	vector<tagBullet>::iterator getViBullet() { return _viBullet; }

};


/**************************************** ���̳� ���� ������ �������°͵� *******************************************************/

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

	//�Ѿ� �߻��Լ�(������ ��ǥ)
	void fire(LPCWSTR filename, float x, float y, float width, float height, int _direction);

	//�Ѿ� �������ݽô�
	void move();
	void removeMissile(int arrNum);
	void set_rect(int num, float val);
	void set_gravity(int num);
	void set_direction(int num);

	vector<tagBullet> get_bullet() { return _vBullet; }
	vector<tagBullet>::iterator get_VI_bullet() { return _viBullet; }
};

/**************************************** ������ ȭ��  *******************************************************/

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

	//�Ѿ��� �����޶�� �����ϴ� �Լ�
	void removeBullet(int arrNum);


	vector<tagBullet> getVBullet() { return _vBullet; }
	vector<tagBullet>::iterator getViBullet() { return _viBullet; }

};