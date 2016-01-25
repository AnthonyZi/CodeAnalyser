#ifndef LABELEDIMAGE_H
#define LABELEDIMAGE_H

#include <vector>
#include "bitimage.h"

class LABELEDImage
{
private:
        LABELEDImage();

        int getLabel(BITImage *pimage, int xoff, int yoff, int currenthighest)

public:
        LABELEDImage(BITImage pimage);
};

#endif
