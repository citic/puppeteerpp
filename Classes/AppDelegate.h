#ifndef _APP_DELEGATE_H_
#define _APP_DELEGATE_H_

#include <cocos2d.h>

/**
@brief Represents the Puppeteer++ game object as a whole

A better name could be PuppeteerVideoGame or GameApp
*/
class AppDelegate : public cocos2d::Application
{
  public:
	/// Constructor
	AppDelegate();

	/// Avoid copies of this object
	AppDelegate(const AppDelegate&) = delete;
	const AppDelegate& operator=(const AppDelegate&) = delete;

	/// Destructor
	virtual ~AppDelegate();

	/** @brief  Called when the video game is launched from the operating system
		@return true    Initialize success, app continue.
		@return false   Initialize failed, app terminate. */
	virtual bool applicationDidFinishLaunching();

	/** Called when the video game enters in background, that is, when the game window is
		minimized or when other appliation is launched in the mobile device */
	virtual void applicationDidEnterBackground();

	/** The function be called when the application exits from background, therefore it recovers
		the focus and becomes the active application */
	virtual void applicationWillEnterForeground();

  protected:
	/** Create the window where the game will be displayed.
		It adapts the game to the screen size on mobile devices, or adapts the screen size in PC **/
	bool createGameWindow();
};

#endif // _APP_DELEGATE_H_
