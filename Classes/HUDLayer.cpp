#pragma execution_character_set("utf-8")
#include "HUDLayer.h"

HUDLayer::HUDLayer() {
	
}

bool HUDLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	//scene size
	auto size = Director::getInstance()->getVisibleSize();

	//Score board
	auto newLabel = Label::createWithTTF(String::createWithFormat("得分:%d",scoreOnShow)->getCString(),"msyh.ttc",40);
	newLabel->setPosition(Vec2(size.width*0.2,size.height*0.85));
	this->addChild(newLabel);
	scoreLabel = newLabel;

	//life image initialize
	int curLife = Player::getLife();

	auto anchor = Vec2(size.width*0.1f,size.height*0.80f);
	int shift = 10;
	auto newSprite = Sprite::create("life.png");
	auto wid = (newSprite->getContentSize()).width;
	for (int i = 0; i <= curLife - 1; i++)
	{
		auto newSprite = Sprite::create("life.png");
		lives.pushBack(newSprite);

		newSprite->setPosition(Vec2(anchor.x+(shift+wid)*i,anchor.y));

		this->addChild(newSprite,5);
	}
	CCLOG("live.szie()=%d",lives.size());

	schedule(schedule_selector(HUDLayer::remove),0.1f);
	schedule(schedule_selector(HUDLayer::scoreUpdate), 0.01f);

	return true;
}


void HUDLayer::scoreUpdate(float dt)
{
	if ((Player::getScore() - scoreOnShow) > 3)
	{
		scoreOnShow += 3;
		scoreLabel->setString(String::createWithFormat("得分:%d",scoreOnShow)->getCString());
	}
	else if ((Player::getScore() - scoreOnShow) < 10 && (Player::getScore() - scoreOnShow)>0)
	{
		scoreOnShow = Player::getScore();
		scoreLabel->setString(String::createWithFormat("得分:%d", scoreOnShow)->getCString());
	}
	else
	{
		//impossible
	}
	
}

Action * HUDLayer::removeOne(Sprite* theSp)
{
	auto * up = MoveBy::create(0.5,Vec2(0,10));//time x y

	auto * fade = FadeOut::create(0.5);//time

	auto del = CallFunc::create(CC_CALLBACK_0(HUDLayer::deleteLife,this,theSp));

	auto combo = Spawn::create(up, fade, NULL);

	auto seq = Sequence::create(combo,del,NULL);

	return seq;
}

void HUDLayer::remove(float dt)
{
	//int cursize = lives.size();
	CCLOG("remove called!");

	while (lives.size() > Player::getLife()&& lives.size()>0)
	{
		Sprite* tempPtr = lives.at(lives.size() - 1);
		lives.popBack();
		
		tempPtr->runAction(removeOne(tempPtr));
	}
}

void HUDLayer::deleteLife(Sprite* toDel)
{
	toDel->removeFromParentAndCleanup(true);
	//lives.eraseObject(toDel);
}
