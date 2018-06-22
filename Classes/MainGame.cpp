#pragma execution_character_set("utf-8")
#include"MainGame.h"
#include"SimpleAudioEngine.h"
#include"HUDLayer.h"
using namespace CocosDenshion;

//initialize static member to avoid BUG
//HUDLayer *MainGame::hudlayer = nullptr;
Label* MainGame::gameOverLabel=nullptr;



MainGame::MainGame()
{
}


MainGame::~MainGame()
{
}

Scene* MainGame::createScene()
{
	auto newScene = Scene::create();


	auto mainGame = MainGame::create();

	auto hudLayer = HUDLayer::create();

	newScene->addChild(hudLayer,4);

	newScene->addChild(mainGame,1);


	return newScene;
}

void MainGame::tick(float dt)
{
	PlayerShoot();
	enemyMove(dt);
	//rocker logic
	//rocket and player and enemy
	RP();
	RE();
	
}

void MainGame::moveBG(float dt)
{
	float dif = 4;

	bg1->setPosition(Vec2(bg1->getPosition().x,bg1->getPosition().y-dif));
	bg2->setPosition(Vec2(bg2->getPosition().x, bg2->getPosition().y - dif));

	if (bg1->getPosition().y<-size.height)
	{
		bg1->setPositionY (bg1->getPositionY() + 2*size.height);
	}

	if (bg2->getPosition().y<-size.height)
	{
		bg2->setPositionY(bg2->getPositionY() + 2*size.height);
	}


}

void MainGame::initEnemy(float dt)
{

	for (int i = 1; i <= 6; i++)
	{
		__String *s = __String::createWithFormat("e%d.png",i);
		auto enemy_frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(s->getCString());
		auto enemy = Sprite::createWithSpriteFrame(enemy_frame);
		enemy->setAnchorPoint(Vec2(0, 1));
		enemy->setPosition((CCRANDOM_0_1())*(size.width),size.height-40*i-50);
		enemies.pushBack(enemy);
		this->addChild(enemy);
	}
}

void MainGame::initEnemy()
{

	for (int i = 1; i <= 6; i++)
	{
		__String *s = __String::createWithFormat("e%d.png", i);
		auto enemy_frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(s->getCString());
		auto enemy = Sprite::createWithSpriteFrame(enemy_frame);
		enemy->setAnchorPoint(Vec2(0, 1));
		enemy->setPosition((CCRANDOM_0_1())*(size.width), size.height - 40 * i - 50);
		enemies.pushBack(enemy);
		this->addChild(enemy);
	}
}

void MainGame::enemyMove(float what)
{
	if (enemies.size() > 0)
	{
		int r = rand() % enemies.size();
		auto theEnemy = enemies.at(r);
		int x = theEnemy->getPositionX();
		int y = theEnemy->getPositionY();

		if (theEnemy->getNumberOfRunningActions() == 0)
		{
			/*int moveLength = CCRANDOM_0_1()*__min(size.width-x,x);

			auto enemyMove = MoveBy::create(2,Vec2(moveLength,0));

			auto reverseMove = enemyMove->reverse();

			auto seq =((CCRANDOM_0_1()>0.5) ? Sequence::create(enemyMove,reverseMove,NULL): Sequence::create(reverseMove,enemyMove, NULL));*/

			auto goal= Vec2(CCRANDOM_0_1()*size.width, y);

			float time = abs(goal.x-x)/ enemySpeedX;


			auto enemyMove = MoveTo::create(time,goal);

			auto seq = Sequence::create(enemyMove,NULL);

			theEnemy->runAction(seq);


		}
		enemyShoot(theEnemy, what);
	}
	else
	{
		scheduleOnce(CC_SCHEDULE_SELECTOR(MainGame::initEnemy), 0.8f);
	}
}

void MainGame::enemyShoot(Sprite * theE, float dt)
{
	enemyShootTimer += dt;
	float curPace=99999.0f;
	if (enemies.size() != 0)
	{
		 curPace = enemyShootPace / enemies.size();
	}
	else
	{
		return;
	}
	

	while (enemyShootTimer >= curPace)
	{
		int x = theE->getPositionX();
		int y = theE->getPositionY();

		enemyShootTimer =0;
		//shoot
		auto newRocket = Sprite::createWithSpriteFrameName("bullet2.png");
		//if (newRocket)CCLOG("new enemy rocket!!");
		newRocket->setPosition(Vec2(x,y));
		
		auto move = MoveTo::create((y+100)/ enemyRocketSpeed, Vec2(x,-10));

		auto cf = CallFunc::create(CC_CALLBACK_0(MainGame::delteEnenyRocket, this, newRocket));

		auto seq = Sequence::create(move,cf,NULL);

		this->addChild(newRocket, 3);

		newRocket->runAction(seq);

		EnemyRockets.pushBack(newRocket);

		


	}

}



void MainGame::delteEnenyRocket(Sprite * what)
{
	if (what->getPosition().y <0)
	{
		//CCLOG("remove Enemy rocket!!!");
		what->removeFromParentAndCleanup(true);
		EnemyRockets.eraseObject(what);
	}

}




void MainGame::deltePlayerRocket(Sprite * what)
{
	if (what->getPosition().y > size.height)
	{
		CCLOG("remove Player rocket!!!");
		what->removeFromParentAndCleanup(true);
		PlayerRockets.eraseObject(what);
	}
}

void MainGame::PlayerShoot()
{
	//audio
	if (isHoldPlayer&&!isDead)
	{
		SimpleAudioEngine::getInstance()->playEffect("playerfire.wav");
		//CCLOG("shoot!!!");



	//rocket animation
		auto playerRocket = Sprite::createWithSpriteFrameName("bullet1.png");

		float x = player->getPositionX();
		float y = player->getPositionY();
		playerRocket->setPosition(Vec2(x, y));

		this->addChild(playerRocket, 4);


		//disable player shoot
		PlayerRockets.pushBack(playerRocket);

		//find time rocket should fly
		float deltaT = (size.height - playerRocket->getPositionY()) / (playerRocketSpeed);

		//create move and destroy and then bind them together
		auto move = MoveTo::create(deltaT, Vec2(x, size.height + 5));

		auto cf = CallFunc::create(CC_CALLBACK_0(MainGame::deltePlayerRocket, this, playerRocket));

		auto seq = Sequence::create(move, cf, NULL);

		playerRocket->runAction(seq);
		//create a seq containing the fly and destory action and then run the seq action



		
	}

}

void MainGame::RP()
{
	if (EnemyRockets.size() > 0)
	{
		Vector<Sprite*> *tempVector = new Vector<Sprite*>();

		for (auto er:EnemyRockets)
		{
			if (player->getBoundingBox().intersectsRect(er->getBoundingBox()))
			{
				//player hit!!
				tempVector->pushBack(er);
				//
				SimpleAudioEngine::getInstance()->playEffect("explod01.wav");
				CCLOG("player hit!!! life:%d", Player::getLife());
				//logic
				player->life--;

				
				//j
				if (player->life <= 0)
				{
					gameOverLabel->setVisible(true);
					isDead = true;
				}
			}
		}


		for (int i=0;i<=tempVector->size()-1;i++)
		{
			Sprite* temp;
			temp = tempVector->at(i);
			EnemyRockets.eraseObject(temp);
			temp->removeFromParentAndCleanup(true);

		}
		delete tempVector;
	}


}

void MainGame::RE()
{
	if (enemies.size() > 0)
	{
		Vector<Sprite*> *tempEnemies = new Vector<Sprite*>();
		for (auto e : enemies)
		{
			for (auto pb : PlayerRockets)
			{
				if (e->getBoundingBox().intersectsRect(pb->getBoundingBox()))
				{
					tempEnemies->pushBack(e);
					SimpleAudioEngine::getInstance()->playEffect("explode02.wav");
					//CCLOG("enemy shooted!!");
					//socre update
					
					
					break;
				}
			}
		}
		//doule loops to go through every rocket and enemy and judge then add to temp vector if collided.


		//then delete every enemy in temp vector by removeChildren
		for (int i =0 ;i<= tempEnemies->size()-1;i++)
		{
			Sprite* temp = tempEnemies->at(i);
			enemies.eraseObject(temp);
			this->removeChild(temp);
			Player::addScore(80+CCRANDOM_0_1()*40);

		}
		delete tempEnemies;
	}
}

bool  MainGame::init()
{
	if (!Layer::init())
	{
		return false;
	}

	//BGM
	SimpleAudioEngine::getInstance()->playBackgroundMusic("bgmusic.wav",true);

	//Timer tracker??? seting the listener 
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [=](Touch* t, Event *e) 
	{
		auto point = t->getLocationInView();
		point = Director::getInstance()->convertToGL(point);
		if (player->getBoundingBox().containsPoint(point))//judge whether touch point is on the player plane
		{
			isHoldPlayer = true;
		}
		else
		{
			isHoldPlayer=false;
		}
		return true;
	};

	listener->onTouchMoved = [=](Touch *t,Event *e) 
	{
		auto point = t->getLocationInView();
		point= Director::getInstance()->convertToGL(point);

		if (isHoldPlayer && !isDead)
		{
			player->setPosition(point);
		}
	};

	listener->onTouchEnded = [=](Touch *t,Event *e) 
	{
		isHoldPlayer = false;
	};

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener,this);

	size = Director::getInstance()->getVisibleSize();

	bg1 = Sprite::createWithSpriteFrameName("back_img1.png");

	float scaleX = size.width / bg1->getContentSize().width;
	float scaleY = size.height / bg1->getContentSize().height;

	bg1->setScale(scaleX,scaleY);
	
	bg1->setAnchorPoint(Vec2(0,0));
	bg1->setPosition(0,1);

	this->addChild(bg1,0);

	bg2 = Sprite::createWithSpriteFrameName("back_img2.png");
	bg2->setScale(scaleX, scaleY);

	bg2->setAnchorPoint(Vec2(0, 0));
	bg2->setPosition(0, size.height+1);

	this->addChild(bg2,0);

	player = Player::createPlayer();
	

	this->addChild(player,3);


	//Enemy
	initEnemy();


	//GameOver
	auto GGLabel = Label::createWithTTF("You have been slain!Äã¹ÒÁË£¡£¡","boldChinese.ttf",40);
	GGLabel->setPosition(size.width/2, size.height/2);
	GGLabel->setVisible(false);
	GGLabel->setColor(Color3B::RED);
	this->addChild(GGLabel,5);
	gameOverLabel = GGLabel;
	//GGGGGGGGGGGGGGGGGGGGGGG


	//the time ticks by???
	schedule(schedule_selector(MainGame::tick),0.1f);//why????????????????????????
	schedule(schedule_selector(MainGame::moveBG));//why????????????????/?????????
	//???????????????????


	//exist button
	//auto backLabel = MenuItemLabel::create(Label::createWithTTF("·µ»Ø","boldChinese.ttf",40),this,menu_selector(MainGame::CBback));
	auto backLabel = MenuItemLabel::create(Label::createWithTTF("·µ»Ø","msyh.ttc",40),this,menu_selector(MainGame::CBback));

	backLabel->setPosition(Vec2(size.width*(0.9-0.5),size.height*(0.8-0.5)));

	backLabel->setTag(666);

	auto menu = Menu::create(backLabel,NULL);

	menu->setAnchorPoint(Point::ZERO);

	this->addChild(menu,4);


	return true;
}

void MainGame::CBback(Ref * pSender)
{
	Sprite * ptr = ((Sprite *)pSender);
	switch (ptr->getTag())
	{
	case 666:

		Welcome::gotoWelcome();

		break;


	default: {}


	}
}




	
