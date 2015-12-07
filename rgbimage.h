#ifndef RGBIMAGE_H
#define RGBIMAGE_H

#include <png.h>
#include <cstdlib>

class RGBImage
{
private:
        png_bytep pixels;
        png_uint_32 width, height;

        RGBImage();

public:
        RGBImage(png_bytep pdata, png_uint_32 width, png_uint_32 height);

        void setPixels(png_bytep pdata, png_uint_32 pwdith, png_uint_32 pheight);
        void quickdownscale(png_uint_32 pmaxwidth, png_uint_32 pmaxheight);
        void quickdownscale(png_uint_32 pmax);

        png_uint_32 getWidth();
        png_uint_32 getHeight();
        png_bytep getPixels();
        png_bytep copydata(png_bytep original, png_uint_32);
};

#endif
