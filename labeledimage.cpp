#include "labeledimage.h"

LABELEDImage::LABELEDImage(BITImage *pimage)
{
        std::vector<int> equivalences;
        int labelcounter = 1;

        pixels = (int*)malloc(sizeof(int)*pimage->getWidth()*pimage->getHeight());

        save_png(pimage->getPixels(), pimage->getWidth(), pimage->getHeight(), "debugpng/pimage.png");
        std::cout << "pimagewidth: " << pimage->getWidth() << " pimageheight: " << pimage->getHeight() << std::endl;

        for(int h = 0; h < pimage->getHeight(); h++)
        {
                for(int w = 0; w < pimage->getWidth(); w++)
                {
                        *(pixels+h*pimage->getWidth()+w) = getLabel(pimage, w, h, &labelcounter);
                }
        }
}

int LABELEDImage::getLabel(BITImage *pimage, int xoff, int yoff, int *currenthighest)
{
        bool* tmpimage = pimage->getPixels();
        int tmpwidth = pimage->getWidth();
        int tmpheight = pimage->getHeight();
        int leftbound = xoff > 0 ? -1 : 0;
        int upperbound = yoff > 0 ? -1 : 0;

        if(*(tmpimage+yoff*tmpheight+xoff) == 0)
                return 0;
        for(int h = upperbound; h <= 0; h++)
        {
                for(int w = leftbound; w <= 0; w++)
                {
                        if(*(pixels+(yoff+h)*tmpwidth+xoff+w) != 0)
                        {
                                std::cout << "!=0 at " << xoff << "/" << yoff << std::endl;
                                return *(pixels+(yoff+h)*tmpwidth+xoff+w);
                        }
                }
        }

        std::cout << *currenthighest << "currrenthighest at " << xoff << "/" << yoff << std::endl;
        return (*currenthighest)++;
}

int* LABELEDImage::getPixels()
{
        return pixels;
}
