#include <math.h>
#include "geometry.h"

MyPoint ::~MyPoint(void)
{

}

bool MyPoint :: isExist()
{
	if(x == inf && y == inf)
		return false;
	else
		return true;
}

float MyPoint :: Dis_PointToPoint(MyPoint temp)
{
	float ans;
	ans = sqrt( (temp.x - this->x)*(temp.x - this->x) + (temp.y - this->y)*(temp.y - this->y));
	return ans;
}

MyLine ::~MyLine(void)
{

}

MyLine :: MyLine(MyPoint AA , MyPoint BB)
{
	A = AA ; B = BB;
}

MyLine :: MyLine(float _Ax = 0.0 ,float _Ay = 0.0,float _Bx = 0.0 ,float _By = 0.0)
{
	A.x = _Ax; A.y = _Ay;
	B.x = _Bx; B.y = _By;
}

/************************************************************************/
/*有可能 A在左上B在右下 或者 A在左下B在右上 或者......                  */
/*也就是 t的x可能在AB的x中间 也可能在BA的x中间 y同理					*/
/************************************************************************/
bool MyLine :: isPointInLine(MyPoint t)
{
	if ( ( (this->A.x <= t.x && t.x <= this->B.x)||(this->B.x <= t.x && t.x <= this->A.x) ) 
	&&   ( (this->A.y <= t.y && t.y <= this->B.y)||(this->B.y <= t.y && t.y <= this->A.y) ) )
	{
		return true;
	}
	else
	{
		return false;
	}
}

/************************************************************************/
/* 点到线的距离                                                         */
/************************************************************************/
float MyLine :: Dis_PointToLine(MyPoint temp)
{
	MyPoint mid;
	mid.x = (temp.x + temp.x + this->A.y - this->B.y)/2;
	mid.y = (temp.y + temp.y + this->B.x - this->A.x)/2;
	return mid.Dis_PointToPoint(temp);
}

/************************************************************************/
/* 两条线叉积                                                           */
/************************************************************************/
float XMultiply(MyLine AB , MyLine CD)
{
	float AB_x = AB.B.x - AB.A.x;
	float AB_y = AB.B.y - AB.A.y;
	float CD_x = CD.B.x - CD.A.x;
	float CD_y = CD.B.y - CD.A.y;

	return (AB_x * CD_y)-(AB_y * CD_x);
}

/************************************************************************/
/*两线交点
/*原理：
/*设有直线AB和CD，求交点P
/*令t = ( AC × CD )/( AB× CD ) 
/*囧了，这里要判断AB×CD是否为0，为0就是平衡或者共线
/*P.x = A.x - (A.x-B.x)*t;
/*P.y = A.y - (A.y-B.y)*t;                                                              
/************************************************************************/
MyPoint isCross(MyLine AB , MyLine CD)
{	
	MyPoint temp;
	float AB_CD = (XMultiply(MyLine(AB.A,AB.B),MyLine(CD.A,CD.B)));
	if(AB_CD != 0)
	{
		float t = ( (XMultiply(MyLine(AB.A,CD.A),MyLine(CD.A,CD.B))) /  AB_CD);
		temp.x = AB.A.x - (AB.A.x - AB.B.x) * t;
		temp.y = AB.A.y - (AB.A.y - AB.B.y) * t;
		if(AB.isPointInLine(temp) && CD.isPointInLine(temp))
		{
			//返回交点temp
			return temp;
		}
		else
		{
			//没有交点，返回一个好远的点，远死了-，-
			return MyPoint(inf,inf);
		}	
	}
	else
	{
		//感觉这个程序没有平衡等其他问题，暂时不处理
		return MyPoint(inf,inf);
	}
}

/************************************************************************/
/* 两线夹角                                                             */
/************************************************************************/
float AngleofLines(MyLine AB , MyLine CD)
{
	//本来是要处理 是否相交的，但是点是自己给的，必然相交，特殊情况暂时不处理
	//cos<AB,CD> = (AB·CD)/(|AB|*|CD|)
	float cos_AB_CD = ( (AB.B.x-AB.A.x)*(CD.B.x - CD.A.x) + (AB.B.y - AB.A.y)*(CD.B.y - CD.A.y) )/(AB.A.Dis_PointToPoint(AB.B) * CD.A.Dis_PointToPoint(CD.B));
	float angle = acos(cos_AB_CD);
	return (angle / PI ) * 180.0; //返回角度

	/*
	if(isCross(AB,CD).isExist() == true)
	{
	//cos<AB,CD> = (AB·CD)/(|AB|*|CD|)
	float cos_AB_CD = ( (AB.B.x-AB.A.x)*(CD.B.x - CD.A.x) + (AB.B.y - AB.A.y)*(CD.B.y - CD.A.y) )/(AB.A.Dis_PointToPoint(AB.B) * CD.A.Dis_PointToPoint(CD.B));
	float angle = acos(cos_AB_CD);
	return (angle / PI ) * 180.0; //返回角度
	}
	else
	{
	//不相交 就返回很大的角度
	return inf;
	}
	*/
}
/************************************************************************/
/*给点逆时针排序				                                        */
/************************************************************************/
void SortPoint(MyPoint MP[] , int numPoint)
{
	int tempindex=0;
	float temp;
	MyPoint tempPoint(inf,inf);
	 //先找出最下点，高度一样就要左边的
	for(int i = 0; i < numPoint ; i++)
	{
		if(MP[i].y < tempPoint.y)
		{
			tempindex = i;
			tempPoint = MP[i];
		}
		else if( fabs(tempPoint.y - MP[i].y) < 1e-6)
		{
			if (MP[i].x < tempPoint.x)
			{
				tempindex = i;
				tempPoint = MP[i];
			}
		}
	}
	//左下点放到下标为0处
	MP[tempindex] = MP[0];
	MP[0] = tempPoint;
	//后面的按角度排序
	float angle[10]; // 记录角度
	for(int i = 1 ; i < numPoint ; i++)
	{
		//<0，MP[i]>向量和x轴夹角
		angle[i] = AngleofLines( MyLine(MP[0],MP[i]) , MyLine(MP[0],MyPoint(MP[0].x+1,MP[0].y)));
	}
	//冒泡排序
	for(int i = 0 ; i < (numPoint-1) ; i++)
	{
		for(int j = 1 ; j < (numPoint-1) ; j++)
		{
			if(angle[j] > angle[j+1])
			{
				temp = angle[j]; angle[j] = angle[j+1]; angle[j+1] = temp;
				tempPoint = MP[j];
				MP[j] = MP[j+1];
				MP[j+1] = tempPoint;
			}
			else if( fabs(angle[j] - angle[j+1]) < 1e-6 && MP[j].Dis_PointToPoint(MP[0]) > MP[j+1].Dis_PointToPoint(MP[0]) )
			{
				temp = angle[j]; angle[j] = angle[j+1]; angle[j+1] = temp;
				tempPoint = MP[j];
				MP[j] = MP[j+1];
				MP[j+1] = tempPoint;
			}
		}
	}
}
/************************************************************************/
/* 点与线的位置关系		                                                */
/*POINT_RIGHTofLINE														*/
/*POINT_ONthefLINE														*/
/*POINT_LEFTofLINE														*/
/************************************************************************/
int PointofLine(MyPoint tempPoint,MyLine tempLine)
{
	float AP_XMultiply_AB = XMultiply( MyLine(tempLine.A,tempPoint) , tempLine);
	if(AP_XMultiply_AB > 0)
		return POINT_RIGHTofLINE;
	else if(AP_XMultiply_AB - 0 <1e-6)
		return POINT_ONthefLINE;
	else if(AP_XMultiply_AB < 0)
		return POINT_LEFTofLINE;
}
