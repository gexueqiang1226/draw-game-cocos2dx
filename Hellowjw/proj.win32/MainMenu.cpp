#include "Mainmenu.h"
#include "AppDelegate.h"
#include "HelloWorldScene.h"

USING_NS_CC;

enum {
	MenuBackground,
	MenuNnormal,
	MenuChallenge,
	MenuMusicwitch,
	MenuQuit,
};

CCScene* MainMenu::scene()
{
	CCScene * scene = NULL;
	do 
	{
		// 'scene' is an autorelease object
		scene = CCScene::create();
		CC_BREAK_IF(! scene);

		// 'layer' is an autorelease object
		MainMenu *layer = MainMenu::create();
		CC_BREAK_IF(! layer);

		// add layer as a child to scene
		scene->addChild(layer);
	} while (0);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool MainMenu::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !CCLayer::init() )
	{
		return false;
	}

	visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	origin = CCDirector::sharedDirector()->getVisibleOrigin();

	size = CCDirector::sharedDirector()->getWinSize();


	//background
	CCSprite* pSprite = CCSprite::create("mainmenu_background.png");

	// Place the sprite on the center of the screen
	pSprite->setPosition(ccp(size.width/2, size.height/2));

	// Add the sprite to HelloWorld layer as a child layer.
	this->addChild(pSprite, 0,MenuBackground);


	//Normal
	CCMenuItemImage *pNormalItem = CCMenuItemImage::create(
		"btn_normalmode.png",
		"btn_normalmode_select.png",
		this,
		menu_selector(MainMenu::menuCloseCallbackNormal));

	pNormalItem->setPosition(ccp(origin.x + pNormalItem->getContentSize().width ,
		origin.y + visibleSize.height -  pNormalItem->getContentSize().height));
	CCMenu* pMenuNormal = CCMenu::create(pNormalItem, NULL);
	pMenuNormal->setPosition(CCPointZero);
	this->addChild(pMenuNormal,1, MenuNnormal);

	//Challenge
	CCMenuItemImage *pChallengeItem = CCMenuItemImage::create(
		"btn_challengemode.png",
		"btn_challengemode_select.png",
		this,
		menu_selector(MainMenu::menuCloseCallbackNormal));
	pChallengeItem->setPosition(ccp(origin.x + pChallengeItem->getContentSize().width ,
		origin.y + visibleSize.height -  2*pChallengeItem->getContentSize().height));
	CCMenu* pChallengeMusic = CCMenu::create(pChallengeItem, NULL);
	pChallengeMusic->setPosition(CCPointZero);
	this->addChild(pChallengeMusic,1, MenuChallenge);

	//Music
	CCMenuItemImage *MusicOnItem = CCMenuItemImage::create("btn_musicon.png","btn_musicon_select.png");
	CCMenuItemImage *MusicOffItem = CCMenuItemImage::create("btn_musicoff.png","btn_musicoff_select.png");
	CCMenuItemToggle *MusicToggle = CCMenuItemToggle::createWithTarget(this, menu_selector(MainMenu::menuMusicCallbackNormal), MusicOnItem,MusicOffItem, NULL);
	MusicToggle->setPosition(ccp(origin.x + pChallengeItem->getContentSize().width ,
		origin.y + visibleSize.height -  3*pChallengeItem->getContentSize().height));
	CCMenu* pMenuMusic = CCMenu::create(MusicToggle, NULL);
	pMenuMusic->setPosition(CCPointZero);
	this->addChild(pMenuMusic,1, MenuMusicwitch);

	//Exit
	CCMenuItemImage *pExitItem = CCMenuItemImage::create(
		"btn_exit.png",
		"btn_exit_select.png",
		this,
		menu_selector(MainMenu::menuCloseCallbackQuit));
	pExitItem->setPosition(ccp(origin.x + pExitItem->getContentSize().width ,
		origin.y + visibleSize.height -  4*pExitItem->getContentSize().height));
	CCMenu* pMenuExit= CCMenu::create(pExitItem, NULL);
	pMenuExit->setPosition(CCPointZero);
	this->addChild(pMenuExit,1, MenuMusicwitch);


	return true;
}

void MainMenu::menuCloseCallbackQuit(CCObject* pSender)
{
	CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}
void MainMenu::menuCloseCallbackNormal(CCObject* pSender){

	CCScene *pScene = HelloWorld::scene();

	CCDirector *pDirector = CCDirector::sharedDirector();

	pDirector->replaceScene(CCTransitionFlipX::transitionWithDuration(0.5f,pScene,kOrientationLeftOver));
}
void MainMenu::menuMusicCallbackNormal(CCObject* pSender){


	static bool musicswitch = true;
	musicswitch = !musicswitch;

	//TODO “Ù¿÷ø™πÿ

}