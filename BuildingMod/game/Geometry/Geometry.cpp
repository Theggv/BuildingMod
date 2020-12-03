#include "Geometry.h"
#include "Vertex.h"
#include "Edge.h"

int edgeType(Point& a, Edge& e)
{
    Point v = e.org;
    Point w = e.dest;
    switch (a.classify(e)) {
    case LEFT:
        return ((v.y < a.y) && (a.y <= w.y)) ? CROSSING : INESSENTIAL;
    case RIGHT:
        return ((w.y < a.y) && (a.y <= v.y)) ? CROSSING : INESSENTIAL;
    case BETWEEN:
    case ORIGIN:
    case DESTINATION:
        return TOUCHING;
    default:
        return INESSENTIAL;
    }
}

int Geometry::PointInPolygon(Point& a, CPolygon& p)
{
    int parity = 0;
    for (int i = 0; i < p.size(); i++, p.advance(CLOCKWISE)) {
        Edge e = p.edge();
        switch (edgeType(a, e)) {
        case TOUCHING:
            return BOUNDARY;
        case CROSSING:
            parity = 1 - parity;
        }
    }
    return (parity ? INSIDE : OUTSIDE);
}
