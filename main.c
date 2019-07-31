#include <stdio.h>
#include "vector.h"
#include "bmp.h"
#include "canvas.h"

int main(void)
{
  BMP_t *image;
  int fd;
  sphere_t* sphere[1];
  sphere_t sphere1;
  sphere_t sphere2;

  image = CreateCanvas();
  fd = CreateBmpFile("picture22.bmp");
  AddSphere(1.732, 1.3, 3.0, 1.0, 0xA4, 0x69, 0xFF);
  DrawSphere(image);
  
  SaveBmpFile(fd, image); 
  return 0;
}