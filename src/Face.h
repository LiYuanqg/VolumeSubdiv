#ifndef _FACE_H_
#define _FACE_H_

#include <list>
#include <cassert>
#include "Edge.h"
#include "Cell.h"
#include "Vertex.h"

class Edge;
class Cell;
class Vertex;

class Face
{
private:
    int id;
    int valence = 0;
    //bool boundary = false;

    std::list<Vertex *> l_fv;
    std::list<Edge *> l_fe;
    Cell *fc[2];

    Vertex* FacePoint;

public:
    // Face();
    Face(int _id) : id(_id)
    {
        fc[0] = nullptr;
        fc[1] = nullptr;
    }

    int &Valence() { return valence; }

    Vertex *add_vertex(Vertex *v){l_fv.push_back(v);return v;}
    Edge *add_edge(Edge *e){l_fe.push_back(e);return e;}
    Cell *add_cell(Cell *c);

    Cell* cell_1(){return fc[0];}
    Cell* cell_2(){return fc[1];}
    bool boundary(){return !(fc[0]&&fc[1]);}
    int idx(){return id;}

    std::list<Vertex *>* fv(){return &l_fv;}
    std::list<Edge *>* fe(){return &l_fe;}

    Vertex* setFacePoint();
    Vertex* getFacePoint(){return FacePoint;}
};

#endif