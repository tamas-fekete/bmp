#include <stdio.h>
#include <stdlib.h>
#include "canvas.h"
typedef struct{
  char red;
  char green;
  char blue;
}color_t;

typedef struct{
 float sx;
 float sy;
 float sz;
 float r;
 color_t color;
}sphere_t;
typedef struct{
  float x1;
  float y1;
  float z1;
  float x2;
  float y2;
  float z2;
}line_t;

char LineIntersectsSphere(line_t *line, sphere_t *sphere);
void putpixel(BMP_t* image,int x, int y, char red, char green, char blue);

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

int DrawSphere(BMP_t *image, float sx, float sy, float sz, float r)
{
  int i, j;
  line_t line;
  sphere_t sphere;
  line.x1 = 1.732f;
  line.y1 = 1.299f;
  line.z1 = 0.0f;
  line.z2 = 1.0f;

  sphere.sx = sx;
  sphere.sy = sy;
  sphere.sz = sz;
  sphere.r  = r;


  for(i=0; i<PIXEL_HEIGHT; i++)
  {
    for(j=0; j<PIXEL_WIDTH; j++)
    {
      line.x2 = ((float)j+0.5)*CANVAS_WIDTH/PIXEL_WIDTH;
      line.y2 =  ((float)i+0.5)*CANVAS_HEIGHT/PIXEL_HEIGHT;
      if(LineIntersectsSphere(&line, &sphere))
      {
        putpixel(image, j, PIXEL_HEIGHT-i-1, 0xA4, 0x69, 0xFF);
      }
      else
      {
        putpixel(image, j, PIXEL_HEIGHT-i-1, 0xFF, 0xFF, 0xFF);
      }
    }
  }
}

void putpixel(BMP_t* image,int x, int y, char red, char green, char blue)
{
  image->pixeldata.data[y][x][0] = blue;
  image->pixeldata.data[y][x][1] = green;
  image->pixeldata.data[y][x][2] = red;
}
char LineIntersectsSphere(line_t *line, sphere_t *sphere)
{
  float x1 = line->x1;
  float x2 = line->x2;
  float x3 = sphere->sx;
  float y1 = line->y1;
  float y2 = line->y2;
  float y3 = sphere->sy;
  float z1 = line->z1;
  float z2 = line->z2;
  float z3 = sphere->sz;
  float r = sphere->r;
  float a = (x2-x1)*(x2-x1) + (y2-y1)*(y2-y1) + (z2-z1)*(z2-z1);
  float b = 2*((x2-x1)*(x1-x3) + (y2-y1)*(y1-y3) + (z2-z1)*(z1-z3));
  float c = x3*x3 + y3*y3 + z3*z3 + x1*x1 + y1*y1 + z1*z1 - 2*(x3*x1 + y3*y1 + z3*z1) - r*r;
  if( (b*b-4*a*c) < 0)
  {
    return 0;
  }
  else return 1;
}
