#pragma once
class npcNode
{


public:
	virtual HRESULT init();			//초기화 함수
	virtual void release();			//메모리 해제 함수
	virtual void update();			//연산 함수
	virtual void render();			//그리기 함수
	virtual void renderInteraction();		//상호작용시 랜더링

	virtual bool getInteraction();
	virtual void setInteraction(bool b);
	virtual int getNpcLevel();
	virtual void setChat(bool b);

};

