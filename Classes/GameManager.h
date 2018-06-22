#pragma once
#include<cocos2d.h>
#include<Welcome.h>
USING_NS_CC;

class GameManager
{
public:
	GameManager();
	~GameManager();

	static GameManager* getInstance();

	Scene *createMainScene();

	void start();


protected:
	static GameManager* thisManager;

};

