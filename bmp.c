#include "bmp.h"
#include <stdlib.h>
#include <stdio.h>

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
