#include <stdio.h>
#include "math.h"
#include "vector.h"
extern sphere_t *sphere[];
extern point_t *sol[];

extern unsigned char sphereCount;
extern unsigned char solCount;


float PointToPointDistance(point_t p1, point_t p2)
{
 return sqrt((p1.x - p2.x)*(p1.x-p2.x) + (p1.y-p2.y)*(p1.y-p2.y) + (p1.z-p2.z)*(p1.z-p2.z));

}
char LineIntersectsSphere(line_t *line, sphere_t *sphere, point_t* point)
{ 
  point_t p1;
  point_t p2;
  float x1 = line->p1.x;
  float x2 = line->p2.x;
  float x3 = sphere->center.x;
  float y1 = line->p1.y;
  float y2 = line->p2.y;
  float y3 = sphere->center.y;
  float z1 = line->p1.z;
  float z2 = line->p2.z;
  float z3 = sphere->center.z;
  float r = sphere->r;
  float a = (x2-x1)*(x2-x1) + (y2-y1)*(y2-y1) + (z2-z1)*(z2-z1);
  float b = 2*((x2-x1)*(x1-x3) + (y2-y1)*(y1-y3) + (z2-z1)*(z1-z3));
  float c = x3*x3 + y3*y3 + z3*z3 + x1*x1 + y1*y1 + z1*z1 - 2*(x3*x1 + y3*y1 + z3*z1) - r*r;
  if( (b*b-4*a*c) < 0)
  {
    return 0;
  }
  else // calculate the point of intersection(s) choose the point closer to the POV
  {
    float t1, t2;
    float px1, py1, pz1, px2, py2, pz2;
    t1 = (-b+sqrt( b*b - 4*a*c) ) / (2*a);
    t2 = (-b-sqrt( b*b - 4*a*c) ) / (2*a);
    p1.z  = z1 + t1*(z2 - z1);   
    p2.z  = z1 + t2*(z2 - z1);
    p1.y  = y1 + t1*(y2 - y1);
    p2.y  = y1 + t2*(y2 - y1);
    p1.x  = x1 + t1*(x2 - x1);
    p2.x  = x1 + t2*(x2 - x1); //theres gotta be an easier way


    if(PointToPointDistance(p1, line->p1) < PointToPointDistance(p2, line->p1))
    {
      *point = p1;
    }
    else
    {
      *point = p2;
    }
    return 1;
  } 
 }
sphere_t* Intersection(line_t *line)
{
  point_t p1;
  point_t p2;
  sphere_t *tmpSphere = NULL;
  int i;
  for(i = 0; i < sphereCount; i++)
  {  
    float x1 = line->p1.x;
    float x2 = line->p2.x;
    float x3 = sphere[i]->center.x;
    float y1 = line->p1.y;
    float y2 = line->p2.y;
    float y3 = sphere[i]->center.y;
    float z1 = line->p1.z;
    float z2 = line->p2.z;
    float z3 = sphere[i]->center.z;
    float r = sphere[i]->r;
    float a = (x2-x1)*(x2-x1) + (y2-y1)*(y2-y1) + (z2-z1)*(z2-z1);
    float b = 2*((x2-x1)*(x1-x3) + (y2-y1)*(y1-y3) + (z2-z1)*(z1-z3));
    float c = x3*x3 + y3*y3 + z3*z3 + x1*x1 + y1*y1 + z1*z1 - 2*(x3*x1 + y3*y1 + z3*z1) - r*r;
    if( (b*b-4*a*c) < 0)
    { 
      continue;
    }
    else // calculate the point of intersection(s) choose the point closer to the POV
    {
      float t1, t2;
      float px1, py1, pz1, px2, py2, pz2;
      t1 = (-b+sqrt( b*b - 4*a*c) ) / (2*a);
      t2 = (-b-sqrt( b*b - 4*a*c) ) / (2*a);
      p1.z  = z1 + t1*(z2 - z1);   
      p2.z  = z1 + t2*(z2 - z1);
      p1.y  = y1 + t1*(y2 - y1);
      p2.y  = y1 + t2*(y2 - y1);
      p1.x  = x1 + t1*(x2 - x1);
      p2.x  = x1 + t2*(x2 - x1); //theres gotta be an easier way


      if(PointToPointDistance(p1, line->p1) < PointToPointDistance(p2, line->p1))
      {
        sphere[i]->intersection = p1;
      }
      else
      {
        sphere[i]->intersection = p2;
      }
      tmpSphere = sphere[i];
      break;
    } 
  } 
  return tmpSphere; 
}
float cosalpha(vector_t p1, vector_t p2)
{
  return (p1.x*p2.x + p1.y*p2.y + p1.z*p2.z)/( sqrt(p1.x*p1.x + p1.y*p1.y + p1.z*p1.z)*sqrt(p2.x*p2.x + p2.y*p2.y + p2.z*p2.z) );
}
float dotproduct(vector_t v1, vector_t v2)
{
 return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
}
vector_t createunitvector(vector_t *v)
{
  vector_t vtmp;                                                   
                                                                        //  _________________                        
  float length = sqrt(v->x*v->x + v->y*v->y + v->y*v->y + v->z*v->z);   // V x^2 + y^2 + z^2 '
  vtmp.x = v->x/length; 
  vtmp.y = v->y/length;
  vtmp.z = v->z/length;

  return vtmp;
}
vector_t pointstovector(point_t *start, point_t *end)
{
  vector_t vtmp;
  vtmp.x = end->x - start->x;
  vtmp.y = end->y - start->y;
  vtmp.z = end->z - start->z;
  return vtmp;
}
vector_t scalartimesvector(float scalar, vector_t v)
{
  vector_t vtmp;
  vtmp.x = v.x * scalar;
  vtmp.y = v.y * scalar;
  vtmp.z = v.z * scalar;
  return vtmp;
}
vector_t vectorminusvector(vector_t v1, vector_t v2)
{
  vector_t vtmp;
  vtmp.x = v1.x - v2.x;
  vtmp.y = v1.y - v2.y;
  vtmp.z = v1.z - v2.z;
  return vtmp;
}
