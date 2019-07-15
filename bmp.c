#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#pragma pack ( 1 )

#define height 768
#define width 1024
#define canvasheight 2.598
#define canvaswidth 3.464
#define bytesperpixel 3

typedef struct{
  u_int16_t Signature; // magic: 0x42 0x4D
  u_int32_t FileSize;
  u_int32_t reserved;
  u_int32_t DataOffset;
}Header_t;

typedef struct{
  u_int32_t Size;
  u_int32_t Width;
  u_int32_t Height;
  u_int16_t Planes;
  u_int16_t BitsPerPixel;
  u_int32_t Compression;
  u_int32_t ImageSize;
  u_int32_t XpixelsPerMeter;
  u_int32_t YpixelsPerMeter;
  u_int32_t ColorsUsed;
  u_int32_t ImportantColors;
}InfoHeader_t;

typedef struct{
  union{
  char data[height][width][bytesperpixel];
  char datab[height*width*bytesperpixel];
  };
}PixelData_t;

typedef struct{
  Header_t header;
  InfoHeader_t infoheader;
  PixelData_t pixeldata;
}BMP_t;

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

void putpixel(BMP_t* image,int x, int y, char red, char green, char blue);
char LineIntersectsSphere(line_t *line, sphere_t *sphere);
int main(void)
{
  BMP_t image;
  int fd;
  int bytes;
  unsigned int i, j;
  sphere_t sphere;
  line_t line;
  sphere.sx  = 1.732;
  sphere.sy  = 1.3;
  sphere.sz  = 3;
  sphere.r = 1;
  line.x1 = 1.732;
  line.y1 = 1.299;
  line.z1 = 0;
  line.z2 = 1;

  image.header.Signature = 0x4D42;
  image.header.FileSize  = sizeof(image);
  image.header.reserved  = 0;
  image.header.DataOffset= sizeof(Header_t) + sizeof(InfoHeader_t);
  image.infoheader.Size = sizeof(InfoHeader_t);
  image.infoheader.Width = width;
  image.infoheader.Height= height;
  image.infoheader.Planes = 1;
  image.infoheader.BitsPerPixel = bytesperpixel*8;
  image.infoheader.Compression = 0;
  image.infoheader.ImageSize = 0;
  image.infoheader.XpixelsPerMeter = 0;
  image.infoheader.YpixelsPerMeter = 0;
  image.infoheader.ColorsUsed = 0;
  image.infoheader.ImportantColors = 0;

  if((fd=open("picture.bmp", O_RDWR|O_CREAT))==-1)
  {
    perror("open error:");
    return -1;
  }
  printf("fd: %d\n", fd);
  printf("sizeof integer: %ld", sizeof(int));
  for(i=0; i<sizeof(image.pixeldata); i++)
  {
    image.pixeldata.datab[i]=0;
  }
  
  printf("here\n");
  for(i=0; i<height; i++)
  {
    for(j=0; j<width; j++)
    {
      line.x2 = ((float)j+0.5)*canvaswidth/width;
      line.y2 =  ((float)i+0.5)*canvasheight/height;
      if(LineIntersectsSphere(&line, &sphere))
      {
        putpixel(&image, j, height-i-1, 0xA4, 0x69, 0xFF);
      }
      else
      {
        putpixel(&image, j, height-i-1, 0xFF, 0xFF, 0xFF);
      }
    }
  }

  if((bytes=write(fd, &image.header, sizeof(image))) < sizeof(image))
  {
     printf("bytes written: %d. Size: %ld\n", bytes, sizeof(image));
     perror("write error:");
     return -1;
  } 

  printf("sizeof header: %ld.\n", sizeof(Header_t));
  printf("sizeof header: %ld.\n", sizeof(InfoHeader_t));
  printf("sizeof header: %ld.\n", sizeof(PixelData_t));
  printf("sizeof header: %ld.\n", sizeof(BMP_t));
  
  if(close(fd) == -1)
  {
    perror("close error:");
    return -1;
  }
  return 0;
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
