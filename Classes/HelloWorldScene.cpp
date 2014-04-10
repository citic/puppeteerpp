#include "HelloWorldScene.h"

#include <CCDirector.h>
#include <CCGeometry.h>
#include <CCLabelTTF.h>
#include <CCMenu.h>
#include <CCMenuItem.h>
#include <CCScene.h>
#include <CCSprite.h>
#include <SimpleAudioEngine.h>

USING_NS_CC;

Scene* HelloWorld::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = HelloWorld::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	// Superclass init first
	if ( ! Layer::init() ) return false;

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();

	// Add a menu item with "X" image, which is clicked to quit the program you may modify it.
	// add a "close" icon to exit the progress. it's an autorelease object
	auto closeItem = MenuItemImage::create("CloseNormal.png", "CloseSelected.png", CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
	closeItem->setPosition(Point(origin.x + visibleSize.width - closeItem->getContentSize().width/2 , origin.y + closeItem->getContentSize().height/2));

	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu, 1);

	// Add your codes below...
	// add a label shows "Hello World"
	// create and initialize a label
	auto label = LabelTTF::create("Puppeteer++", "Arial", 24);

	// position the label on the center of the screen
	label->setPosition(Point(origin.x + visibleSize.width/2, origin.y + visibleSize.height - label->getContentSize().height));

	// add the label as a child to this layer
	this->addChild(label, 1);

	createMainMenu();

	// Play the background music
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("Music/puppeteer.mp3");
	return true;
}


void HelloWorld::menuCloseCallback(Ref* /*pSender*/)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
	return;
#endif

	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

void HelloWorld::createMainMenu()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();

	// Place the background image
	auto background = Sprite::create("GameMenu/Background.png");
	background->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
	this->addChild(background, 0);

	// Place the game title
}
