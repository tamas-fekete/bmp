#pragma pack (1)
#include <math.h>
#define CANVAS_HEIGHT  PIXEL_HEIGHT*CANVAS_WIDTH/PIXEL_WIDTH //2.598f // PIXEL_HEIGHT*CANVAS_WIDTH/PIXEL_WIDTH
#define CANVAS_WIDTH  2*tan(1.0472)// 3.464f // 2*tan(60 degrees)

void AddSphere(float x, float y, float z, float r, unsigned char red, unsigned char green, unsigned char blue, double reflection);
void AddSol(float x, float y, float z);
void DrawScene(void);
