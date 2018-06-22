#pragma once
#include<cocos2d.h>
#include"Player.h"
#include"Welcome.h"
#include"HUDLayer.h"

USING_NS_CC;

class MainGame:public Layer
{
public:
	Player * player = nullptr;

	MainGame();
	~MainGame();

	

	static Scene* createScene();

	void tick(float dt);

	void moveBG(float dt);

	void initEnemy(float dt);

	void initEnemy();

	void enemyMove(float what);

	void enemyShoot(Sprite*,float);

	void delteEnenyRocket(Sprite* what);

	void deltePlayerRocket(Sprite* what);

	void PlayerShoot();

	void RP();

	void RE();

	virtual bool init();

	void CBback(Ref * pSender);

	CREATE_FUNC(MainGame);

	static HUDLayer * hudLayer;

	static HUDLayer * getHudLayer();
	
	static void keepHudLayer(HUDLayer* theHUD);

protected:
	static Label* gameOverLabel;

	bool isHoldPlayer=false;

	
	

	Sprite * bg1, * bg2;

	Size size = Director::getInstance()->getVisibleSize();

	

	Vector <Sprite*> enemies;

	Vector<Sprite*> PlayerRockets;

	Vector<Sprite*> EnemyRockets;

	float timePassed;

	float playerRocketSpeed=500.0;

	float enemySpeedX = 200.0;

	float enemyShootTimer = 0;

	const float enemyShootPace = 0.4f;//test change!!!!!!!!!!!!!!!!!!!!

	const float enemyRocketSpeed = 200.0f;

	bool isDead = false;

	
};

