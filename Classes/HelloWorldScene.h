#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include <cocos2d.h>

class HelloWorld : public cocos2d::Layer
{
  public:
	/// Create a scene with this layer
	static cocos2d::Scene* createScene();

	/// Initializes the scene: creates the scenery and places each actor in its place before
	/// the scene will be shown
	virtual bool init();

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(HelloWorld)

  protected:
	/// Create the main menu scenography
	void createMainMenu();
	/// Create the game title and animates it
	void createGameTitle();
};

#endif // __HELLOWORLD_SCENE_H__
