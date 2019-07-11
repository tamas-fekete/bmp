#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#pragma pack ( 1 )
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
  char data[600][800][3];
  char datab[600*800*3];
  };
}PixelData_t;

typedef struct{
  Header_t header;
  InfoHeader_t infoheader;
  PixelData_t pixeldata;
}BMP_t;


int main(void)
{

  BMP_t image;
  int fd;
  int bytes;
  unsigned int i;
  image.header.Signature = 0x4D42;
  image.header.FileSize  = sizeof(image);
  image.header.reserved  = 0;
  image.header.DataOffset= sizeof(Header_t) + sizeof(InfoHeader_t);
  image.infoheader.Size = sizeof(InfoHeader_t);
  image.infoheader.Width = 800;
  image.infoheader.Height= 600;
  image.infoheader.Planes = 1;
  image.infoheader.BitsPerPixel = 24;
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

  for(i=0; i<800*600*3; i++)
  {
    image.pixeldata.datab[i]=255;
  }
  image.pixeldata.data[300][400][0] = 0;
  image.pixeldata.data[300][400][1] = 0;
  image.pixeldata.data[300][400][2] = 0;
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

