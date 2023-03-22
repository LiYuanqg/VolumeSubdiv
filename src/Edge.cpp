#include "Edge.h"

Edge::Edge(EdgeKey ek)
{
    assert(ek.first->idx() < ek.second->idx());
    ev[0] = ek.first;
    ev[1] = ek.second;
}

Face *Edge::add_face(Face *f)
{
    l_ef.push_back(f);
    return f;
}

Cell *Edge::add_cell(Cell *c)
{
    l_ec.push_back(c);
    return c;
}
