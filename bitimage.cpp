#include "bitimage.h"

BITImage::BITImage(LABImage* plab) : pixels(NULL), threshold(THRESHOLDSTANDARD)
{
        rgbref[0] = RSTANDARD;
        rgbref[1] = GSTANDARD;
        rgbref[2] = BSTANDARD;
        setImage(plab);
}

BITImage::BITImage(LABImage* plab, unsigned char rref, unsigned char gref, unsigned char bref) : pixels(NULL), threshold(THRESHOLDSTANDARD)
{
        rgbref[0] = rref;
        rgbref[1] = gref;
        rgbref[2] = bref;
        setImage(plab);
}

void BITImage::setImage(LABImage* plab)
{
        width = plab->getWidth();
        height = plab->getHeight();

        int* sigmat = getSignificance(plab);
        pixels = get_bitmatrix(sigmat);
        free(sigmat);
}

void BITImage::setRef(unsigned char r, unsigned char g, unsigned char b)
{
        rgbref[0] = r;
        rgbref[1] = g;
        rgbref[2] = b;
}

void BITImage::setThreshold(int pthreshold)
{
        threshold = pthreshold;
}

int* BITImage::getSignificance(LABImage* plab)
{
        float* labpixels = plab->getPixels();

        float* labref = plab->getLAB(rgbref[0], rgbref[1], rgbref[2]);

        int* sig_mat = (int*)malloc(sizeof(int)*width*height);
        
        float ldat, adat, bdat;
        float ldif, adif, bdif;
        for(uint32_t i = 0; i<(uint32_t)width*height; i++)
        {
                ldat = *(labpixels+i*3);
                adat = *(labpixels+i*3+1);
                bdat = *(labpixels+i*3+2);

                ldif = ldat-*(labref);
                adif = adat-*(labref+1);
                bdif = bdat-*(labref+2);

                *(sig_mat+i) = 10*sqrt(ldif*ldif + adif*adif + bdif*bdif);
        }

        free(labref);

        return sig_mat;
}

bool* BITImage::get_bitmatrix(int* sigmat)
{        
        bool* bitmat = (bool*)malloc(sizeof(bool)*width*height);
        for(int h = 0; h<height; h++)
        {
                for(int w = 0; w<width; w++)
                {
                        int tmp = *(sigmat+h*width+w);
                        *(bitmat+h*width+w) = tmp>threshold ? false : true;
                }
        }
        return bitmat;
}

int BITImage::getWidth()
{
        return width;
}

int BITImage::getHeight()
{
        return height;
}

bool* BITImage::getPixels()
{
        return pixels;
}

unsigned char* BITImage::getREF()
{
        return &rgbref[0];
}
