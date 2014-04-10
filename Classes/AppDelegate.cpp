#include "AppDelegate.h"
#include "HelloWorldScene.h"

#include <CCDirector.h>
#include <CCGLView.h>
#include <SimpleAudioEngine.h>

USING_NS_CC;

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate()
{
}

bool AppDelegate::applicationDidFinishLaunching()
{
	// Initialize director
	auto director = Director::getInstance();

	// Create the game window
	if ( ! createGameWindow() ) return false;

	// turn on display FPS
	director->setDisplayStats(true);

	// set FPS. the default value is 1.0/60 if you don't call this
	director->setAnimationInterval(1.0 / 60);

	// create a scene. it's an autorelease object
	auto scene = HelloWorld::createScene();

	// run
	director->runWithScene(scene);

	return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
	Director::getInstance()->stopAnimation();

	// if you use SimpleAudioEngine, it must be pause
	CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
	Director::getInstance()->startAnimation();

	// if you use SimpleAudioEngine, it must resume here
	CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}

bool AppDelegate::createGameWindow()
{
	auto director = Director::getInstance();
	auto window = director->getOpenGLView();
	if( ! window )
	{
		window = GLView::create("Puppeteer++");
		if ( ! window ) return false;
		director->setOpenGLView(window);
	}

	// Game graphics are designed for 1024x768
	window->setDesignResolutionSize(1024, 768, ResolutionPolicy::EXACT_FIT);

#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 || CC_TARGET_PLATFORM == CC_PLATFORM_LINUX || CC_TARGET_PLATFORM == CC_PLATFORM_MAC
	window->setFrameSize(1024, 768);
#endif

	return true;
}
