#include "Mesh.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cassert>

int Mesh::update_vid(int _vid)
{
    if (_vid > vid)
        vid = 1 + _vid;
    else
        vid++;
    return vid;
}
int Mesh::update_fid(int _fid)
{
    if (_fid > fid)
        fid = 1 + _fid;
    else
        fid++;
    return fid;
}
int Mesh::update_cid(int _cid)
{
    if (_cid > cid)
        cid = 1 + _cid;
    else
        cid++;
    return cid;
}

Vertex *Mesh::add_vertex(int vid)
{
    if (m_int_v.count(vid) != 0)
        return m_int_v[vid];
    Vertex *v = new Vertex(vid);
    update_vid(vid);
    l_v.push_back(v);
    m_int_v[vid] = v;
    return v;
}

Edge *Mesh::add_edge(Vertex *v1, Vertex *v2)
{
    if (v1->idx() > v2->idx())
    { // 确保v1的id小于v2的id
        Vertex *temp = v2;
        v2 = v1;
        v1 = temp;
    }

    EdgeKey ek(v1, v2);
    if (m_ek_e.count(ek) != 0) // 这条边已经存在
        return m_ek_e[ek];

    Edge *e = new Edge(ek);
    l_e.push_back(e);
    m_ek_e[ek] = e;
    v1->add_edge(e);
    v2->add_edge(e);

    return e;
}

Face *Mesh::add_face(std::vector<Vertex *> &vertices, int fid)
{
    if (m_int_f.count(fid) != 0)
        return m_int_f[fid];
    Face *f = new Face(fid);
    update_fid(fid);
    f->Valence() = vertices.size();
    for (int i = 0; i < vertices.size(); ++i)
    {
        Vertex *v1 = vertices[i];
        Vertex *v2 = vertices[(i + 1) % vertices.size()];
        Edge *e = add_edge(v1, v2);
        f->add_vertex(v1);
        f->add_vertex(v2);
        f->add_edge(e);
        e->add_face(f);
    }
    l_f.push_back(f);
    m_int_f.insert(std::pair<int, Face *>(fid, f)); // m_int_f[id]=f;
    return f;
}

Face *Mesh::add_face(std::vector<int> &num_of_vertices, int fid)
{
    if (m_int_f.count(fid) != 0)
        return m_int_f[fid];
    std::vector<Vertex *> vertices;
    for (int i = 0; i < num_of_vertices.size(); ++i)
    {
        Vertex *v = add_vertex(num_of_vertices[i]);
        vertices.push_back(v);
    }
    Face *f = add_face(vertices, fid);
    return f;
}

Cell *Mesh::add_cell(std::vector<Face *> &faces, int cid)
{
    if (m_int_c.count(cid) != 0)
        return m_int_c[cid];
    Cell *c = new Cell(cid);
    update_cid(cid);
    int valence = faces.size();
    c->Valence() = valence;
    for (int i = 0; i < c->Valence(); ++i)
    {
        Face *f = faces[i];
        c->add_face(f);
        f->add_cell(c);
        for (auto it = f->fv()->begin(); it != f->fv()->end(); ++it)
        {
            (*it)->add_cell(c);
        }
        for (auto it = f->fe()->begin(); it != f->fe()->end(); ++it)
        {
            (*it)->add_cell(c);
        }
    }
    l_c.push_back(c);
    return c;
}

Cell *Mesh::add_cell(std::vector<int> &num_of_faces, int cid)
{
    std::vector<Face *> faces;
    for (int i = 0; i < num_of_faces.size(); ++i)
    {
        assert(m_int_f.count(num_of_faces[i]) != 0); // 这个面一定要存在
        Face *f = m_int_f[num_of_faces[i]];
        faces.push_back(f);
    }
    Cell *c = add_cell(faces, cid);
    return c;
}

Cell *Mesh::createHexFromEightVertex(std::vector<Vertex *> vertices, int cid)
{
    assert(vertices.size() == 8);
    // 从8个点中选取4个点组成一个面
    std::vector<Vertex *> four_vertices;
    four_vertices.push_back(vertices[0]);
    four_vertices.push_back(vertices[1]);
    four_vertices.push_back(vertices[2]);
    four_vertices.push_back(vertices[3]);
    Face *bottom_face = add_face(four_vertices,next_fid());

    four_vertices.clear();
    four_vertices.push_back(vertices[4]);
    four_vertices.push_back(vertices[5]);
    four_vertices.push_back(vertices[6]);
    four_vertices.push_back(vertices[7]);
    Face *top_face=add_face(four_vertices,next_fid());

    four_vertices.clear();
    four_vertices.push_back(vertices[1]);
    four_vertices.push_back(vertices[5]);
    four_vertices.push_back(vertices[2]);
    four_vertices.push_back(vertices[6]);
    Face *front_face=add_face(four_vertices,next_fid());

    four_vertices.clear();
    four_vertices.push_back(vertices[7]);
    four_vertices.push_back(vertices[4]);
    four_vertices.push_back(vertices[0]);
    four_vertices.push_back(vertices[3]);
    Face *back_face=add_face(four_vertices,next_fid());

    four_vertices.clear();
    four_vertices.push_back(vertices[0]);
    four_vertices.push_back(vertices[4]);
    four_vertices.push_back(vertices[5]);
    four_vertices.push_back(vertices[1]);
    Face *left_face=add_face(four_vertices,next_fid());

    four_vertices.clear();
    four_vertices.push_back(vertices[6]);
    four_vertices.push_back(vertices[7]);
    four_vertices.push_back(vertices[3]);
    four_vertices.push_back(vertices[2]);
    Face *top_face=add_face(four_vertices,next_fid());
}

Mesh *Mesh::create_mesh(std::vector<Face *> faces)
{
}

Mesh *Mesh::read_mesh(const std::string &path)
{
    std::ifstream fin;
    fin.open(path, std::ios::in);
    if (!fin.is_open())
    {
        std::cerr << "cannot open the file..." << std::endl;
    }

    char line[102] = {0};
    char seps[] = " ,\t\n";
    int vid = 1;
    int fid = 1;
    int cid = 1;
    while (fin.getline(line, sizeof(line)))
    {
        char *token = strtok(line, seps);
        if (token == NULL)
            continue;
        if (strcmp(token, "v") == 0)
        {
            token = strtok(NULL, seps);
            double x = atof(token);
            token = strtok(NULL, seps);
            double y = atof(token);
            token = strtok(NULL, seps);
            double z = atof(token);
            Vertex *v = add_vertex(vid++);
            v->modify_point(x, y, z);
        }
        else if (strcmp(token, "f") == 0)
        {
            std::vector<int> num_of_vertices;
            while (token = strtok(NULL, seps))
            {
                num_of_vertices.push_back(atoi(token));
            }
            Face *f = add_face(num_of_vertices, fid++);
        }
        else if (strcmp(token, "c") == 0)
        {
            std::vector<int> num_of_faces;
            while (token = strtok(NULL, seps))
            {
                num_of_faces.push_back(atoi(token));
            }
            Cell *c = add_cell(num_of_faces, cid++);
        }
    }
}