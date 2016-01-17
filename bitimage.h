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
        bool* filter_median_square(bool* tmpimage, int kernelradius, bool ones, bool more, int threshold);
        int count_bits_in_square(bool* tmpimage, int kernelradius, bool ones, int xoff, int yoff);

public:
        //create new image out of plab and standard refs
        BITImage(LABImage* plab);
        //create new image out of plab and specified refs
        BITImage(LABImage* plab, unsigned char rref, unsigned char gref, unsigned char bref);
        //copy-constructor
        BITImage(const BITImage &pbitimage);

        void setImage(LABImage* plab);
        void setRef(unsigned char rref, unsigned char gref, unsigned char bref);
        //optional (normally unused because standard threshold is good)
        void setThreshold(int threshold);

        void erase_small_structures();

        int getWidth();
        int getHeight();
        bool* getPixels();
        unsigned char* getREF();
};

#endif
