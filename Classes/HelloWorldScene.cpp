#include "HelloWorldScene.h"

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
	createGameTitle();

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

//#include <cocos2d.h>

void HelloWorld::createGameTitle()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();

	// Place the game title
	auto gameTitle = Sprite::create("GameMenu/GameTitle.png");
	gameTitle->setPosition(Point(visibleSize.width/2 + origin.x - 122 / 2, visibleSize.height - 150.0f + 55));
	this->addChild(gameTitle, 0);

/*
	char buffer[256];
	auto animation = Animation::create();
	for ( int i = 0; i <= 10; ++i )
	{
		int imageIndex = i <= 5 ? i : 10 - i;
		sprintf(buffer, "GameMenu/GameTitle%i.png", imageIndex);
		animation->addSpriteFrameWithFile(buffer);
	}

	animation->setDelayPerUnit( 0.1333f);
	auto repeatAnimation = RepeatForever::create( Animate::create(animation) );
	gameTitle->runAction(repeatAnimation);
*/
	// Place the masks animation

	Vector<SpriteFrame*> animFrames(14);
	for(int i = 0; i < 7; ++i)
		animFrames.pushBack( SpriteFrame::create("GameMenu/Masks.png", Rect(0, i * 143, 122, 143)) );

	for(int i = 6; i >= 0; --i)
		animFrames.pushBack( SpriteFrame::create("GameMenu/Masks.png", Rect(0, i * 143, 122, 143)) );

	auto masks = Sprite::createWithSpriteFrame( animFrames.at(0) );
	masks->setPosition(Point(visibleSize.width / 2 + origin.x + 122, visibleSize.height - 150.0f));
	this->addChild(masks, 0);

	auto animation = Animation::createWithSpriteFrames(animFrames, 0.1333f);
	auto animate = Animate::create(animation);
	auto repeatAnimation = RepeatForever::create(animate);
	masks->runAction(repeatAnimation);
}
