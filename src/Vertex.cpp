#include "Vertex.h"


Vertex::Vertex(/* args */)
{
    point[0] = point[1] = point[2] = 0.0;
}
Vertex::Vertex(double x, double y, double z, int _id)
{
    point[0] = x;
    point[1] = y;
    point[2] = z;
    id = _id;
}

void Vertex::modify_point(double x, double y, double z)
{
    point[0] = x;
    point[1] = y;
    point[2] = z;
}
