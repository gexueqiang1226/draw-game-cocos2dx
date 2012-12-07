#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

#include "Box2D/Box2D.h"

#include "chipmunk.h"

#include "SimpleAudioEngine.h"

#include "geometry.h"


class HelloWorld : public cocos2d::CCLayer
{
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();  

	// there's no 'id' in cpp, so we recommand to return the exactly class pointer
	static cocos2d::CCScene* scene();

	// a selector callback
	void menuCloseCallback(CCObject* pSender);


	int numofSPA;
	cocos2d::CCNode* SpriteArray[200];//精灵数组，方便释放时候加动作
	
	cocos2d::CCSize size;//屏幕大小

	MyPoint PlantLine[2500];//画的点坐标，用于判断形状
	int PlantLineNum;//画的点数
	float plainlen;//画的长度

	float m_time;//时间
	int m_score;//分数
	int now_score;//显示的分数
	int temp_score;//延时分数


	int GoalShape;//目标形状
	int JudgeResult;//判断结果

	void AddTimeLabel();//时间文字
	void step(float dt);//时间更新事件

	//TODO 当前时间，毫秒，暂时不用
	long millisecondNow();

	//Touch
	virtual void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
	virtual void ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
	virtual void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);

	void spriteFinished(cocos2d::CCNode* sender);//删除精灵
	cocos2d::CCNode* makeStarSprite(float x,float y);//生成星星精灵
	void StarSpriteDown(cocos2d::CCNode* sender);//精灵的下落动画
	void StarSpriteUp(cocos2d::CCNode* sender);//精灵的上升动画
	void SpecilScore(int);//特殊得分
	void ResultText(bool);//Accept WrongAnswer

	void JudgeClose(int &close1,int &close2);//封闭区间
	void JudgeShape(int s,int t);//判断封闭形状

	//*计算PlantLine中 点的平均距离      
	float Cal_k();

	//画出形状
	void PushCricle(float _x,float _y,float _r);
	void PushLine(float _x1,float _y1,float _x2, float _y2,const float len);
	void PushFourPoint(float _x1,float _y1,float _x2,float _y2,float _x3,float _y3,float _x4,float _y4);
	void PushThreePoint(float _x1,float _y1,float _x2,float _y2,float _x3,float _y3);

	// implement the "static node()" method manually
	CREATE_FUNC(HelloWorld);
};

#endif  // __HELLOWORLD_SCENE_H__