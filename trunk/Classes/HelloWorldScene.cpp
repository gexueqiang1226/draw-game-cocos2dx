#include "HelloWorldScene.h"

using namespace cocos2d;

enum {
	kTagTimeLabel,
	kTagScoreLabel,
	kTagSprite3,
	kTagSprite4,
	kTagSprite5,
	kTagSprite6,
	kTagSprite7,
	kTagSprite8,
};

CCScene* HelloWorld::scene()
{
	CCScene * scene = NULL;
	do 
	{
		// 'scene' is an autorelease object
		scene = CCScene::create();
		CC_BREAK_IF(! scene);

		// 'layer' is an autorelease object
		HelloWorld *layer = HelloWorld::create();
		CC_BREAK_IF(! layer);

		// add layer as a child to scene
		scene->addChild(layer);
	} while (0);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	bool bRet = false;
	do 
	{
		//init data
		numofSPA = 0;
		PlantLineNum = 0;
		plainlen = 0;
		m_time = 0;
		m_score = 0;
		now_score = 0;
		temp_score = 0;

		//////////////////////////////////////////////////////////////////////////
		// super init first
		//////////////////////////////////////////////////////////////////////////

		CC_BREAK_IF(! CCLayer::init());

		//////////////////////////////////////////////////////////////////////////
		// add your codes below...
		//////////////////////////////////////////////////////////////////////////

		// 1. Add a menu item with "X" image, which is clicked to quit the program.

		// Create a "close" menu item with close icon, it's an auto release object.
		//һ�����Ե����x��ť
		CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
			"CloseNormal.png",
			"CloseSelected.png",
			this,
			menu_selector(HelloWorld::menuCloseCallback));//�رյķ�������
		CC_BREAK_IF(! pCloseItem);

		// Place the menu item bottom-right conner.
		pCloseItem->setPosition(ccp(size.width - 20, 20));

		// Create a menu with the "close" menu item, it's an auto release object.
		CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
		pMenu->setPosition(CCPointZero);
		CC_BREAK_IF(! pMenu);

		// Add the menu to HelloWorld layer as a child layer.
		this->addChild(pMenu, 1);

		// 2. Add a label shows "Hello World".

		// Create a label and initialize with string "Hello World".
		CCLabelTTF* pLabel = CCLabelTTF::create("00000", "Arial", 24);
		CC_BREAK_IF(! pLabel);

		// Get window size and place the label upper. 
		size = CCDirector::sharedDirector()->getWinSize();
		pLabel->setPosition(ccp(40, size.height-24 ));

		// Add the label to HelloWorld layer as a child layer.
		this->addChild(pLabel, 1,kTagScoreLabel);


		// 3. Add add a splash screen, show the cocos2d splash image.
		CCSprite* pSprite = CCSprite::create("background.png");
		CC_BREAK_IF(! pSprite);

		// Place the sprite on the center of the screen
		pSprite->setPosition(ccp(size.width/2, size.height/2));

		// Add the sprite to HelloWorld layer as a child layer.
		this->addChild(pSprite, 0);

		//ʱ��
		AddTimeLabel();

		this->setTouchEnabled(true);

		bRet = true;

	} while (0);

	return bRet;
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
	// "close" menu item clicked
	CCDirector::sharedDirector()->end();
}


void HelloWorld::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{		
}

void HelloWorld::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
	CCSetIterator iter = pTouches->begin();

	for (; iter != pTouches->end(); iter++)
	{
		CCTouch* pTouch = (CCTouch*)(*iter);
		CCPoint location = pTouch->getLocation();

		if(numofSPA<200){
			SpriteArray[numofSPA] = NULL;
			SpriteArray[numofSPA] = makeStarSprite(location.x,location.y);
			if(SpriteArray[numofSPA]!=NULL){
				numofSPA++;

				PlantLine[PlantLineNum+1].x = location.x;
				PlantLine[PlantLineNum+1].y =location.y;
				plainlen += PlantLine[PlantLineNum].Dis_PointToPoint(PlantLine[PlantLineNum+1]);
				PlantLineNum++;
			}

		}
	}
}

void HelloWorld::ccTouchesEnded(CCSet* pTouches, CCEvent* pEvent)
{
	for(int i=0;i<numofSPA;i++){
		StarSpriteDown(SpriteArray[i]);
	}
	//�ж�
	int temp1 ,temp2;
	JudgeClose(temp1,temp2);
	if(temp1 != -1 && temp2 != -1)
	{
		JudgeShape(temp1,temp2);
	}
	numofSPA = 0;
	PlantLineNum = 0;
}

void HelloWorld::AddTimeLabel()
{
	m_time = 0;
	CCLabelTTF* label = CCLabelTTF::create("0.00", "Arial", 24);
	addChild(label,1, kTagTimeLabel);
	label->setPosition( ccp(size.width-50,size.height-20) );
	label->setOpacity( 80 );
	schedule(schedule_selector(HelloWorld::step)); 
}
void HelloWorld::step(float dt)
{
	m_time += dt;
	char str[12] = {0};
	sprintf(str, "%2.2f", m_time);

	CCLabelTTF* label = (CCLabelTTF*)getChildByTag(kTagTimeLabel);
	label->setString(str);


	if(now_score<m_score){
		now_score++;
		char str[12] = {0};
		sprintf(str, "%05d", now_score);
		CCLabelTTF* label = (CCLabelTTF*)getChildByTag(kTagScoreLabel);
		label->setString(str);
	}
}

/************************************************************************/
/* ɾ������                                                             */
/************************************************************************/
void HelloWorld::spriteFinished(CCNode* sender){
	CCSprite *sprite  = (CCSprite *) sender;
	this->removeChild(sprite,true);
	if(temp_score!=0)
		m_score+=temp_score,temp_score=0;

}

/************************************************************************/
/* �������Ǿ���                                                         */
/************************************************************************/
CCNode* HelloWorld::makeStarSprite(float x,float y){

	if(x<0||y<0
		||x>size.width||y>size.height)
		return NULL;

	CCSprite* pSprite = CCSprite::create("star.png");

	pSprite->setPositionX(x);
	pSprite->setPositionY(y);

	addChild(pSprite, 0);


	return pSprite;

}
/************************************************************************/
/*��������䶯��                                                        */
/************************************************************************/
void HelloWorld::StarSpriteDown(cocos2d::CCNode* sender){
	CCSprite *pSprite  = (CCSprite *) sender;

	int moveunit = 200;
	int doubleunit = moveunit<<1;
	CCPoint cbegan = ccp(pSprite->getPositionX(),pSprite->getPositionY());
	CCPoint cend = CCPoint(pSprite->getPositionX()+(CCRANDOM_0_1()*doubleunit-moveunit),-10);

	ccBezierConfig bezier; // ��������������
	bezier.controlPoint_1 = cbegan; // ��ʼ��
	bezier.controlPoint_2 = ccp((cbegan.x+cend.x)*0.5, (cbegan.y+cend.y)*0.5+200); //���Ƶ�
	bezier.endPosition = cend; // ����λ��

	// Move projectile to actual endpoint
	pSprite->runAction( CCSequence::actions(
		CCBezierTo::actionWithDuration(0.8, bezier),
		CCCallFuncN::actionWithTarget(this, 
		callfuncN_selector(HelloWorld::spriteFinished)), 
		NULL) );


}
/************************************************************************/
/*�������������                                                        */
/************************************************************************/
void HelloWorld::StarSpriteUp(cocos2d::CCNode* sender)
{
	CCSprite *pSprite  = (CCSprite *) sender;

	CCPoint cbegan = ccp(pSprite->getPositionX(),pSprite->getPositionY());
	CCPoint cend = CCPoint(10,size.height);

	ccBezierConfig bezier; // ��������������
	bezier.controlPoint_1 = cbegan; // ��ʼ��
	bezier.controlPoint_2 = ccp((cbegan.x+cend.x)*0.5, (cbegan.y+cend.y)*0.5+400*CCRANDOM_0_1()-200); //���Ƶ�
	bezier.endPosition = cend; // ����λ��

	// Move projectile to actual endpoint
	pSprite->runAction( CCSequence::actions(
		CCBezierTo::actionWithDuration(0.8, bezier),
		CCCallFuncN::actionWithTarget(this, 
		callfuncN_selector(HelloWorld::spriteFinished)), 
		NULL) );
}

long HelloWorld::millisecondNow()  
{ 
	struct cc_timeval now; 
	CCTime::gettimeofdayCocos2d(&now, NULL); 
	return (now.tv_sec * 1000 + now.tv_usec / 1000); 
} 

/************************************************************************/
/* �ཻ�� s t                                                           */
/************************************************************************/
void HelloWorld::JudgeShape(int s,int t)
{
	MyPoint temppoint = PlantLine[t+1];
	PlantLine[t+1] = PlantLine[s];
	int i;
	float k = 120.0;
	float temp;
	int sum1 = 0,sum2 = 0 , sum3 = 0;
	//������������ͻ����
	int cross[1000];           //ͻ�����±�
	MyPoint crossPoint[1000]; //���ˣ���һ����������¼ͻ��㣬�����õ�
	int index = 1;
	int cross_len = 6;//ͻ������
	int lase_cross = 0;
	cross[0] = s;
	CCLog("began cluculate between : %d %d\n",s,t);
	for(i=s;i<t;i++)
	{
		temp = AngleofLines(MyLine(PlantLine[i+1],PlantLine[i]) , MyLine(PlantLine[i+1],PlantLine[i+2]));
		if(temp != inf)
		{
			if(temp == 180.0) sum3++;
			if(temp > 175) sum1 ++;
			if(temp <= 175 && temp >160) sum2 ++;

			if(temp <= 160)
			{
				if(i - lase_cross > cross_len && t - cross_len > i)
				{
					cross[index] = i;
					index++;
				}
				lase_cross = i;
				CCLog("<%012.3lf>  ",temp);//����ר��
			}
			else
			{
				CCLog("%14.3lf  ",temp);//����ר��
			}
		}
		else
			CCLog("\t   INF  ");
	}
	CCLog("\n");//����ר��
	CCLog("==180: %d / %d -- %.4lf\n",sum3,t-s+1,(double(sum3) / (t-s+1)));//����ר��
	CCLog(">=175: %d / %d -- %.4lf\n",sum1,t-s+1,(double(sum1) / (t-s+1)));//����ר��
	CCLog("160-175: %d / %d -- %.4lf\n",sum2,t-s+1,(double(sum2) / (t-s+1)));//����ר��


	if(index > 6)
		CCLog("WTF");
// 		CCLog("����������ʲôͼ�ΰ�\n");


	CCLog("Cross_len : %d So many angle %d\n",cross_len,index);
	for (i = 0; i < index ; i++)
	{
		crossPoint[i] = PlantLine[cross[i]];
	}
	
	if( ( (double(sum1) / (t-s))  < 0.45 && (double(sum2) / (t-s)) > 0.45) || index >= 6)//��ʱ�����������Ϊ��һ��Բ
	{
		MyPoint O_mid;
		float O_r;
		float temp_x = 0, temp_y = 0 , temp_r = 0;
		for(i = s ; i <= t ; i++)
		{
			temp_x += PlantLine[i].x;
			temp_y += PlantLine[i].y;
		}
		O_mid.x = temp_x / (t-s+1);
		O_mid.y = temp_y / (t-s+1);
		for (i = s ; i<= t ; i++)
		{
			temp_r += O_mid.Dis_PointToPoint(PlantLine[i]);
		}
		O_r = temp_r / (t-s+1);

		PushCricle(O_mid.x,O_mid.y,O_r);

		CCLog("Judge->yuan xing");
		//TODO �ж�����
// 		JudgeCricleScore(O_mid.x,O_mid.y,O_r);
	}
	else
	{
		//������ʱ������
		SortPoint(crossPoint,index);
		//����ר�� ������
		for(int i  = 0 ;i < index ; i++)
		{
			CCLog(" %d  %.4lf %.4lf\n",i,crossPoint[i].x,crossPoint[i].y);
		}
		//����ר��*/
		crossPoint[index] =crossPoint[0];
		if(index == 4)
		{
			PushFourPoint(PlantLine[cross[0]].x,PlantLine[cross[0]].y,
						  PlantLine[cross[1]].x,PlantLine[cross[1]].y,
						  PlantLine[cross[2]].x,PlantLine[cross[2]].y,
						  PlantLine[cross[3]].x,PlantLine[cross[3]].y);
			CCLog("Judge->si bian xing");
			//TODO �ж�����
// 			JudgeSquareScore(crossPoint,index);
		}
		if(index == 3)
		{
			PushThreePoint(PlantLine[cross[0]].x,PlantLine[cross[0]].y,
						   PlantLine[cross[1]].x,PlantLine[cross[1]].y,                                                                                                                                                    
						   PlantLine[cross[2]].x,PlantLine[cross[2]].y);
			CCLog("Judge->san jiao xing");
			//TODO �ж�����
// 			JudgeSquareScore(crossPoint,index);
		}
	}

	PlantLine[t+1] = temppoint;
}

/************************************************************************/
/* �жϱպ�             
return  close1, close2 
/************************************************************************/
void HelloWorld::JudgeClose(int &close1,int &close2)
{
	int i,j;
	int min_cross_point_len = inf;
	float min_oneToLine = inf;
	int temp1,temp2;
	int num_cross = 0; // ����¼ӵı�������¼�ж��ٸ��ཻ�㣬̫���ཻ�㣬���ǲ��Ϸ���ͼ��
	//���ж�ͼ���ǲ��ǽ��Ʊպϵ�,��ͼ�εĿ�ʼ��ͽ�β����΢�ӳ�һ��
	/*  ��x^2 + ��y^2 = k^2
		��y / ��x = t
		���� k���ӳ��Ľ��Ƶĳ��ȣ�t = (y1 - y2)/(x1 - x2) Ϊб��
		���: (t^2+1)��x^2 = k^2
	*/
	//k��ֵҪ���ձ�����ȷ��
	float k = Cal_k() * 3;
	if(k < 0.3)   k = 0.3;
	CCLog("k = %lf \n",k);//����ר��
	if(PlantLineNum > 1)
	{
		//���ǿ�ʼ����ӳ�
		double t = (PlantLine[1].y - PlantLine[2].y)/(PlantLine[1].x - PlantLine[2].x);
		double tx = (double)sqrt((k*k)/(t*t+1));

		if (fabs(PlantLine[1].x - PlantLine[2].x) < 0.00001)
		{
			PlantLine[0].x = PlantLine[1].x;
			if(PlantLine[1].y < PlantLine[2].y)
				PlantLine[0].y = PlantLine[1].y - k;
			else
				PlantLine[0].y = PlantLine[1].y + k;
		}
		else
		{
			if(PlantLine[1].x < PlantLine[2].x)
				PlantLine[0].x = PlantLine[1].x - tx;
			else
				PlantLine[0].x = PlantLine[1].x + tx;

			if(PlantLine[1].y < PlantLine[2].y)
				PlantLine[0].y = PlantLine[1].y - fabs(tx * t);
			else
				PlantLine[0].y = PlantLine[1].y + fabs(tx * t);
		}

		//ͬ���ӳ�������
		t = (PlantLine[PlantLineNum].y - PlantLine[PlantLineNum-1].y)/(PlantLine[PlantLineNum].x - PlantLine[PlantLineNum-1].x);
		tx = sqrt((k*k)/(t*t+1));

		if(fabs(PlantLine[PlantLineNum].x - PlantLine[PlantLineNum-1].x) < 0.00001)
		{
			PlantLine[PlantLineNum+1].x = PlantLine[PlantLineNum].x;
			if(PlantLine[PlantLineNum].y < PlantLine[PlantLineNum-1].y)
				PlantLine[PlantLineNum+1].y = PlantLine[PlantLineNum].y - k;
			else
				PlantLine[PlantLineNum+1].y = PlantLine[PlantLineNum].y + k;
		}
		else
		{
			if(PlantLine[PlantLineNum].x < PlantLine[PlantLineNum-1].x)
				PlantLine[PlantLineNum+1].x = PlantLine[PlantLineNum].x - tx;
			else
				PlantLine[PlantLineNum+1].x = PlantLine[PlantLineNum].x + tx;

			if(PlantLine[PlantLineNum].y < PlantLine[PlantLineNum-1].y)
				PlantLine[PlantLineNum+1].y = PlantLine[PlantLineNum].y - fabs(tx * t);
			else
				PlantLine[PlantLineNum+1].y = PlantLine[PlantLineNum].y + fabs(tx * t);
		}

		//Ȼ���ٿ�ʼ�жϷ���һ���ж������߶�֮����û���㽶
		for(i=0;i<=PlantLineNum;i++)
		{
			for(j=0;j<=PlantLineNum;j++)
			{
				if( abs(i-j) < 6 ) break;//����ܽ��ĵ㣬�����ཻ��������
				MyPoint temp = isCross(MyLine(PlantLine[i],PlantLine[i+1]),MyLine(PlantLine[j],PlantLine[j+1]));
				if(temp.isExist())
				{
					num_cross ++;
					if(min_cross_point_len > abs(i-j))
					{
						min_cross_point_len = abs(i-j);
						temp1 = i;
						temp2 = j;
					}
				}
			}
		}
		//��������ҵ����ཻ�㣬�Ͳ��÷�������
		//Ȼ���ٿ�ʼ�жϷ�������1�����жϵ�һ����߶εľ���
		if(min_cross_point_len == inf)
		{
			float len_l,len_mid,len_r;
			float l_pointToLine;
			const float LEN = k * 0.8;
			len_r = PlantLine[1].Dis_PointToPoint(PlantLine[19]);
			for(i = 20;i<=PlantLineNum;i++)
			{
				len_l = len_r;
				len_mid = MyLine(PlantLine[i-1],PlantLine[i]).Dis_PointToLine(PlantLine[1]);
				len_r = PlantLine[1].Dis_PointToPoint(PlantLine[i]);
				if( (len_mid < len_l && len_mid < len_r) || (len_mid > len_l && len_mid > len_r) )
				{
					l_pointToLine = len_l < len_r ? len_l : len_r;
				}
				else
				{
					l_pointToLine = len_mid;
				}
				if(l_pointToLine < LEN && l_pointToLine < min_oneToLine)
				{
					min_oneToLine = l_pointToLine;
					temp1 = 1;
					temp2 = i-1;
				}
			}

			//Ȼ���ٿ�ʼ�жϷ�������2�����ж����һ����߶εľ���
			len_r = PlantLine[PlantLineNum].Dis_PointToPoint(PlantLine[PlantLineNum-19]);
			for(i = PlantLineNum-20;i>0;i--)
			{
				len_l = len_r;
				len_mid = MyLine(PlantLine[i],PlantLine[i+1]).Dis_PointToLine(PlantLine[PlantLineNum]);
				len_r = PlantLine[PlantLineNum].Dis_PointToPoint(PlantLine[i]);
				if( (len_mid < len_l && len_mid < len_r) || (len_mid > len_l && len_mid > len_r) )
				{
					l_pointToLine = len_l < len_r ? len_l : len_r;
				}
				else
				{
					l_pointToLine = len_mid;
				}
				if(l_pointToLine < LEN && l_pointToLine < min_oneToLine)
				{
					min_oneToLine = l_pointToLine;
					temp1 = i;
					temp2 = PlantLineNum;
				}
			}
		}
	}
	else
	{
		CCLog("�����㶼û��Ҳ����ң�!!\n");
	}

	if(min_cross_point_len == inf && min_oneToLine == inf)
	{
		close1 = close2 = -1;
	}
	else
	{
		close1 = temp1 > temp2 ? temp2 : temp1;
		close2 = temp2 > temp1 ? temp2 : temp1;
	}
}

/************************************************************************/
/*����PlantLine�� ���ƽ������                                          */
/************************************************************************/
float HelloWorld:: Cal_k()
{
	int i;
	float temp = 0;
	for (i=1;i < PlantLineNum ;i++)
	{
		temp += PlantLine[i].Dis_PointToPoint(PlantLine[i+1]);
	}
	return (temp / PlantLineNum);
}

void HelloWorld::PushCricle(float _x,float _y,float _r)
{
	float i;
	MyPoint *pointrtemp;
	float C = 2 * _r * PI; 
	//������Լ1/10�Ĵ�С,����֮�����������λ��
	int num_star = int(C / 30.0);
	float temp = 360.0 / num_star;
	for (i=0;i<(360);i+=temp)
	{
		pointrtemp= new MyPoint(_x + cos((i)/180.0 * PI) * _r,_y + sin((i)/180.0 * PI) * _r);
		StarSpriteUp(makeStarSprite(pointrtemp->x,pointrtemp->y));

		temp_score ++;
	}
}
void HelloWorld::PushLine(float _x1,float _y1,float _x2, float _y2,const float len)
{
	if( MyPoint(_x1,_y1).Dis_PointToPoint( MyPoint(_x2,_y2)) > (len * 2) )
	{
		MyPoint *pointrtemp;

		pointrtemp= new MyPoint((_x1 + _x2)/2,(_y1 + _y2)/2);

		StarSpriteUp(makeStarSprite(pointrtemp->x,pointrtemp->y));

		temp_score ++;

		PushLine(_x1,_y1,pointrtemp->x,pointrtemp->y,len);
		PushLine(_x2,_y2,pointrtemp->x,pointrtemp->y,len);
	}
}
void HelloWorld::PushFourPoint(float _x1,float _y1,float _x2,float _y2,float _x3,float _y3,float _x4,float _y4)
{
	PushLine(_x1,_y1,_x2,_y2,22.0f);
	PushLine(_x2,_y2,_x3,_y3,22.0f);
	PushLine(_x3,_y3,_x4,_y4,22.0f);
	PushLine(_x4,_y4,_x1,_y1,22.0f);
}
void HelloWorld::PushThreePoint(float _x1,float _y1,float _x2,float _y2,float _x3,float _y3)
{
	PushLine(_x1,_y1,_x2,_y2,22.0f);
	PushLine(_x2,_y2,_x3,_y3,22.0f);
	PushLine(_x3,_y3,_x1,_y1,22.0f);
}

