
#include <stdlib.h>
#include <stdio.h>
#include "bmp.h"

static BMP_t image; 

void InitBmpHeader(void);
int CreateBmpFile(char* name);
int SaveBmpFile(int fd);

void SaveImage(char *name)
{ 
  int fd = CreateBmpFile(name);
  InitBmpHeader();
  SaveBmpFile(fd);
  
}
void InitBmpHeader(void)
{
  image.header.Signature = 0x4D42;
  image.header.FileSize  = sizeof(BMP_t);
  image.header.reserved  = 0;
  image.header.DataOffset= sizeof(Header_t) + sizeof(InfoHeader_t);
  image.infoheader.Size = sizeof(InfoHeader_t);
  image.infoheader.Width = PIXEL_WIDTH;
  image.infoheader.Height= PIXEL_HEIGHT;
  image.infoheader.Planes = 1;
  image.infoheader.BitsPerPixel = BYTES_PER_PIXEL*8;
  image.infoheader.Compression = 0;
  image.infoheader.ImageSize = 0;
  image.infoheader.XpixelsPerMeter = 0;
  image.infoheader.YpixelsPerMeter = 0;
  image.infoheader.ColorsUsed = 0;
  image.infoheader.ImportantColors = 0;
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


int SaveBmpFile(int fd)
{
  int bytes;
  if((bytes=write(fd, &image, sizeof(BMP_t))) < sizeof(BMP_t))
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

PixelData_t* GetPixelData(void)
{
  return &image.pixeldata;
}