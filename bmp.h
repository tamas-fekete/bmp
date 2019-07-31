
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define PIXEL_HEIGHT 768u
#define PIXEL_WIDTH 1024u
#define BYTES_PER_PIXEL 3u

#pragma pack(1)


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

void SaveImage(char *name);
PixelData_t* GetPixelData(void);
