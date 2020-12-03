#ifndef _UTILITY_GEOMETRY_POINT_H_
#define _UTILITY_GEOMETRY_POINT_H_

#include <pch.h>

class Edge;

enum { LEFT, RIGHT, BEYOND, BEHIND, BETWEEN, ORIGIN, DESTINATION };
//    �����, ������, �������, ������, �����,   ������, �����

class Point
{
public:
	double x, y;

	Point(double _x = 0.0, double _y = 0.0);

	Point operator+(Point&);
	Point operator-(Point&);
	friend Point operator* (double, Point&);

	// ���������� ���������� �, ���� � �������� �������
	// ���������� ������� �������� �, ��� ���������� � ��� ������� 1
	double operator[] (int);

	// ��������� �� ����� ?
	int operator== (Point&);
	int operator!= (Point&);

	// ������������������ ������� ���������, ����� � < ����� b,
	// ���� ���� �.� < b.�, ���� a.� = b.x � �.� < b.�.  
	int operator< (Point&);
	int operator> (Point&);

	// ������������ �������� ���� ������������, ����������� �� ���������
	// ����� ������������ �������
	// enum {LEFT,  RIGHT,  BEYOND,  BEHIND, BETWEEN, ORIGIN, DESTINATION};
	//       �����, ������, �������, ������, �����,   ������, �����
	int classify(Point&, Point&);
	int classify(Edge&);  // ����� ������ ���� �����

	// ���� ����� � �������� ������� ���������
	// ���������� -1, ���� ����� = (0, 0)
	double polarAngle(void);

	double length(void);

	double distance(Edge&);
};

#endif // !_UTILITY_GEOMETRY_POINT_H_
