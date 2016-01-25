#include "labeledimage.h"

LABELEDImage::LABELEDImage(BITImage *pimage)
{
        std::vector<int> equivalences;
        int labelcounter = 1;

        for(int h = 0; h < pimage->getHeight(); h++)
        {
                for(int w = 0; w < pimage->getWidth(); w++)
                {
                        
                }
        }
}

int LABELEDImage::getLabel(BITImage *pimage, int xoff, int yoff, int currenthighest)
{
        for(int i = -1; i < 1; i++)
        {
                for(int j = -1; j < 1; j++)
                {

                }
        }

        return currenthighest;
}
