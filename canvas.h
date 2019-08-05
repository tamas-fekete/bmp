#pragma pack (1)

#define CANVAS_HEIGHT  2.598f // PIXEL_HEIGHT*CANVAS_WIDTH/PIXEL_WIDTH
#define CANVAS_WIDTH   3.464f // 2*tan(60 degrees)

void AddSphere(float x, float y, float z, float r, unsigned char red, unsigned char green, unsigned char blue);
void AddSol(float x, float y, float z);
int DrawSphere(void);
