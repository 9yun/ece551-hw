#include<cstdlib>
#include<cstdio>
#include<math.h>
#include"point.h"

Point::Point():x(0),y(0){}
void Point:: move(double dx,double dy){
  x+=dx;
  y+=dy;
}
double Point:: distanceFrom(const Point & p){
  double distance=sqrt((this->x-p.x)*(this->x-p.x)+(this->y-p.y)*(this->y-p.y));
  return distance;
}
