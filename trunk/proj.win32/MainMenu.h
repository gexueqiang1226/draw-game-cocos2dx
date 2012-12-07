#ifndef __MAINMENU_H__
#define __MAINMENU_H__

#include "cocos2d.h"

class MainMenu : public cocos2d::CCLayer
{
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();  

	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::CCScene* scene();

	// a selector callback
	void menuCloseCallbackQuit(CCObject* pSender);

	// a selector callback
	void menuCloseCallbackNormal(CCObject* pSender);

	// a selector callback
	void menuMusicCallbackNormal(CCObject* pSender);

	cocos2d::CCSize size;//ÆÁÄ»´óÐ¡
	cocos2d::CCSize visibleSize;
	cocos2d::CCPoint origin;

	// implement the "static node()" method manually
	CREATE_FUNC(MainMenu);
};

#endif // __MAINMENU_H__
