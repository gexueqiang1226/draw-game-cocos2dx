#include "cocos2d.h"
#include "CCEGLView.h"
#include "AppDelegate.h"
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "Mainmenu.h"

using namespace CocosDenshion;

USING_NS_CC;

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate()
{
    SimpleAudioEngine::end();
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());

    // enable High Resource Mode(2x, such as iphone4) and maintains low resource on other devices.
//     pDirector->enableRetinaDisplay(true);
CCEGLView::sharedOpenGLView()->setDesignResolutionSize(480, 320,kResolutionShowAll); 

	TargetPlatform target = getTargetPlatform();

	if (target == kTargetIpad)
	{
		// ipad

		if (pDirector->enableRetinaDisplay(true))
		{
			// ipad hd
			CCFileUtils::sharedFileUtils()->setResourceDirectory("ipadhd");
		}
		else 
		{
			CCFileUtils::sharedFileUtils()->setResourceDirectory("ipad");
		}
	}
	else if (target == kTargetIphone)
	{
		// iphone

		if (pDirector->enableRetinaDisplay(true))
		{
			// iphone hd
			CCFileUtils::sharedFileUtils()->setResourceDirectory("hd");
		}
	}


    // turn off display FPS
    pDirector->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    CCScene *pScene = MainMenu::scene();

    // run
    pDirector->runWithScene(pScene);
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->stopAnimation();

    SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->startAnimation();

    SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}