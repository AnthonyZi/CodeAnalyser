#include "rgbimage.h"

RGBImage::RGBImage(std::string ppath)
{
        if(loadPNG(ppath))
                std::cerr << "loading of the image failed" << std::endl;
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

int RGBImage::loadPNG(std::string ppath)
{
        pixels = NULL;

        if(check_png_version())
        {
                std::cerr << "png version check failed" << std::endl;
                return 1;
        }

        //load file and load variables to read png
        FILE* fp = fopen(ppath.c_str(), "rb");
        if(!fp)
        {
                std::cerr << "couldn't open " << ppath << std::endl;
                return 1;
        }
        png_structp png_ptr = NULL;
        png_infop info_ptr = NULL;

        if(readpng_init(fp, &png_ptr, &info_ptr))
        {
                std::cerr << "png-read initialisation failed" << std::endl;
                return 1;
        }
        pixels = readpng_get_image_white_alpha(&png_ptr, &info_ptr, NULL);

        width = png_get_image_width(png_ptr, info_ptr);
        height = png_get_image_height(png_ptr, info_ptr);

        fclose(fp);
        png_destroy_read_struct(&png_ptr, &info_ptr, NULL);

        if(pixels == NULL)
        {
                std::cerr << "pixel-data is not valid" << std::endl;
        }
        return 0;
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
