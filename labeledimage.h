#ifndef LABELEDIMAGE_H
#define LABELEDIMAGE_H

#include <vector>
#include "bitimage.h"
#include "writepng.h"

#include <iostream>

class LABELEDImage
{
private:
        int* pixels;


        LABELEDImage();

        int getLabel(BITImage *pimage, int xoff, int yoff, int *currenthighest);

public:
        LABELEDImage(BITImage *pimage);

        int* getPixels();
};

#endif
