#include "rgbimage.h"

RGBImage::RGBImage(png_bytep pdata, png_uint_32 pwidth, png_uint_32 pheight)
{
        width = pwidth;
        height = pheight;
        pixels = copydata(pdata, width*height*3);
}

void RGBImage::setPixels(png_bytep pdata, png_uint_32 pwidth, png_uint_32 pheight)
{
        width = pwidth;
        height = pheight;
        pixels = copydata(pdata, width*height*3);
}

void RGBImage::quickdownscale(png_uint_32 pmaxwidth, png_uint_32 pmaxheight)
{
        while(width > pmaxwidth || height > pmaxheight)
        {
                int widthold = width;
                width /= 2;
                height /= 2;

                png_bytep tmppixels = (png_bytep)malloc(sizeof(png_byte)*width*height*3);

                int sumr, sumg, sumb;
                for(png_uint_32 h = 0; h < height; h++)
                {
                        for(png_uint_32  w = 0; w < width*3; w+=3)
                        {
                                sumr = 0;
                                sumg = 0;
                                sumb = 0;

                                for(int i = 0; i<2; i++)
                                {
                                        for(int j = 0; j<=3; j+=3) { sumr += *(pixels+(2*h+i)*widthold*3+(2*w+j)); sumg += *(pixels+(2*h+i)*widthold*3+(2*w+j)+1);
                                                sumb += *(pixels+(2*h+i)*widthold*3+(2*w+j)+2);
                                        }
                                }

                                *(tmppixels+h*width*3+w) = sumr/4; 
                                *(tmppixels+h*width*3+w+1) = sumg/4;
                                *(tmppixels+h*width*3+w+2) = sumb/4;
                        }
                }
                pixels = (png_bytep)realloc(pixels, sizeof(png_byte)*width*height*3);
                pixels = tmppixels;
        }
}

void RGBImage::quickdownscale(png_uint_32 pmax)
{
        quickdownscale(pmax, pmax);
}

png_uint_32 RGBImage::getWidth()
{
        return width;
}

png_uint_32 RGBImage::getHeight()
{
        return height;
}

png_bytep RGBImage::getPixels()
{
        return pixels;
}

png_bytep RGBImage::copydata(png_bytep original, png_uint_32 length)
{
        png_bytep copy = (png_bytep)malloc(sizeof(png_byte)*length);
        for(png_uint_32 i = 0; i < length; i++)
        {
                *(copy+i) = *(original+i);
        }
        return copy;
}
