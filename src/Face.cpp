#include "Face.h"

Cell *Face::add_cell(Cell *c)
{
    if (fc[0] == nullptr)
        fc[0] = c;
    else
    {
        assert(fc[1] == nullptr); // 一个face最多关联两个cell
        if (c->idx() > fc[0]->idx())
            fc[1] = c;
        else
        {
            fc[1] = fc[0];
            fc[0] = c;
        }
    }
    return c;
}
