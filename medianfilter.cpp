#include "medianfilter.h"

float bits_in_shape(BITImage *sourceimage, Shape *kernel, bool ones, int xoff, int yoff)
{ 
        int sum = 0; 
        int leftkernelradius = (kernel->getSize()-1)/2;
        int yleftborder = yoff-leftkernelradius > 0 ? yoff-leftkernelradius : 0;
        int yrightborder = yleftborder+kernel->getSize() < sourceimage->getHeight() ? yleftborder+kernel->getSize() : sourceimage->getHeight();

        int xleftborder = xoff-leftkernelradius > 0 ? xoff-leftkernelradius : 0;
        int xrightborder = xleftborder+kernel->getSize() < sourceimage->getWidth() ? xleftborder+kernel->getSize() : sourceimage->getWidth();

        int ykerneloffset = leftkernelradius-yoff > 0 ? leftkernelradius-yoff : 0;
        int xkerneloffset = leftkernelradius-xoff > 0 ? leftkernelradius-xoff : 0;

        for(int y = yleftborder, ykoff = ykerneloffset; y < yrightborder; y++, ykoff++)
        { 
                for(int x = xleftborder, xkoff = xkerneloffset; x < xrightborder; x++, xkoff++) 
                {
                        sum += *(sourceimage->getPixels()+y*sourceimage->getWidth()+x) && *(kernel->getmatrix()+ykoff*kernel->getSize()+xkoff);
                } 
        } 
        if(ones) 
                return sum; 
        else return kernel->getonescounted()-sum; 
}

void filter_median(BITImage *sourceimage, Shape *kernel, bool ones, bool more, float threshold)
{
        bool* tmp = (bool*)malloc(sizeof(bool)*sourceimage->getWidth()*sourceimage->getHeight());
        if(more)
        {
                for(int h = 0; h < sourceimage->getHeight(); h++)
                {
                        for(int w = 0; w < sourceimage->getWidth(); w++)
                        {
                                *(tmp+h*sourceimage->getWidth()+w) = bits_in_shape(sourceimage, kernel, ones, w, h) > threshold ? ones : !ones;
                        }
                }
        }
        else
        {
                for(int h = 0; h < sourceimage->getHeight(); h++)
                {
                        for(int w = 0; w < sourceimage->getWidth(); w++) {
                                *(tmp+h*sourceimage->getWidth()+w) = bits_in_shape(sourceimage, kernel, ones, w, h) < threshold ? ones : !ones;
                        }
                }
        }
        sourceimage->setPixels(tmp);
}

void extend_image(BITImage *sourceimage, Shape *kernel, bool ones)
{
        bool* tmp = (bool*)malloc(sizeof(bool)*sourceimage->getWidth()*sourceimage->getHeight());
        bool* tmpsourceimage = sourceimage->getPixels();
        bool* tmpkernel = kernel->getmatrix();

        int sourceheight = sourceimage->getHeight();
        int sourcewidth = sourceimage->getWidth();
        int kernelsize = kernel->getSize();

        for(int z = 0; z < sourcewidth*sourceheight; z++)
                *(tmp+z) = 0;

        for(int h = 0; h < sourceheight; h++)
        {
                for(int w = 0; w < sourcewidth; w++)
                {
                        if(*(tmpsourceimage+h*sourcewidth+w))
                        {
                                int leftkernelradius = (kernel->getSize()-1)/2;
                                int yleftborder = h-leftkernelradius > 0 ? h-leftkernelradius : 0;
                                int yrightborder = yleftborder+kernelsize < sourceheight ? yleftborder+kernelsize : sourceheight;

                                int xleftborder = w-leftkernelradius > 0 ? w-leftkernelradius : 0;
                                int xrightborder = xleftborder+kernelsize < sourcewidth ? xleftborder+kernelsize : sourcewidth;

                                int ykerneloffset = leftkernelradius-h > 0 ? leftkernelradius-h : 0;
                                int xkerneloffset = leftkernelradius-w > 0 ? leftkernelradius-w : 0;

                                for(int y = yleftborder, ykoff = ykerneloffset; y < yrightborder; y++, ykoff++)
                                {
                                        for(int x = xleftborder, xkoff = xkerneloffset; x < xrightborder; x++, xkoff++)
                                        {
                                                *(tmp+y*sourcewidth+x) |= *(tmpkernel+ykoff*kernelsize+xkoff);
                                        }
                                }
                        }
                }
        }
        sourceimage->setPixels(tmp);
}
