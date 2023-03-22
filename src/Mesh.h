#ifndef _MESH_H_
#define _MESH_H_

#include <list>
#include <map>
#include <string>
#include <vector>
#include "Edge.h"
#include "Face.h"
#include "Cell.h"
#include "Vertex.h"

class Edge;
class Face;
class Cell;
class Vertex;
class Mesh
{
private:
    std::list<Vertex *> l_v;
    std::list<Edge *> l_e;
    std::list<Face *> l_f;
    std::list<Cell *> l_c;

    std::map<int, Vertex *> m_int_v;
    std::map<int, Face *> m_int_f;
    std::map<EdgeKey, Edge *> m_ek_e;

public:
    // Mesh();
    // ~Mesh();

    /// @brief 在mesh中加入一个新vertex
    /// @param id vertex的id
    /// @return 新加入的vertex的指针
    Vertex *add_vertex(int id);

    Edge *add_edge(Vertex *v1, Vertex *v2);

    Face *add_face(std::vector<int> &num_of_vertices, int id);
    //Face *add_face(std::vector<Vertex *> &vertices, int id);

    Cell *add_cell(std::vector<int> &num_of_faces, int id);

    /// @brief create a mesh from specific file
    /// @param path file path
    /// @return a mesh
    Mesh *create_mesh(const std::string &path);

    Mesh *create_mesh(std::vector<Face*> faces);
    Mesh *createHexFromEightVertex(std::vector<Vertex*> vertices);

    std::list<Vertex *> *vertices(){return &l_v;}
    std::list<Edge *> *edges(){return &l_e;}
    std::list<Face *> *faces(){return &l_f;}
    std::list<Cell *> *cells(){return &l_c;}
};

#endif