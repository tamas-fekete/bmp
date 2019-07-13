#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#pragma pack ( 1 )

#define height 600
#define width 800
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
 int sx;
 int sy;
 int sz;
 int r;
 color_t color; 
}sphere_t;
typedef struct{
  int x1;
  int y1;
  int z1;
  int x2;
  int y2;
  int z2;
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
  sphere.sx  = 100;
  sphere.sy  = 100;
  sphere.sz  = 100;
  sphere.r = 1000;
  line.x1 = width/2;
  line.y1 = height/2;
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

  for(i=0; i<sizeof(image.pixeldata); i++)
  {
    image.pixeldata.datab[i]=0;
  }
 
  for(i=0; i<600; i++)
  {
    for(j=0; j<800; j++)
    {
      line.x2 = j;
      line.y2 = i;
      if(LineIntersectsSphere(&line, &sphere))
      {
        putpixel(&image, j, 599-i, 0xA4, 0x69, 0xFF);
      }
      else
      {
        putpixel(&image, j, 599-i, 0xFF, 0xFF, 0xFF);
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
  int a = (line->x2-line->x1)*(line->x2-line->x1)+(line->y2-line->y1)*(line->y2-line->y1)+(line->z2-line->z1)*(line->z2-line->z1);
  int b = 2*((line->x2-line->x1)*(line->x1-sphere->sx) + (line->y2-line->y1)*(line->y1-sphere->sy) + (line->z2-line->z1)*(line->z1-sphere->sz));
  int c = sphere->sx*sphere->sx+sphere->sy*sphere->sy+sphere->sz*sphere->sz+line->x1*line->x1+line->y1*line->y1+line->z1*line->z1-2*(sphere->sx*line->x1+sphere->sy*line->y1+sphere->sz*line->z1) - sphere->r*sphere->r;
  if( (b*b-4*a*c) < 0)
  {
    return 0;
  }
  else return 1;
}
