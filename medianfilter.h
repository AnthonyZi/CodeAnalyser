#ifndef MEDIANFILTER_H
#define MEDIANFILTER_H

void filter_median(BITImage *sourceimage, Shape *kernel, bool ones, bool more, float threshold)
{
        bool* tmp = (bool*)malloc(sizeof(bool)*sourceimage->width*sourceimage->heigth);
        if(more)
        {
                for(int h = 0; h < height; h++)
                {
                        for(int w = 0; w < width; w++)
                        {
                                *(tmp+h*width+w) = bits_in_square(sourceimage, kernel, ones, w, h) > threshold ? ones : !ones;
                        }
                }
        }
        else
        {
                for(int h = 0; h < height; h++)
                {
                        for(int w = 0; w < width; w++)
                        {
                                *(tmp+h*width+w) = bits_in_square(sourceimage, kernel, ones, w, h) < threshold ? ones : !ones;
                        }
                }
        }
        sourceimage->setPixels(tmp);
}


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

        for(int y = yleftborder, int ykoff = ykerneloffset; y < yrightborder; y++, ykoff++)
        { 
                for(int x = xleftborder, int xkoff = xkerneloffset; x < xrightborder; x++, xkoff++) 
                {
                        sum += *(sourceimage->getPixels()+y*sourceimage->getWidth()+x) && *(kernel->getmatrix()+ykoff*kernel->getSize()+xkoff);
                } 
        } 
        if(ones) 
                return sum; 
        else 
                return kernel->getonescounted()-sum; 
}


#endif
