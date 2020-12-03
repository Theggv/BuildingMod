#include "Polygon.h"
#include "Point.h"
#include "Edge.h"
#include "Vertex.h"

CPolygon::CPolygon(void) :
    _v(NULL), _size(0)
{
}

CPolygon::CPolygon(CPolygon& p) {
    _size = p._size;
    if (_size == 0)
        _v = NULL;
    else {
        _v = new Vertex(p.point());
        for (int i = 1; i < _size; i++) {
            p.advance(CLOCKWISE);
            _v = _v->insert(new Vertex(p.point()));
        }
        p.advance(CLOCKWISE);
        _v = _v->cw();
    }
}

CPolygon::CPolygon(Vertex* v) :
    _v(v)
{
    resize();
}

CPolygon::CPolygon(std::vector<Point> points)
{
    _size = points.size();

    if (_size == 0)
        _v = NULL;
    else
    {
        _v = new Vertex(points[0]);

        for (int i = 1; i < _size; ++i)
        {
            _v = _v->insert(new Vertex(points[1]));
        }

        _v = _v->cw();
    }
}

void CPolygon::resize(void)
{
    if (_v == NULL)
        _size = 0;
    else {
        Vertex* v = _v->cw();
        for (_size = 1; v != _v; ++_size, v = v->cw());
    }
}

CPolygon::~CPolygon(void)
{
    if (_v) {
        Vertex* w = _v->cw();
        while (_v != w) {
            delete w->remove();
            w = _v->cw();
        }
        delete _v;
    }
}

Vertex* CPolygon::v(void)
{
    return _v;
}

int CPolygon::size(void)
{
    return _size;
}

Point CPolygon::point(void)
{
    return _v->point();
}

Edge CPolygon::edge(void)
{
    return Edge(point(), _v->cw()->point());
}

Vertex* CPolygon::cw(void)
{
    return _v->cw();
}

Vertex* CPolygon::ccw(void)
{
    return _v->ccw();
}

Vertex* CPolygon::neighbor(int rotation)
{
    return _v->neighbor(rotation);
}

Vertex* CPolygon::advance(int rotation)
{
    return _v = _v->neighbor(rotation);
}

Vertex* CPolygon::setV(Vertex* v)
{
    return _v = v;
}

Vertex* CPolygon::insert(Point& p)
{
    if (_size++ == 0)
        _v = new Vertex(p);
    else
        _v = _v->insert(new Vertex(p));
    return _v;
}

void CPolygon::remove(void)
{
    Vertex* v = _v;
    _v = (--_size == 0) ? NULL : _v->ccw();
    delete v->remove();
}

CPolygon* CPolygon::split(Vertex* b)
{
    Vertex* bp = _v->split(b);
    resize();
    return new CPolygon(bp);
}

bool pointInConvexPolygon(Point& s, CPolygon& p)
{
    if (p.size() == 1)
        return (s == p.point());
    if (p.size() == 2) {
        int c = s.classify(p.edge());
        return ((c == BETWEEN) || (c == ORIGIN) || (c == DESTINATION));
    }
    Vertex* org = p.v();
    for (int i = 0; i < p.size(); i++, p.advance(CLOCKWISE))
        if (s.classify(p.edge()) == LEFT) {
            p.setV(org);
            return FALSE;
        }
    return TRUE;
}

Vertex* leastVertex(CPolygon& p, int (*cmp)(Point*, Point*))
{
    Vertex* bestV = p.v();
    p.advance(CLOCKWISE);
    for (int i = 1; i < p.size(); p.advance(CLOCKWISE), i++)
        if ((*cmp)(p.v(), bestV) < 0)
            bestV = p.v();
    p.setV(bestV);
    return bestV;
}

int leftToRightCmp(Point* a, Point* b)
{
    if (*a < *b) return -1;
    if (*a > * b) return 1;
    return 0;
}

int rightToLeftCmp(Point* a, Point* b)
{
    return leftToRightCmp(b, a);
}

