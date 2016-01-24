#ifndef WRITEPNG_H
#define WRITEPNG_H

#include <png.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/* Write "bitmap" to a PNG file specified by "path"; returns 0 on
   success, non-zero on error. */

int save_png(png_bytep pixeldata, png_uint_32 width, png_uint_32 height, const char *path);

int save_png(bool* pixeldata, png_uint_32 width, png_uint_32 height, const char *path);

#endif
