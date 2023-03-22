#ifndef _VERTEX_H_
#define _VERTEX_H_

#include <list>
#include <iterator>
#include "Edge.h"
#include "Face.h"
#include "Cell.h"

class Edge;
class Face;
class Cell;

class Vertex
{
private:
    double point[3];
    int id;
    bool boundary = false;
    std::list<Edge *> l_ve;
    std::list<Face *> l_vf;
    std::list<Cell *> l_vc;
    Vertex* VertexPoint;

public:
    Vertex();
    Vertex(int _id) : id(_id) { Vertex();}
    Vertex(double x, double y, double z, int _id);
    //~Vertex();

    /// @brief modifying the coordinates of the point.
    void modify_point(double x, double y, double z);

    int &idx() { return id; }
    Edge *add_edge(Edge *e){l_ve.push_back(e);return e;}
    Face *add_face(Face *f){l_vf.push_back(f);return f;}
    Cell *add_cell(Cell *c){l_vc.push_back(c);return c;}

    double x(){return point[0];}
    double y(){return point[1];}
    double z(){return point[2];}

    std::list<Edge *>* ve(){return &l_ve;}
    std::list<Face *>* vf(){return &l_vf;}
    std::list<Cell *>* vc(){return &l_vc;}

    void setVertexPoint(Vertex* v){VertexPoint=v;}
    Vertex* getVertexPoint(){return VertexPoint;}
};

#endif