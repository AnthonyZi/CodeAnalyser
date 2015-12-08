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

void BITImage::erase_small_structures()
{
        bool* tmpimage = (bool*)malloc(sizeof(bool)*width*height);
        for(uint32_t i = 0; i < (uint32_t)width*height; i++)
                *(tmpimage+i) = *(pixels+i);
        int filterclass = (int)log2((width < height ? width : height)/100);
        for(int i = 0; i < filterclass; i++)
                tmpimage = filter_median_square(tmpimage, 1, 0, 1, 2);
        tmpimage = filter_median_square(tmpimage, filterclass, 1, 1, 1);
        for(uint32_t i = 0; i < (uint32_t)width*height; i++)
                *(pixels+i) = (*(pixels+i) & *(tmpimage+i));
}

bool* BITImage::filter_median_square(bool* ptmpimage, int kernelradius, bool ones, bool more, int threshold)
{
        bool* tmp = (bool*)malloc(sizeof(bool)*width*height);
        if(more)
        {
                for(int h = 0; h < height; h++)
                {
                        for(int w = 0; w < width; w++)
                        {
                                *(tmp+h*width+w) = count_bits_in_square(ptmpimage, kernelradius, ones, w, h) > threshold ? ones : !ones;
                        }
                }
        }
        else
        {
                for(int h = 0; h < height; h++)
                {
                        for(int w = 0; w < width; w++)
                        {
                                *(tmp+h*width+w) = count_bits_in_square(ptmpimage, kernelradius, ones, w, h) < threshold ? ones : !ones;
                        }
                }
        }
        free(ptmpimage);
        return tmp;
}

int BITImage::count_bits_in_square(bool* ptmpimage, int kernelradius, bool ones, int xoff, int yoff)
{ 
        int sum = 0; 
        for(int y = -kernelradius; y <= kernelradius; y++) 
        { 
                for(int x = -kernelradius; x <= kernelradius; x++) 
                {
                        if(xoff+x > 0 && xoff+x < width && yoff+y > 0 && yoff+y < height)
                        { 
                                sum += *(ptmpimage+(yoff+y)*width+(xoff+x)); 
                        } 
                } 
        } 
        if(ones) 
                return sum; 
        else 
                return (2*kernelradius+1)*(2*kernelradius+1)-sum; 
}
