#include <stdio.h>
#include "canvas.h"

int main(void)
{
  BMP_t *image;
  int fd;
 
  image = CreateCanvas();
  fd = CreateBmpFile("picture.bmp");
 
  DrawSphere(image, 1.732f, 1.3f, 3.0f, 1.0f);//image, x, y, z, radius
  
  SaveBmpFile(fd, image); 
  return 0;
}
