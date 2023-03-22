#ifndef _EDGE_H_
#define _EDGE_H_

#include <list>
#include <utility>
#include <cassert>

#include "Face.h"
#include "Cell.h"
#include "Vertex.h"

/// @brief 由两个点组成EdgeKey，规定第一个点的id小于第二个点
using EdgeKey = std::pair<Vertex *, Vertex *>;


class Cell;
class Face;
class Vertex;

class Edge
{
private:
    bool boundary = false;
    Vertex *ev[2]; // 一条边由两个点组成
    std::list<Face *> l_ef;
    std::list<Cell *> l_ec;

    Vertex *EdgePoint;

public:
    // Edge();
    Edge(EdgeKey ek);

    Vertex *vertex_1() { return ev[0]; }
    Vertex *vertex_2() { return ev[1]; }
    Face *add_face(Face *f);
    Cell *add_cell(Cell *c);

    std::list<Face *> *ef() { return &l_ef; }
    std::list<Cell *> *ec() { return &l_ec; }

    void setEdgePoint(Vertex *v){EdgePoint=v;}
    Vertex* getEdgePoint(){return EdgePoint;}
};

#endif