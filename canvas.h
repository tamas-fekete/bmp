

#pragma pack (1)



#define CANVAS_HEIGHT  2.598f // PIXEL_HEIGHT*CANVAS_WIDTH/PIXEL_WIDTH
#define CANVAS_WIDTH   3.464f // 2*tan(60 degrees)







int DrawSphere(BMP_t *image, sphere_t* sphere[], int numberOfSphere);
int SaveBmpFile(int fd, BMP_t* image);
int CreateBmpFile(char *name);


BMP_t* CreateCanvas(void);
