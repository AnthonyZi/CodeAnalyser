#ifndef BITIMAGE_H
#define BITIMAGE_H

#define RSTANDARD 0x14
#define GSTANDARD 0x1c
#define BSTANDARD 0x1b
#define THRESHOLDSTANDARD 300

#include <cstdlib>
#include "labimage.h"
#include <iostream>

class BITImage
{
private:
        bool* pixels;
        int width, height;
        int threshold;
        unsigned char rgbref[3];

        BITImage();
        int* getSignificance(LABImage* plab);
        bool* get_bitmatrix(int* sigmat);

public:
        BITImage(LABImage* plab);
        BITImage(LABImage* plab, unsigned char rref, unsigned char gref, unsigned char bref);

        void setImage(LABImage* plab);
        void setRef(unsigned char rref, unsigned char gref, unsigned char bref);
        void setThreshold(int threshold);

        int getWidth();
        int getHeight();
        bool* getPixels();
        unsigned char* getREF();
};

#endif
