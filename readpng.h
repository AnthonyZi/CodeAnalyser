#ifndef READPNG_H
#define READPNG_H

#include <png.h>
#include <iostream>
#include <stdlib.h>
#include <string>

//errorcodes for check_png_version()
#define VERSIONERR (1)
//errorcodes for readpng_init()
#define FILEOPENERR (1)
#define FILEIDENTIFICATIONERR (2)
#define STRUCTINIERR (3)
#define SETJMPERR (4)

void print_png_version_info();
//version check -> 0 means everything is ok
int check_png_version();
// reading file into structs png_structp and png_infop -> 0 means ok!
int readpng_init(FILE*, png_structp*, png_infop*); 
// get the image in a png_byte[height][numrowbytes] + end_ptr(last param)
png_bytep readpng_get_image(png_structp*, png_infop*, png_infop*);
png_bytep readpng_get_image_noalpha(png_structp*, png_infop*, png_infop*);
png_bytep delete_alpha(png_structp*, png_infop*, png_bytep);

#endif
