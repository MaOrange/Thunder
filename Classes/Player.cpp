#include "Player.h"
#include<cocos2d.h>
#include"SimpleAudioEngine.h"
USING_NS_CC;
using namespace CocosDenshion;


int Player::life = 5;
int Player::score = 0;

Player::Player()
{
}


Player::~Player()
{
}


int Player::getLife()
{
	return life;
}

int Player::getScore()
{
	return score;
}

void Player::addScore(int plus)
{
	score += plus;
}

void Player::reinit()
{
	life = 5;

	score = 0;

	SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}




bool Player::initSprite()
{
	if (!Sprite::init())
	{
		return false;

	}

	Size size = Director::getInstance()->getVisibleSize();

	auto player_frame = SpriteFrameCache::getInstance()->getSpriteFrameByName("player.png");

	this->setSpriteFrame(player_frame);

	this->setScale(2.0);

	this->setPosition(Vec2(size.width/2,size.height*0.2));
	return true;
}


Player * Player::createPlayer()
{

	Player * newPlayer = new Player;

	newPlayer->initSprite();

	newPlayer->autorelease();

	return newPlayer;

}