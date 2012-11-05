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
/*�п��� A������B������ ���� A������B������ ����......                  */
/*Ҳ���� t��x������AB��x�м� Ҳ������BA��x�м� yͬ��					*/
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
/* �㵽�ߵľ���                                                         */
/************************************************************************/
float MyLine :: Dis_PointToLine(MyPoint temp)
{
	MyPoint mid;
	mid.x = (temp.x + temp.x + this->A.y - this->B.y)/2;
	mid.y = (temp.y + temp.y + this->B.x - this->A.x)/2;
	return mid.Dis_PointToPoint(temp);
}

/************************************************************************/
/* �����߲��                                                           */
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
/*���߽���
/*ԭ��
/*����ֱ��AB��CD���󽻵�P
/*��t = ( AC �� CD )/( AB�� CD ) 
/*���ˣ�����Ҫ�ж�AB��CD�Ƿ�Ϊ0��Ϊ0����ƽ����߹���
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
			//���ؽ���temp
			return temp;
		}
		else
		{
			//û�н��㣬����һ����Զ�ĵ㣬Զ����-��-
			return MyPoint(inf,inf);
		}	
	}
	else
	{
		//�о��������û��ƽ����������⣬��ʱ������
		return MyPoint(inf,inf);
	}
}

/************************************************************************/
/* ���߼н�                                                             */
/************************************************************************/
float AngleofLines(MyLine AB , MyLine CD)
{
	//������Ҫ���� �Ƿ��ཻ�ģ����ǵ����Լ����ģ���Ȼ�ཻ�����������ʱ������
	//cos<AB,CD> = (AB��CD)/(|AB|*|CD|)
	float cos_AB_CD = ( (AB.B.x-AB.A.x)*(CD.B.x - CD.A.x) + (AB.B.y - AB.A.y)*(CD.B.y - CD.A.y) )/(AB.A.Dis_PointToPoint(AB.B) * CD.A.Dis_PointToPoint(CD.B));
	float angle = acos(cos_AB_CD);
	return (angle / PI ) * 180.0; //���ؽǶ�

	/*
	if(isCross(AB,CD).isExist() == true)
	{
	//cos<AB,CD> = (AB��CD)/(|AB|*|CD|)
	float cos_AB_CD = ( (AB.B.x-AB.A.x)*(CD.B.x - CD.A.x) + (AB.B.y - AB.A.y)*(CD.B.y - CD.A.y) )/(AB.A.Dis_PointToPoint(AB.B) * CD.A.Dis_PointToPoint(CD.B));
	float angle = acos(cos_AB_CD);
	return (angle / PI ) * 180.0; //���ؽǶ�
	}
	else
	{
	//���ཻ �ͷ��غܴ�ĽǶ�
	return inf;
	}
	*/
}
/************************************************************************/
/*������ʱ������				                                        */
/************************************************************************/
void SortPoint(MyPoint MP[] , int numPoint)
{
	int tempindex=0;
	float temp;
	MyPoint tempPoint(inf,inf);
	 //���ҳ����µ㣬�߶�һ����Ҫ��ߵ�
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
	//���µ�ŵ��±�Ϊ0��
	MP[tempindex] = MP[0];
	MP[0] = tempPoint;
	//����İ��Ƕ�����
	float angle[10]; // ��¼�Ƕ�
	for(int i = 1 ; i < numPoint ; i++)
	{
		//<0��MP[i]>������x��н�
		angle[i] = AngleofLines( MyLine(MP[0],MP[i]) , MyLine(MP[0],MyPoint(MP[0].x+1,MP[0].y)));
	}
	//ð������
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
/* �����ߵ�λ�ù�ϵ		                                                */
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
