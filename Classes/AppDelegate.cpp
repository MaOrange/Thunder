#include "AppDelegate.h"
#include "HelloWorldScene.h"
#include"Welcome.h"
#include"GameManager.h"
#include"MainGame.h"
#include<SimpleAudioEngine.h>
using namespace CocosDenshion;
USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
	//set OpenGL context attributions,now can only set six attributions:
	//red,green,blue,alpha,depth,stencil
	GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

	GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching() {
	// initialize director
	auto director = Director::getInstance();
	auto glview = director->getOpenGLView();
	if(!glview) {
		glview = GLViewImpl::createWithRect("Thunder", Rect(0, 0, 640, 960));
		director->setOpenGLView(glview);
	}

	director->getOpenGLView()->setDesignResolutionSize(640, 960, ResolutionPolicy::SHOW_ALL);

	// turn on display FPS
	director->setDisplayStats(true);

	// set FPS. the default value is 1.0/60 if you don't call this
	director->setAnimationInterval(1.0f / 60);

	FileUtils::getInstance()->addSearchPath("res");



	////init Audio MCZ/////////////////////
	//SimpleAudioEngine::getInstance()->preloadBackgroundMusic("bgssmusic.wav");
	//SimpleAudioEngine::getInstance()->preloadEffect("fire01.wav");
	//SimpleAudioEngine::getInstance()->preloadEffect("explode1.wav");
	//SimpleAudioEngine::getInstance()->preloadEffect("expload2.wav");

	//SpriteFrameCache::getInstance()->addSpriteFramesWithFile("plane.plist");

	//auto bg = Sprite::createWithSpriteFrameName("background.png");


	//MCZ:: start here|||||||||||||||||||||||||||||||| 
	auto newScene = Scene::create();

	auto newLayer = Welcome::create();
	newScene->addChild(newLayer);

	Director::getInstance()->runWithScene(newScene);



	return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
	Director::getInstance()->stopAnimation();

	// if you use SimpleAudioEngine, it must be pause
	// SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
	Director::getInstance()->startAnimation();

	// if you use SimpleAudioEngine, it must resume here
	// SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
