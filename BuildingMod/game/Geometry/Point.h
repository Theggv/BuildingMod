#ifndef _UTILITY_GEOMETRY_POINT_H_
#define _UTILITY_GEOMETRY_POINT_H_

#include <pch.h>

class Edge;

enum { LEFT, RIGHT, BEYOND, BEHIND, BETWEEN, ORIGIN, DESTINATION };
//    СЛЕВА, СПРАВА, ВПЕРЕДИ, ПОЗАДИ, МЕЖДУ,   НАЧАЛО, КОНЕЦ

class Point
{
public:
	double x, y;

	Point(double _x = 0.0, double _y = 0.0);

	Point operator+(Point&);
	Point operator-(Point&);
	friend Point operator* (double, Point&);

	// возвращает координату х, если в качестве индекса
	// координаты указано значение О, или координату у при индексе 1
	double operator[] (int);

	// одинаковы ли точки ?
	int operator== (Point&);
	int operator!= (Point&);

	// лексикографический порядок отношений, точка а < точки b,
	// если либо а.х < b.х, либо a.х = b.x и а.у < b.у.  
	int operator< (Point&);
	int operator> (Point&);

	// Возвращается значение типа перечисления, указывающее на положение
	// точки относительно отрезка
	// enum {LEFT,  RIGHT,  BEYOND,  BEHIND, BETWEEN, ORIGIN, DESTINATION};
	//       СЛЕВА, СПРАВА, ВПЕРЕДИ, ПОЗАДИ, МЕЖДУ,   НАЧАЛО, КОНЕЦ
	int classify(Point&, Point&);
	int classify(Edge&);  // ребро вместо пары точек

	// Угол точки в полярной системе координат
	// возвращает -1, если точка = (0, 0)
	double polarAngle(void);

	double length(void);

	double distance(Edge&);
};

#endif // !_UTILITY_GEOMETRY_POINT_H_
