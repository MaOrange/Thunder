#pragma once
#include<cocos2d.h>
#include"Player.h"//????????????????
USING_NS_CC;


class HUDLayer:public Layer 
{
public:
	HUDLayer();

	virtual bool init() override;

	CREATE_FUNC(HUDLayer);

	void scoreUpdate(float dt);

	Action* removeOne(Sprite* theSp);

	void remove(float dt);

	Label * scoreLabel;

	Vector<Sprite*> lives;

	void deleteLife(Sprite*);

	int scoreOnShow = 0;
protected:


};
