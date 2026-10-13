#ifndef PIXEL_H
#define PIXEL_H

struct _pixel // defining pixel structure
{
  float r;
  float g;
  float b;
  int x;
  int y;
};
typedef struct _pixel Pixel; // changing name of structure to pixel

#endif
