#ifndef _UTILITY_GEOMETRY_POLYGON_H_
#define _UTILITY_GEOMETRY_POLYGON_H_

#include <pch.h>

class Point;
class Edge;
class Vertex;

class CPolygon
{
private:
	Vertex* _v;
	int _size;
	void resize(void);
public:
	CPolygon(void);
	CPolygon(CPolygon&);
	CPolygon(Vertex*);
	CPolygon(std::vector<Point> points);
	~CPolygon(void);
	Vertex* v(void);
	int size(void);
	Point point(void);
	Edge edge(void);
	Vertex* cw(void); // next clock-wise vertex
	Vertex* ccw(void); // next counter clock-wise vertex
	Vertex* neighbor(int rotation);
	Vertex* advance(int rotation);
	Vertex* setV(Vertex*);
	Vertex* insert(Point&);
	void remove(void);
	CPolygon* split(Vertex*);
};

#endif // !_UTILITY_GEOMETRY_POLYGON_H_
