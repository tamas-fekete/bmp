#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#pragma pack (1)

#define PIXEL_HEIGHT 768u
#define PIXEL_WIDTH 1024u

#define CANVAS_HEIGHT  2.598f
#define CANVAS_WIDTH   3.464f
#define BYTES_PER_PIXEL 3u


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
  char data[PIXEL_HEIGHT][PIXEL_WIDTH][BYTES_PER_PIXEL];
  char datab[PIXEL_HEIGHT*PIXEL_WIDTH*BYTES_PER_PIXEL];
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

int DrawSphere(BMP_t *image, sphere_t* sphere[], int numberOfSphere);
int SaveBmpFile(int fd, BMP_t* image);
int CreateBmpFile(char *name);
BMP_t* CreateCanvas(void);


