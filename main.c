#include <stdio.h>
#include "vector.h"
#include "bmp.h"
#include "canvas.h"

int main(void)
{

  AddSphere(1.732, 1.3, 3.0, 1.0, 0xA4, 0x69, 0xFF);
  DrawSphere();
  SaveImage("picture4.bmp");
  return 0;
}