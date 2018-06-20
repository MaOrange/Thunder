#pragma once
#include<cocos2d.h>
#include<GameManager.h>
#include"MainGame.h"
#include"Player.h"

USING_NS_CC;


class Welcome:public Layer
{
public:
	Welcome();
	~Welcome();

	CREATE_FUNC(Welcome);

	virtual bool init();

	void start();

	void setting();

	static void gotoWelcome();

	//static void gotoWelcome(Ref*);


protected:
	void menuCB(Ref* what);

};

