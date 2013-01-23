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
	cocos2d::CCNode* SpriteArray[200];//�������飬�����ͷ�ʱ��Ӷ���
	
	cocos2d::CCSize size;//��Ļ��С

	MyPoint PlantLine[2500];//���ĵ����꣬�����ж���״
	int PlantLineNum;//���ĵ���
	float plainlen;//���ĳ���

	float m_time;//ʱ��
	int m_score;//����
	int now_score;//��ʾ�ķ���
	int temp_score;//��ʱ����


	int GoalShape;//Ŀ����״
	int JudgeResult;//�жϽ��

	void AddTimeLabel();//ʱ������
	void step(float dt);//ʱ������¼�

	//TODO ��ǰʱ�䣬���룬��ʱ����
	long millisecondNow();

	//Touch
	virtual void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
	virtual void ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
	virtual void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);

	void spriteFinished(cocos2d::CCNode* sender);//ɾ������
	cocos2d::CCNode* makeStarSprite(float x,float y);//�������Ǿ���
	void StarSpriteDown(cocos2d::CCNode* sender);//��������䶯��
	void StarSpriteUp(cocos2d::CCNode* sender);//�������������
	void SpecilScore(int);//����÷�
	void ResultText(bool);//Accept WrongAnswer

	void JudgeClose(int &close1,int &close2);//�������
	void JudgeShape(int s,int t);//�жϷ����״

	//*����PlantLine�� ���ƽ������      
	float Cal_k();

	//������״
	void PushCricle(float _x,float _y,float _r);
	void PushLine(float _x1,float _y1,float _x2, float _y2,const float len);
	void PushFourPoint(float _x1,float _y1,float _x2,float _y2,float _x3,float _y3,float _x4,float _y4);
	void PushThreePoint(float _x1,float _y1,float _x2,float _y2,float _x3,float _y3);

	// implement the "static node()" method manually
	CREATE_FUNC(HelloWorld);
};

#endif  // __HELLOWORLD_SCENE_H__