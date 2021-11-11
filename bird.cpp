#include "stdafx.h"
#include "bird.h"
#include "Player.h"

HRESULT bird::init()
{
	//변수 초기화
	_x = _y = 0;
	_birdX = 100;
	_birdY = 100;
	_oldBirdX = _angle = 0;
	_indexX = _indexY = _frameTime = 0;
	_moveValue = _moveStop = false;
	_moveSpeed = DfBirdMoveSpeed;
	_oldAngle = _angle = 0;
	_tickTime = 0;
	_up = _down = 0;

	//발사 새 변수 초기화
	_eggHaving = 0;
	_shotTimer = 0;

	//이미지 등록
	_birdImage = new image;
	_birdImage->D_Init(L"image\\Bird\\inventoryBird(384x256).png", 384, 256, 6, 4);
	_bulletBirdImage = new image;
	_bulletBirdImage->D_Init(L"image\\Bird\\bulletBird(512x512).png", 512, 512, 8, 8);
	_eggImage = new image;
	_eggImage->D_Init(L"image\\Bird\\egg(60x32).png", 60, 32, 5, 2);
	//효과 이미지
	EFFECTMANAGER->addEffect("birdE", "image\\Bird\\etc_costem(256x64).png", 256, 64, 4, 1, 10, 0, 0);

	//테스트 용
	_debugMod = false;
	_eggHaving = 11;

	return S_OK;
}

void bird::release()
{

}

void bird::update()
{
	//새알 사용 쿨타임
	if (!_bulletBirdShot) 	_shotTimer++;
	if (_shotTimer == 60)
	{
		_shotTimer = 0;
		_bulletBirdShot = true;
	}

	birdMove();

	//임시 새알 발사 입력시 동작
	if (KEYMANAGER->isOnceKeyDown('W') && _bulletBirdShot)
	{

		if (_eggHaving > 0)
		{
			makeBulletBird();
			_eggHaving--;
		}

		_bulletBirdShot = false;
	}

	bulletBirdMove();


	if (KEYMANAGER->isOnceKeyDown('P'))
	{
		_debugMod ^= 1;
	}

}

void bird::render()
{

	//디버깅용 텍스트
	/*WCHAR str[128];
	swprintf_s(str, L"XYdata : %.1f | %.1f | %.1f | %.1f | ", _x, _y, _birdX, _birdY);
	D2DMANAGER->DrawTextD2D(D2DMANAGER->defaultBrush, L"나눔고딕", 17.0f, str, _x, _y,
		_x+200, _y+20);
	swprintf_s(str, L"data :  %.1f | %.1f | %.1f | %d",
		 _traceX, _traceY, _traceAngle, _tickTime);
	D2DMANAGER->DrawTextD2D(D2DMANAGER->defaultBrush, L"나눔고딕", 17.0f, str, _x, _y +40,
		_x + 200, _y + 60);*/

	eggRender();
	birdRender();


	//총알 새 생성

	bulletBirdRender();




}

void bird::birdMove()
{

	_x = _player->getPlayerX();
	_y = _player->getPlayerY();


	//새의 이동 목표 정보 보정 필요시 활성화
	/*if ()
	{
		_x += 60;
		_y -= 10;
	}*/




	//플레이어와 새의 상대 거리 계산
	_valueX = _x - _birdX;
	_valueY = _y - _birdY;
	_distance = _valueX * _valueX + _valueY * _valueY;

	//새는 플레이어와 일정 거리가 떨어지면 이동
	if (_distance >= 12000)
	{
		_moveValue = true;
		_moveStop = false;
		_moveSpeed = DfBirdMoveSpeed;
	}

	// 이동 명령이 참이 되면 이동
	if (_moveValue)
	{
		_angle = -atan2f(_valueY, _valueX);

		//유도 각도 한계 설정
		/*_oldAngle = _angle;
		_angle = -atan2f(_valueY, _valueX);
		if (abs(_oldAngle - _angle) > 0.5)
		{
			if ((_oldAngle - _angle) > 0) _angle = _oldAngle - 0.45;
			else _angle = _oldAngle + 0.45;
		}*/

		_birdX = _birdX + cosf(_angle)*_moveSpeed;
		_birdY = _birdY - sinf(_angle)*_moveSpeed;
	}
	//플에이어와 거리가 가까워 지면 이동속도 조정
	if (_distance <= 3000)
	{
		_moveSpeed = _moveSpeed * 0.9;
		if (_moveSpeed < 1) _moveSpeed = 1;
	}
	//목표지점 근방에 다르면 멈춤 동작
	if (_distance <= 64 && _moveValue)
	{
		_moveValue = false;
		_moveStop = true;
		_oldAngle = _angle;
	}
	//멈출때 한바퀴 회전
	if (_moveStop)
	{
		_moveSpeed = 0.5;
		//회전 방향
		if (_oldAngle >= 0) _angle += 0.02;
		else _angle -= 0.02;
		//한바퀴 돌면 정지
		if (abs(_oldAngle - _angle) > PI * 2) _moveStop = false;

		_birdX = _birdX + cosf(_angle)*_moveSpeed;
		_birdY = _birdY - sinf(_angle)*_moveSpeed;
	}


	//새의 이동 방향 랜더링 설정
	if (_oldBirdX - _birdX > 0)	_indexY = RIGHT_bird;
	if (_oldBirdX - _birdX < 0)	_indexY = LEFT_bird;

	_oldBirdX = _birdX;

	//새 위아래 흔들림
	if (_tickTime >= 15)
	{
		_down = 0;
		_up -= 0.03;
		_birdY += _up;
	}
	else
	{
		_up = 0;
		_down += 0.03;
		_birdY += _down;
	}
	_tickTime++;
	if (_tickTime == 30) _tickTime = 0;
}

void bird::birdRender()
{

	//디버깅용
	if (_debugMod)
	{
		_birdRect = D2DMANAGER->RectMakeCenter(_birdX, _birdY, 20, 20);
		D2DMANAGER->Rectangle(_birdRect);
	}




	//프레임 인덱스 업데이트
	if (_frameTime == DfFrameTime)
	{
		_indexX++;
		_frameTime = 0;
	}
	//실제 새 랜더링
	_birdImage->FrameRender(_birdX - 30, _birdY - 30, _indexX, _indexY, 1);
	//인덱스 초기화
	if (_indexX == 5) _indexX = 0;
	_frameTime++;

}

void bird::bulletBirdMove()
{
	//새 총알 각자 동작
	for (int i = 0; i < 20; i++)
	{
		if (_bB[i].bulletBirdShot)
		{
			//타이머 동작
			_bB[i].timer++;
			//새를 중심으로 설정
			_bB[i].traceX = _birdX;
			_bB[i].traceY = _birdY;
			//새를 중심으로 회전
			_bB[i].traceX = _bB[i].traceX + _bB[i].traceAngle * 10 * cosf(_bB[i].traceAngle);
			_bB[i].traceY = _bB[i].traceY - _bB[i].traceAngle * 10 * sinf(_bB[i].traceAngle);
			//회전 방향 및 각 속도
			if (_bB[i].direction == LEFT_bird) _bB[i].traceAngle += 0.05;
			if (_bB[i].direction == RIGHT_bird) _bB[i].traceAngle -= 0.05;

			//일정 시간 경과시 파괴
			if (_bB[i].timer > 1000) _bB[i].bulletDestroy = true;

			//총알 새 파괴 시 동작
			if (_bB[i].bulletDestroy)
			{
				_bB[i].bulletBirdShot = false;
				_bB[i].bulletDestroy = false;

				EFFECTMANAGER->play("birdE", _bB[i].traceX, _bB[i].traceY);

			}
		}

	}
}

void bird::bulletBirdRender()
{


	for (int i = 0; i < 20; i++)
	{
		if (_bB[i].bulletBirdShot)
		{

			//충돌 처리용
			_bB[i].bulletBirdRect = D2DMANAGER->RectMakeCenter(_bB[i].traceX, _bB[i].traceY, 30, 30);
			//디버깅용
			if (_debugMod)
			{
				D2DMANAGER->Rectangle(_bB[i].bulletBirdRect);
			}


			//프레임 인덱스 업데이트
			if (_bB[i].bulletFrameTime == DfFrameTime)
			{
				_bB[i].bulletIndexX++;
				_bB[i].bulletFrameTime = 0;
			}

			//좌우 이동에 따른 좌우 변경
			if (_bB[i].traceX - _bB[i].oldTraceX > 0)
			{
				//실제 총알 새 랜더링
				_bulletBirdImage->FrameRender(_bB[i].traceX - 35, _bB[i].traceY - 35, _bB[i].bulletIndexX, _bB[i].bulletIndexY, 1);
			}
			else
			{
				_bulletBirdImage->Frame_scale_start(_bB[i].traceX - 25, _bB[i].traceY - 35, -1.0, 1.0);
				_bulletBirdImage->FrameRender(_bB[i].traceX - 25, _bB[i].traceY - 35, _bB[i].bulletIndexX, _bB[i].bulletIndexY, 1);
				_bulletBirdImage->scale_end();
			}

			//인덱스 초기화
			if (_bB[i].helmetColor == GREEN)
			{
				if (_bB[i].bulletIndexX == 5) _bB[i].bulletIndexX = 0;
			}
			if (_bB[i].helmetColor == GOLD || _bB[i].helmetColor == COLOREND)
			{
				if (_bB[i].bulletIndexX == 7) _bB[i].bulletIndexX = 0;
			}


			_bB[i].bulletFrameTime++;

			//좌우 이동 확인용
			_bB[i].oldTraceX = _bB[i].traceX;

		}
	}

}

void bird::makeBulletBird()
{

	_bB[_bBIndex].bulletBirdShot = true;
	_bB[_bBIndex].direction = _indexY;
	_bB[_bBIndex].timer = 0;
	_bB[_bBIndex].traceAngle = 0;
	_playerData = _player->getTagPlayer();
	_bB[_bBIndex].helmetColor = _playerData->helmet_color;

	switch (_bB[_bBIndex].helmetColor)
	{
	case GREEN: 		_bB[_bBIndex].bulletIndexY = 1;
		break;
	case GOLD:			_bB[_bBIndex].bulletIndexY = 5;
		break;
	case COLOREND:		_bB[_bBIndex].bulletIndexY = 6;
		break;
	}

	_bBIndex++;
	if (_bBIndex == 20) _bBIndex = 0;

}

void bird::eggRender()
{

	int k = _eggHaving / 3;
	int m = k;
	int n = _eggHaving % 3;

	int eggX = -12;

	//첫줄은 나머지
	for (int i = 0; i < n; i++)
	{
		int j = i % 3;

		if (_indexY == LEFT_bird)
		{
			_eggImage->FrameRender(_birdX - 2 + (j * 8), _birdY - 20 - (k * 8), 0, 0, 1);
		}
		else
		{
			_eggImage->FrameRender(_birdX - 2 + eggX + (j * 8), _birdY - 20 - (k * 8), 0, 0, 1);
		}
	}
	//아래는 모두 랜더
	for (int i = 0; i < k; i++)
	{
		for (int i = 0; i < 3; i++)
		{
			if (_indexY == LEFT_bird)
			{
				if (i == 0)	_eggImage->FrameRender(_birdX + 2, _birdY - 18 - (m * 8), 0, 0, 1);
				else		_eggImage->FrameRender(_birdX - 10 + (i * 8), _birdY - 13 - (m * 8), 0, 0, 1);
			}
			else
			{
				if (i == 0)	_eggImage->FrameRender(_birdX + 2 + eggX, _birdY - 18 - (m * 8), 0, 0, 1);
				else		_eggImage->FrameRender(_birdX - 10 + eggX + (i * 8), _birdY - 13 - (m * 8), 0, 0, 1);
			}
		}
		m--;
	}

}
