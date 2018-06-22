#include "GameManager.h"



GameManager::GameManager()
{
}


GameManager::~GameManager()
{
}



GameManager* GameManager::getInstance()
{
	if (!thisManager)
	{
		auto newManager = new GameManager;
		thisManager = newManager;
	}
	return thisManager;
}


void GameManager::start()
{
	CCLOG("start callled!!!");

	auto gameScene = Scene::create();

	Director::getInstance()->replaceScene(gameScene);



}

Scene* GameManager::createMainScene()
{
	auto newScene = Scene::create();

	auto newLayer = Scene::create();

	newScene->addChild(newLayer);

	return newScene;


}

GameManager* GameManager::thisManager = new GameManager;