#include <stdio.h>
#include "canvas.h"

int main(void)
{
  BMP_t *image;
  int fd;
  sphere_t* sphere[2];
  sphere_t sphere1;
  sphere_t sphere2;
  sphere[0] = &sphere1;
  sphere[1] = &sphere2;
  sphere[0]->sx = 1.732;
  sphere[0]->sy = 1.3;
  sphere[0]->sz = 3.0;
  sphere[0]->r  = 1.0;
  sphere[0]->color.red = 0xA4;
  sphere[0]->color.green = 0x69;
  sphere[0]->color.blue = 0xFF;
  sphere[1]->sx  = 0.5;
  sphere[1]->sy  = 0.5;
  sphere[1]->sz  = 2.5;
  sphere[1]->r   = 0.3f;
  sphere[1]->color.red = 0x0;
  sphere[1]->color.green = 0xFF;
  sphere[1]->color.blue = 0x0;
  image = CreateCanvas();
  fd = CreateBmpFile("picture.bmp");
 
  DrawSphere(image, sphere, 2);
  
  SaveBmpFile(fd, image); 
  return 0;
}
