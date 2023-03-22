#include "Mesh.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <cstring>
#include <cstdlib>

Vertex *Mesh::add_vertex(int id)
{
    if (m_int_v.count(id) != 0)
        return m_int_v[id];
    Vertex *v = new Vertex(id);
    l_v.push_back(v);
    m_int_v[id] = v;
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

Face *Mesh::add_face(std::vector<int> &num_of_vertices, int id)
{
    if (m_int_f.count(id) != 0)
        return m_int_f[id];
    Face *f = new Face(id);
    int valence = num_of_vertices.size(); // 面f的价（即面f关联的边）
    f->Valence() = valence;
    for (int i = 0; i < valence; ++i)
    {
        Vertex *v1 = add_vertex(num_of_vertices[i]);
        Vertex *v2 = add_vertex(num_of_vertices[(i + 1) % valence]);
        Edge *e = add_edge(v1, v2);
        f->add_vertex(v1);
        f->add_vertex(v2);
        f->add_edge(e);
        e->add_face(f);
    }
    l_f.push_back(f);
    m_int_f.insert(std::pair<int, Face *>(id, f)); // m_int_f[id]=f;
    return f;
}

Mesh *Mesh::create_mesh(std::vector<Face*> faces){
    
}

Cell *Mesh::add_cell(std::vector<int> &num_of_faces, int id)
{
    Cell *c = new Cell(id);
    int valence = num_of_faces.size();
    c->Valence() = valence;
    for (int i = 0; i < valence; ++i)
    {
        assert(m_int_f.count(num_of_faces[i]) != 0); // 这个面一定要存在
        Face *f = m_int_f[num_of_faces[i]];
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

Mesh *Mesh::create_mesh(const std::string &path)
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
        if (strcmp(token, "v")==0)
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