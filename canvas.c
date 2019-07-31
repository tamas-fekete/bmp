#include <stdio.h>
#include <stdlib.h>
#include "vector.h"
#include "canvas.h"
#include <math.h>


char LineIntersectsSphere(line_t *line, sphere_t *sphere, point_t* point);
void putpixel(BMP_t* image,int x, int y, unsigned char red, unsigned char green, unsigned char blue);
float cosalpha(vector_t p1, vector_t p2);
float dotproduct(vector_t v1, vector_t v2);
BMP_t* CreateCanvas(void)
{
  int i;
  BMP_t* image = (BMP_t*)malloc(sizeof(BMP_t)); 
  image->header.Signature = 0x4D42;
  image->header.FileSize  = sizeof(BMP_t);
  image->header.reserved  = 0;
  image->header.DataOffset= sizeof(Header_t) + sizeof(InfoHeader_t);
  image->infoheader.Size = sizeof(InfoHeader_t);
  image->infoheader.Width = PIXEL_WIDTH;
  image->infoheader.Height= PIXEL_HEIGHT;
  image->infoheader.Planes = 1;
  image->infoheader.BitsPerPixel = BYTES_PER_PIXEL*8;
  image->infoheader.Compression = 0;
  image->infoheader.ImageSize = 0;
  image->infoheader.XpixelsPerMeter = 0;
  image->infoheader.YpixelsPerMeter = 0;
  image->infoheader.ColorsUsed = 0;
  image->infoheader.ImportantColors = 0;
  
  for(i=0; i<sizeof(image->pixeldata); i++)
  {
    image->pixeldata.datab[i]=0;
  }
  return image;
}

int CreateBmpFile(char *name)
{
  int fd;
  if((fd=open(name, O_RDWR|O_CREAT))==-1)
  {
    perror("open error:");
    return -1;
  }
  else return fd;
}


int SaveBmpFile(int fd, BMP_t* image)
{
  int bytes;
  if((bytes=write(fd, image, sizeof(BMP_t))) < sizeof(BMP_t))
  {
     printf("bytes written: %d. Size: %ld\n", bytes, sizeof(image));
     perror("write error:");
     return -1;
  } 
 if(close(fd) == -1)
  {
    perror("close error:");
    return -1;
  }

  return 0;
}

int DrawSphere(BMP_t *image, sphere_t* sphere[], int numberOfSpheres)
{
  int i, j, k;
  line_t line;
  line.p1.x = 1.732f; //CANVAS_WIDTH/2 Point of view
  line.p1.y = 1.299f; //CANVAS_HEIGHT/2 Point of view
  line.p1.z = 0.0f;
  line.p2.z = 1.0f;
  point_t sol;
  sol.x = -1.0f;
  sol.y = 1.3f;
  sol.z = 1.0f;
  vector_t ray;
  vector_t spherenormal;
  point_t intersection; //pov sphere point of intersection
  float light = 0.0;
  float specularLight = 0.0;
  float light2 = 0.0;
  for(i=0; i<PIXEL_HEIGHT; i++)
  {
    for(j=0; j<PIXEL_WIDTH; j++)
    {
      line.p2.x = ((float)j+0.5)*CANVAS_WIDTH/PIXEL_WIDTH;
      line.p2.y =  ((float)i+0.5)*CANVAS_HEIGHT/PIXEL_HEIGHT;
      for(k=0; k<numberOfSpheres; k++)
      {
        if(LineIntersectsSphere(&line, sphere[k], &intersection))
        {
         vector_t sphereUnitNormal;
         vector_t vtmp;
         vector_t reflection;
         spherenormal = pointstovector(&sphere[k]->center, &intersection);
         
         ray = pointstovector(&intersection, &sol);
         //diffuse reflection calculation
         light = cosalpha(ray, spherenormal);
         if(light <= 0)
         {
           light = 0;
           light2 = 0;
         }
          
          if(light > 0)
          {
         //specular reflection calculation
            sphereUnitNormal = createunitvector(&spherenormal);
            reflection = vectorminusvector(scalartimesvector(dotproduct(scalartimesvector(2.0, ray), sphereUnitNormal),sphereUnitNormal), ray);
            
            light2 = cosalpha( pointstovector(&intersection, &line.p2) , reflection);
          }
          if(light2 <= 0)
          {
            light2 = 0;
          }
          
          light2 = pow(light2, 40);
          
          float dred = sphere[k]->color.red*light; 
          float dgreen = sphere[k]->color.green*light;
          float dblue = sphere[k]->color.blue*light;
          float red = dred + (255-dred)*light2;
          float green = dgreen + (255-dgreen)*light2;
          float blue = dblue + (255-dblue)*light2;
        red =  red>255 ? 255:red;
        green = green>255 ? 255:green;
        blue = blue>255 ? 255:blue;
          //display
        
         // putpixel(image, j, PIXEL_HEIGHT-i-1, sphere[k]->color.red*light, sphere[k]->color.green*light, sphere[k]->color.blue*light);
        // putpixel(image, j, PIXEL_HEIGHT-i-1,255.0*light2, 255.0*light2, 255.0*light2);
           putpixel(image, j, PIXEL_HEIGHT-i-1, red, green, blue);
          
          break;
        }
        else
        {
          putpixel(image, j, PIXEL_HEIGHT-i-1, 0xFF, 0xFF, 0xFF);
        }
      }
    }
  }
}

void putpixel(BMP_t* image,int x, int y, unsigned char red, unsigned char green,unsigned char blue)
{
  
  image->pixeldata.data[y][x][0] = blue;
  image->pixeldata.data[y][x][1] = green;
  image->pixeldata.data[y][x][2] = red;
}

