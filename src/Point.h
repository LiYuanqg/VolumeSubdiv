#ifndef _POINT_H_
#define _POINT_H_

class Point{
private:
    double x,y,z;
public:
    Point(){};
    Point(double _x, double _y, double _z):x(_x),y(_y),z(_z){}
    double &X(){return x;}
    double &Y(){return y;}
    double &Z(){return z;}
};

#endif