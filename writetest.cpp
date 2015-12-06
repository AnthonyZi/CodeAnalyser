#include <png.h>
#include <cstdlib>
#include "writepng.h"

int main()
{
        png_uint_32 width = 1280;
        png_uint_32 height = 768;
        png_bytep pixels = (png_bytep)malloc(sizeof(png_byte)*width*3*height);

        for(png_uint_32 i = 0; i < height; i++)
        {
                for(png_uint_32 j = 0; j < width*3; j++)
                {
                        *(pixels+i*width*3+j) = rand()%255;
                }
        }


        bool* data = (bool*)malloc(sizeof(bool)*width*height);

        for(int i = 0; i < height; i++)
        {
                for(int j = 0; j < width; j++)
                {
                        *(data+i*width+j) = (i/20)%2;
                }
        }

        save_png(pixels, width, height, "selfmade.png");
        save_png(data, width, height, "binary.png");
}
