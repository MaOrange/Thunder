#pragma once
#include<cocos2d.h>

USING_NS_CC;

class Player:public Sprite
{
public:
	Player();
	~Player();

	bool initSprite();

	static Player* createPlayer();

	static int life;

	static int score;

	static int getLife();

	static int getScore();		

	static void addScore(int plus);

	//CREATE_FUNC(Player);
	
	static void reinit();

};

