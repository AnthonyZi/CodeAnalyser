#ifndef RGBIMAGE_H
#define RGBIMAGE_H

#include <png.h>
#include <cstdlib>
#include <iostream>
#include "readpng.h"

class RGBImage
{
private:
        png_bytep pixels;
        png_uint_32 width, height;

        RGBImage();

public:
        RGBImage(std::string ppath);

        void setPixels(png_bytep pdata, png_uint_32 pwdith, png_uint_32 pheight);
        void quickdownscale(png_uint_32 pmaxwidth, png_uint_32 pmaxheight);
        void quickdownscale(png_uint_32 pmax);

        int loadPNG(std::string path);

        png_uint_32 getWidth();
        png_uint_32 getHeight();
        png_bytep getPixels();
};

#endif
