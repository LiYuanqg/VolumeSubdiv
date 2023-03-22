#ifndef _CELL_H_
#define _CELL_H_

#include <list>
#include <iterator>
#include "Edge.h"
#include "Face.h"

#include "Vertex.h"

class Edge;
class Face;
class Vertex;

class Cell
{
private:
    int id;
    int valence = 0;
    bool boundary = false;
    std::list<Vertex *> l_cv;
    std::list<Edge *> l_ce;
    std::list<Face *> l_cf;

    // Vertex* CellPoint;

public:
    Cell(int _id) : id(_id) {}

    int &Valence() { return valence; }
    int idx() { return id; }

    Vertex *add_vertex(Vertex *v){l_cv.push_back(v);return v;}
    Edge *add_edge(Edge *e){l_ce.push_back(e);return e;}
    Face *add_face(Face *f){l_cf.push_back(f);return f;}

    std::list<Vertex *> *cv() { return &l_cv; }
    std::list<Edge *> *ce() { return &l_ce; }
    std::list<Face *> *cf() { return &l_cf; }
};

#endif