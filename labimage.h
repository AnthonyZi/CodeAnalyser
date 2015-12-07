#ifndef LABIMAGE_H
#define LABIMAGE_H

#include <cstdlib>
#include <stdint.h>
#include <iostream>
#include <cmath>
#include "rgbimage.h"

class LABImage
{
private:
        float* pixels;
        int width, height;

        LABImage();
        static void rgb_to_lab(float* labpix, unsigned char r, unsigned char g, unsigned char b);

public:
        LABImage(RGBImage* prgb);

        void setImage(RGBImage* prgb);

        int getWidth();
        int getHeight();
        float* getPixels();
        
        static float* getLAB(unsigned char r, unsigned char g, unsigned char b);
};

#endif
