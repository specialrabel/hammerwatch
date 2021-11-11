#pragma once
#include <vector>

typedef void(*CALLBACK_FUNCTION)(void);
typedef void(*CALLBACK_FUNCTION_PARAMETER)(void*);

//���̵� ������
//����ִ� ���� ����Ų��? -> �����̵� �� ����ų���ִ�
//�ٸ� ���� ����Ų ���� �������� ���� �����ؾ� ��밡��

class animation
{
public:
	//������ ����Ʈ
	typedef vector<POINT> _vFrameList;

	//������
	typedef vector<int> _vPlayList;

private:
	int			_frameNum;			//������ ����

	_vFrameList _frameList;
	_vPlayList	_playList;

	int			_frameWidth;		
	int			_frameHeight;

	float		_frameUpdateSec;	//������ ������Ʈ
	float		_elapsedSec;		//ƽ

	DWORD		_nowPlayIdx;		//���� �÷��� �ε���
	BOOL		_play;				//��� ����
	BOOL		_loop;
	BOOL		_end;

	void*						_obj;
	CALLBACK_FUNCTION			_callbackFunction;
	CALLBACK_FUNCTION_PARAMETER _callbackFunctionParameter;

public:
	animation();
	~animation();

	HRESULT init(int totalW, int totalH, int frameW, int frameH);
	void release();

	//����Ʈ �ִϸ��̼� ���
	void setDefPlayFrame(BOOL reverse = FALSE, BOOL loop = FALSE );
	void setDefPlayFrame(BOOL reverse, BOOL loop, CALLBACK_FUNCTION cbFunction);
	void setDefPlayFrame(BOOL reverse, BOOL loop, CALLBACK_FUNCTION_PARAMETER cbFunction, void* obj);
	
	//�迭�� ��Ƽ� �ִϸ��̼� ���
	void setPlayFrame(int* playArr, int arrLen, BOOL loop = FALSE);
	void setPlayFrame(int* playArr, int arrLen, BOOL loop, CALLBACK_FUNCTION cbFunction);
	void setPlayFrame(int* playArr, int arrLen, BOOL loop, CALLBACK_FUNCTION_PARAMETER cbFunction, void* obj);
		
	//���� �ִϸ��̼� ���
	void setPlayFrame(int start, int end, BOOL reverse = FALSE, BOOL loop = false);
	void setPlayFrame(int start, int end, BOOL reverse, BOOL loop, CALLBACK_FUNCTION cbFunction);
	void setPlayFrame(int start, int end, BOOL reverse, BOOL loop, CALLBACK_FUNCTION_PARAMETER cbFunction, void* obj);

	void setFPS(int framePerSec);

	void frameUpdate(float elapsedTime);

	void start();
	void stop();
	void pause();
	void resume();
	bool isCheck(int num);

	inline BOOL isPlay() { return _play; }
	inline BOOL isEnd() { return _end; }

	inline POINT getFramePos() { return _frameList[_playList[_nowPlayIdx]]; }

	inline int getFrameWidth() { return _frameWidth; }
	inline int getFrameHeight() { return _frameHeight; }

};
