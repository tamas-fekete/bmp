#include <stdio.h>
#include "vector.h"
#include "bmp.h"
#include "canvas.h"

int main(void)
{
  AddSphere(1.0, 1.0, 1.5, 0.35, 0xFF, 0xFF, 0x00, 0.0);
  AddSphere(1.2, 0.5, 2.0, 0.4, 0xA4, 0x69, 0xFF, 0.0);
  AddSphere(0.0, 0.0, 2.0, 0.6, 0x7f, 0x0, 0x0, 1.0);
  AddSphere(3.0, 0.0, 14.0, 10.0, 0x00, 0x00, 0xf0, 1.0);
  AddSol(4.0, 3.0, 0.0);
  AddSol(1.7, -3.0, 2.0);
//  AddSol(1.7, 1.3, 4.0);
//  AddSol(4.0, 3.2, 0.0);
  DrawScene();
  SaveImage("picture8.bmp");
  return 0;
}
