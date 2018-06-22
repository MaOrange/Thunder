#pragma execution_character_set("utf-8")
#include "Welcome.h"

#include<SimpleAudioEngine.h>
using namespace CocosDenshion;


Welcome::Welcome()
{
}


Welcome::~Welcome()
{
}

bool Welcome::init()
{
	//base init
	if (!Layer::init())
	{
		return false;
	}
	///////////////////////////////////



	//creat something///////
	Size size = Director::getInstance()->getWinSize();


	auto newLabel = Label::createWithTTF("MCZ的游戏","boldChinese.ttf", 80);
	newLabel->setPosition(Vec2(size.width/2,size.height*3/4));
	

	auto menu = Menu::create();

	auto opt1 = MenuItemLabel::create(Label::createWithTTF("开始！", "msyh.ttc",50),CC_CALLBACK_1(Welcome::menuCB,this));
	opt1->setPosition(Point::ZERO);
	menu->addChild(opt1);
	opt1->setTag(100);

	auto opt2 = MenuItemLabel::create(Label::createWithTTF("设置", "msyh.ttc", 50), CC_CALLBACK_1(Welcome::menuCB, this));
	opt2->setPosition(Vec2(0,-200));
	menu->addChild(opt2);
	opt2->setTag(101);

	this->addChild(newLabel,1);
	this->addChild(menu,1);
	//////////////////////////////////////////

	//preload////
	/*SimpleAudioEngine::getInstance*()->preloadBackgroundMusic("bgssmusic.wav");*/
	
	//init Audio MCZ/////////////////////
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("bgssmusic.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("fire01.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("explode1.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("expload2.wav");

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("plane.plist");

	auto bg = Sprite::createWithSpriteFrameName("background.png");

	bg->setPosition(Vec2(size.width/2,size.height/2));

	double Scaclex = size.width/bg->getContentSize().width ;
	double ScacleY = size.height/ bg->getContentSize().height;


	bg->setScaleX(Scaclex);
	bg->setScaleY(ScacleY);
	this->addChild(bg,0);

	//////////////////////////////////////
	return true;
}



void Welcome::menuCB(Ref* what)
{
	log("MenuCB called!!!");
	switch (((MenuItem*)what)->getTag())
	{
	case 100:
	{
		//log("Tag100 called!!");
		start();

		break;
	}
	case 101:
	{
		log("Tag101 called!!");
		break;
	}
	default:
		break;
	}



}


void Welcome::start()
{
	//????
	CCLOG("Welcome::start()  called!!");

	Director::getInstance()->replaceScene(TransitionPageTurn::create(1.0f,MainGame::createScene(),false));


}

void Welcome::setting()
{




}

void Welcome::gotoWelcome()
{
	CCLOG("tag 666 picked!!!");

	auto newScene = Scene::create();
	auto newLayer = Welcome::create();

	Player::reinit();

	newScene->addChild(newLayer);
	Director::getInstance()->replaceScene(newScene);
}
