#include <stdio.h>
#include "canvas.h"

int main(void)
{
  BMP_t *image;
  int fd;
  printf("here1\n");  
  image = CreateCanvas();
  printf("here2\n");
  fd = CreateBmpFile("picture.bmp");
  printf("here3\n");
  DrawSphere(image, 1.732f, 1.3f, 3.0f, 1.0f);   
 printf("here4\n"); 
  SaveBmpFile(fd, image);

 
  return 0;

}
