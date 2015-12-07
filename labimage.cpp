#include "labimage.h"

LABImage::LABImage(RGBImage* prgb) : pixels(NULL)
{
        setImage(prgb);
}

void LABImage::setImage(RGBImage* prgb)
{
        float* labpix;
        png_bytep rgbpixels = prgb->getPixels();
        width = (int)prgb->getWidth();
        height = (int)prgb->getHeight();

        if(pixels == NULL)
                pixels = (float*)malloc(sizeof(float)*width*height*3);
        else
                pixels = (float*)realloc(pixels, sizeof(float)*width*height*3);
        unsigned char rdat, gdat, bdat;
        for(uint32_t i = 0; i < (uint32_t)width*height; i++)
        {
                rdat = *(rgbpixels +i*3);
                gdat = *(rgbpixels +i*3 +1);
                bdat = *(rgbpixels +i*3 +2);
                
                labpix = pixels+i*3;
                rgb_to_lab(labpix, rdat, gdat, bdat);
        }
}

void LABImage::rgb_to_lab(float* labpix, unsigned char rdat, unsigned char gdat, unsigned char bdat)
{
        float tempx, tempy, tempz;
        float tempr, tempg, tempb;

        tempr = (float)rdat / 255;
        tempg = (float)gdat / 255;
        tempb = (float)bdat / 255;

        if(tempr > 0.04045)
                tempr = pow( (tempr+0.055)/1.055, 2.4);
        else
                tempr /= 12.92;
        if(tempg > 0.04045)
                tempg = pow( (tempg+0.055)/1.055, 2.4);
        else
                tempg /= 12.92;
        if(tempb > 0.04045)
                tempb = pow( (tempb+0.055)/1.055, 2.4);
        else
                tempb /= 12.92;

        tempr *= 100;
        tempg *= 100;
        tempb *= 100;

        tempx = tempr*0.4124 + tempg*0.3576 + tempb*0.1805;
        tempy = tempr*0.2126 + tempg*0.7152 + tempb*0.0722;
        tempz = tempr*0.0193 + tempg*0.1192 + tempb*0.9505;

        tempx /= 95.047;
        tempy /= 100;
        tempz /= 108.883;
        if(tempx > 0.008856)
                tempx = pow(tempx, 1.0/3);
        else
                tempx = (7.787*tempx) + (16.0/116);
        if(tempy > 0.008856)
                tempy = pow(tempy, 1.0/3);
        else
                tempy = (7.787*tempy) + (16.0/116);
        if(tempz > 0.008856)
                tempz = pow(tempz, 1.0/3);
        else
                tempz = (7.787*tempz) + (16.0/116);

        *(labpix) = (116*tempy) - 16;
        *(labpix+1) = 500*(tempx - tempy);
        *(labpix+2) = 200*(tempy - tempz);
}

int LABImage::getWidth()
{
        return width;
}

int LABImage::getHeight()
{
        return height;
}

float* LABImage::getPixels()
{
        return pixels;
}

float* LABImage::getLAB(unsigned char r, unsigned char g, unsigned char b)
{
        float* lab = (float*)malloc(sizeof(float)*3);
        rgb_to_lab(lab, r, g, b);
        return lab;
}
