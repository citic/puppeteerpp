#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include <CCLayer.h>
#include <CCPlatformMacros.h>

class cocos2d::Ref;
class cocos2d::Scene;

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
};

#endif // __HELLOWORLD_SCENE_H__
