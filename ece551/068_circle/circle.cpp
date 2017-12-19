
#include<cstdio>
#include<cstdlib>
#include"circle.h"
#include<math.h>



Circle::Circle(Point p, double r):center(p),radius(r){}


 

void Circle::move(double dx,double dy){
  center.move(dx,dy);
}
double Circle::intersectionArea(const Circle & otherCircle){
  const Point &p=otherCircle.center;
  double centerdistance=this->center.distanceFrom(p);
  //double halfdistance=centerdistance/2;
  double max_radius;
  double min_radius;
  if(this->radius>otherCircle.radius){
    min_radius=otherCircle.radius;
    max_radius=this->radius;
  }
  else{
    min_radius=this->radius;
    max_radius=otherCircle.radius;
  }
  //fprintf(stdout,"%f\n",centerdistance);
  //fpritnf(stdout,"%f\n",max_radius);
  //fprintf(stdout,"%f\n",min_radius);
  if((centerdistance==0) && (this->radius==otherCircle.radius)){
    return 3.14*this->radius*this->radius;
  }
  if((centerdistance>(max_radius-min_radius))&&(centerdistance<(max_radius+min_radius))){
    double halfalpha=acos((max_radius*max_radius+centerdistance*centerdistance-min_radius*min_radius)/(2*max_radius*centerdistance));
    double alpha=halfalpha*2;
    double cir_area=alpha*max_radius*max_radius/2;
    double halfalpha1=acos((min_radius*min_radius+centerdistance*centerdistance-max_radius*max_radius)/(2*min_radius*centerdistance));
    double alpha1=halfalpha1*2;
    double cir_area1=alpha1*(min_radius)*(min_radius)/2;
    double trian_area=min_radius*centerdistance*sin(halfalpha1);
    return (cir_area+cir_area1-trian_area);
  }
  
  else if(centerdistance<=max_radius-min_radius){
      return 3.14*min_radius*min_radius;
  }
  else if((this->radius==0)||(otherCircle.radius==0)){
    return 0;
  }
  else{
    return 0;
  }
}
