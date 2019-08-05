#include <stdio.h>
#include "vector.h"
#include "bmp.h"
#include "canvas.h"

int main(void)
{

  AddSphere(0.7, 1.0, 3.0, 1.0, 0xA4, 0x69, 0xFF);
  AddSphere(2.5, 1.7, 4.1, 0.6, 0x7f, 0x0, 0x0);
  AddSphere(2.5, 1.8, 8.0, 3.0, 0x00, 0x00, 0xAf);
  AddSol(-1.0, 1.3, 1.0);
  AddSol(-1.0, -2.0, 2.0);
  DrawSphere();
  SaveImage("picture4.bmp");
  return 0;
}
