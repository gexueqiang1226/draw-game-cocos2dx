#ifndef __GEOMETRY_H__
#define __GEOMETRY_H__

const float inf = 1000000000;
const float PI = 3.1415926;
const int POINT_LEFTofLINE  = 1;
const int POINT_ONthefLINE  = 0;
const int POINT_RIGHTofLINE = -1;

class MyPoint
{
public:
	float x;
	float y;
	int distime;
	float v_x , ax;
	float v_y , ay;
public:
	MyPoint(float _x = 0.0,float _y = 0.0,float _v_x = 0.0f,float _v_y = 0.0f, int _distime = 0 ,float _ax =0.0 ,float _ay =0.0)
	{x = _x; y = _y;v_x = _v_x;v_y  =_v_y;distime = _distime; ax = _ax; ay = _ay;}
	virtual ~MyPoint(void);
public:
	bool isExist();
	float Dis_PointToPoint(MyPoint temp);
	void Update()
	{
		if(distime > 0)
		{
			x += v_x;
			y += v_y;
			distime--;
			v_x += ax;
			v_y += ay;
		}
		else
		{
			distime++;
		}
		
	}
};

class MyLine
{
public:
	MyPoint A;
	MyPoint B;
public:
	MyLine(float _Ax,float _Ay,float _Bx,float _By);
	MyLine(MyPoint , MyPoint);
public:
	bool isPointInLine(MyPoint A);
	float Dis_PointToLine(MyPoint temp);
};


//两线叉乘
float XMultiply(MyLine AB , MyLine CD);

//判断两线是否相交
MyPoint isCross(MyLine AB , MyLine CD);

//两直线夹角
float AngleofLines(MyLine AB , MyLine CD);

//给点排序 排成逆时针序
void SortPoint(MyPoint MP[] , int numPoint);

//点与线的位置关系
int PointofLine(MyPoint tempPoint,MyLine tempLine);


#endif  // __GEOMETRY_H__