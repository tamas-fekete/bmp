#include <stdio.h>
#include <stdlib.h>
#include "vector.h"
#include "bmp.h"
#include "canvas.h"
#include <math.h>

#define MAX_RECURSION_DEPTH 3
#define NUMBER_OF_SPHERES 5
#define NUMBER_OF_SOLS 3
sphere_t *sphere[NUMBER_OF_SPHERES];
point_t *sol[NUMBER_OF_SOLS];
unsigned char sphereCount = 0;
unsigned char solCount = 0;

void putpixel(int x, int y, unsigned char red, unsigned char green, unsigned char blue);
color_t Trace(line_t *r, char recursionDepth);
float DiffuseReflection(sphere_t* Sphere, vector_t ray, vector_t sphereNormal);
float SpecularReflection(sphere_t* Sphere, vector_t ray, vector_t sphereNormal, point_t pov);
vector_t ReflectionVector(vector_t normal, vector_t incident);
float BlendColors(float a, float b, float t);

void AddSphere(float x, float y, float z, float r, unsigned char red, unsigned char green, unsigned char blue, double reflection)
{
  static char i = 0;

  if(i<NUMBER_OF_SPHERES)
  {
    sphere[i] = (sphere_t*) malloc(sizeof(sphere_t));
    sphere[i]->center.x = x;
    sphere[i]->center.y = y;
    sphere[i]->center.z = z;
    sphere[i]->r  = r;
    sphere[i]->color.red = red;
    sphere[i]->color.green = green;
    sphere[i]->color.blue = blue;
    sphere[i]->reflection = reflection;
    sphereCount = ++i;
  }
  else
  {
    printf("Too many spheres!\n");
  }
 }

 void AddSol(float x, float y, float z)
 {
  static char j = 0;
  if(j<NUMBER_OF_SOLS)
  {
    sol[j] = (point_t*)malloc(sizeof(point_t));
    sol[j]->x = x;
    sol[j]->y = y;
    sol[j]->z = z;
    solCount = ++j;
  }
  else
  {
    printf("Too many sols\n");
  }
 }

color_t Trace(line_t *r, char recursionDepth)
{
  color_t color = { 0xffu, 0xffu, 0xffu};
sphere_t localSphere;
  sphere_t *tmpSphere = &localSphere;
sphere_t dontCareSphere;
  int i;
  unsigned char sphereIntersected = 0;
  float DiffuseLight = 0.0f;
  float SpecularLight = 0.0f;
  vector_t ray;
  vector_t sphereUnitNormal;
  vector_t sphereNormal;

  if(recursionDepth > MAX_RECURSION_DEPTH){return color;}
  sphereIntersected = Intersection(r, tmpSphere); // check if ray intersects an object in the scene
  if(sphereIntersected == 0) // no intersection
  {
    color.red = 0xff;
    color.green = 0xff;
    color.blue = 0xff;
  }
  else
  {
    if(tmpSphere->reflection > 0)
    {
      // if sphere is made out reflective material, the reflection is calculated
      // i need the point of intersection and a point in the direction of the sphere normal
      vector_t reflection, incident;
      line_t reflectionLine;
      sphereNormal = pointstovector(&tmpSphere->center, &tmpSphere->intersection);
      incident = pointstovector(&r->p2, &r->p1);
      reflection = ReflectionVector(sphereNormal, incident);
      reflectionLine.p1 = tmpSphere->intersection;
      reflectionLine.p2 = vectorplusvector(tmpSphere->intersection, reflection);
      color = Trace(&reflectionLine, recursionDepth+1);
    }
     sphereNormal = pointstovector(&tmpSphere->center, &tmpSphere->intersection);
     sphereUnitNormal = createunitvector(&sphereNormal);  
    //diffuse and specular color calculation taking into account every source of light (sol)
    for(DiffuseLight=0, SpecularLight=0, i=0; i<solCount; i++)
    {
      ray = pointstovector(&tmpSphere->intersection, sol[i]);

      //check if source of light is blocked
      if(Intersection(pointstoline(&tmpSphere->intersection, sol[i] ),&dontCareSphere) != 0)
      {
        DiffuseLight += 0;
        SpecularLight += 0;
      }
      else
      {
        DiffuseLight += DiffuseReflection(tmpSphere, ray, sphereNormal);
        SpecularLight += pow(SpecularReflection(tmpSphere, ray, sphereNormal, r->p2), 40);
      }
    }
    if(DiffuseLight > 1)
    {
      DiffuseLight = 1.0f;
    }
    if(SpecularLight > 1)
    {
      SpecularLight = 1.0f;
    }

    float dred = tmpSphere->color.red*DiffuseLight; 
    float dgreen = tmpSphere->color.green*DiffuseLight;
    float dblue = tmpSphere->color.blue*DiffuseLight;
    float red = dred + (255-dred)*SpecularLight;
    float green = dgreen + (255-dgreen)*SpecularLight;
    float blue = dblue + (255-dblue)*SpecularLight;
    red =  red>255 ? 255:red;
    green = green>255 ? 255:green;
    blue = blue>255 ? 255:blue;
    
    if(tmpSphere->reflection>0)
    {
      color.red =   BlendColors( color.red, red, 0.25);
      color.green = BlendColors( color.green, green, 0.25);
      color.blue =  BlendColors( color.blue, blue, 0.25);
    }
    else
    {
      color.red = red;
      color.green = green;
      color.blue = blue;
    }
  }
   return color;
}

float DiffuseReflection(sphere_t* Sphere, vector_t ray, vector_t sphereNormal)
{
  float diffuseLight;
  float sumDiffuseLight = 0;
  diffuseLight = cosalpha(ray, sphereNormal); 
  if(diffuseLight < 0)
  {
    diffuseLight = 0;  
  }
  return diffuseLight;
}
vector_t ReflectionVector(vector_t normal, vector_t incident)
{ 
    normal = createunitvector(&normal);
    return vectorminusvector(scalartimesvector(dotproduct(scalartimesvector(2.0, incident), normal), normal), incident);
}
float SpecularReflection(sphere_t* Sphere, vector_t ray, vector_t sphereNormal, point_t pov)
{
     //  specular reflection calculation
    float specularLight;
    vector_t reflection = ReflectionVector(sphereNormal, ray); 
    specularLight = cosalpha( pointstovector(&Sphere->intersection, &pov) , reflection);     
    if(specularLight < 0)
    {
      specularLight = 0;
    } 
    return specularLight;
}

void DrawScene(void)
{  
  int i, j;
  line_t line;
  line.p1.x = 1.732f; //CANVAS_WIDTH/2 Point of view
  line.p1.y = 1.299f; //CANVAS_HEIGHT/2 Point of view
  line.p1.z = 0.0f;
  line.p2.z = 1.0f;
  color_t color;
  for(i=0; i<PIXEL_HEIGHT; i++)
  {
    for(j=0; j<PIXEL_WIDTH; j++)
    {
      line.p2.x = ((float)j+0.5)*CANVAS_WIDTH/PIXEL_WIDTH;
      line.p2.y =  ((float)i+0.5)*CANVAS_HEIGHT/PIXEL_HEIGHT;
      color = Trace(&line, 0);
      putpixel(j, PIXEL_HEIGHT-i-1, color.red, color.green, color.blue); 
    }
  }   
}
float BlendColors(float a, float b, float t)
{
  return sqrt( (1-t)*a*a + t*b*b);
}

void putpixel(int x, int y, unsigned char red, unsigned char green,unsigned char blue)
{
  PixelData_t* pixeldata = GetPixelData();
  pixeldata->data[y][x][0] = blue;
  pixeldata->data[y][x][1] = green;
  pixeldata->data[y][x][2] = red;
}
